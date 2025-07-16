/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/16 17:03:38 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static void	init_sphere_struct(t_object *object, t_sphere *sphere)
{
	object->type = SPHERE;
	object->data = (void *)sphere;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
}

static t_sphere_quad	intersect_sphere_quad(t_ray *ray, t_sphere *sphere)
{
	t_vector3d		l;
	t_sphere_quad	quad;

	if (!ray || !sphere)
	{
		ft_bzero(&quad, sizeof(t_sphere_quad));
		quad.discriminant = -1.0f;
		return (quad);
	}
	l = subtract_vectors(ray->origin, sphere->sphere_center);
	quad.a = dot_product(ray->direction, ray->direction);
	quad.b = 2.0f * dot_product(ray->direction, l);
	quad.c = dot_product(l, l)
		- (sphere->diameter * sphere->diameter) / 4.0f;
	quad.discriminant = quad.b * quad.b - 4.0f * quad.a * quad.c;
	return (quad);
}

static bool	intersect_sphere_solution(t_sphere_quad quad, float *t)
{
	float	nearest;
	float	farther;

	if (!t)
		return (false);
	if (quad.discriminant < 0.0f)
		return (false);
	if (quad.a == 0.0f || quad.discriminant < 0.0f || isnan(quad.discriminant))
		return (false);
	nearest = (-quad.b - sqrtf(quad.discriminant)) / (2.0f * quad.a);
	farther = (-quad.b + sqrtf(quad.discriminant)) / (2.0f * quad.a);
	if (nearest < 0.0f && farther < 0.0f)
		return (false);
	else if (nearest < 0.0f)
		*t = farther;
	else if (farther < 0.0f)
		*t = nearest;
	else
	{
		if (nearest < farther)
			*t = nearest;
		else
			*t = farther;
	}
	return (true);
}

void	uv_map(t_vector3d point, t_sphere *sphere, float *u, float *v)
{
	t_vector3d	local;

	if (!sphere || !u || !v)
		return ;
	local = normalize(subtract_vectors(point, sphere->sphere_center));
	*u = 0.5f + atan2f(local.z, local.x) / (2 * M_PI);
	*v = 0.5f - asinf(local.y) / M_PI;
	if (*u < 0.0f)
		*u = 0.0f;
	if (*u > 1.0f)
		*u = 1.0f;
	if (*v < 0.0f)
		*v = 0.0f;
	if (*v > 1.0f)
		*v = 1.0f;
}

t_vector3d	calculate_sphere_normal(t_sphere *sphere,
	t_vector3d point)
{
	t_vector3d	normal;
	float		radius;

	if (!sphere)
		return ((t_vector3d){0.0f, 0.0f, 0.0f});
	radius = sphere->diameter / 2.0f;
	normal = subtract_vectors(point, sphere->sphere_center);
	normal = scalar_multiplication(1.0f / radius, normal);
	return (normal);
}

t_vector3d	apply_bump_map(t_sphere *sphere, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_bumpmap	bump;

	if (!sphere || !bump_texture || !bump_texture->pixels)
		return (normal);
	if (bump_texture->width == 0 || bump_texture->height == 0)
		return (normal);
	uv_map(point, sphere, &bump.u, &bump.v);
	bump.texture_x = (int)(bump.u * (bump_texture->width - 1));
	bump.texture_y = (int)(bump.v * (bump_texture->height - 1));
	if (bump.texture_x < 0 || bump.texture_x >= (int)bump_texture->width
		|| bump.texture_y < 0 || bump.texture_y >= (int)bump_texture->height)
		return (normal);
	bump.i = (bump.texture_y * bump_texture->width + bump.texture_x) * 4;
	if (bump.i < 0 || bump.i + 2 >= (int)(bump_texture->width
		* bump_texture->height * 4))
		return (normal);
	bump.height_value = bump_texture->pixels[bump.i];
	bump.bump_strength = 0.5f;
	bump.x1 = bump.texture_x + 1;
	bump.y1 = bump.texture_y + 1;
	if (bump.x1 >= (int)bump_texture->width)
		bump.x1 = bump.texture_x;
	if (bump.y1 >= (int)bump_texture->height)
		bump.y1 = bump.texture_y;
	bump.i1 = (bump.texture_y * bump_texture->width + bump.x1) * 4;
	bump.i2 = (bump.y1 * bump_texture->width + bump.texture_x) * 4;
	if (bump.i1 < 0 || bump.i1 >= (int)(bump_texture->width
		* bump_texture->height * 4) || bump.i2 < 0
			|| bump.i2 >= (int)(bump_texture->width * bump_texture->height * 4))
		return (normal);
	bump.h1 = bump_texture->pixels[bump.i1];
	bump.h2 = bump_texture->pixels[bump.i2];
	bump.du = (float)(bump.h1 - bump.height_value)
		/ 255.0f * bump.bump_strength;
	bump.dv = (float)(bump.h2 - bump.height_value)
		/ 255.0f * bump.bump_strength;
	bump.tangent = (t_vector3d){-sinf(bump.u * 2 * M_PI), 0,
		cosf(bump.u * 2 * M_PI)};
	bump.bitangent = cross_product(normal, bump.tangent);
	bump.bump_normal = add_vectors(normal,
			scalar_multiplication(bump.du, bump.tangent));
	bump.bump_normal = add_vectors(bump.bump_normal,
			scalar_multiplication(bump.dv, bump.bitangent));
	return (normalize(bump.bump_normal));
}

t_intersec_info	intersect_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene)
{
	t_sphere_quad	quad;
	t_intersec_info	info;
	t_object		sphere_object;

	ft_bzero(&info, sizeof(t_intersec_info));
	if (!ray || !sphere)
		return (info);
	quad = intersect_sphere_quad(ray, sphere);
	if (!intersect_sphere_solution(quad, &info.dist_to_intersec))
		return (info);
	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(info.dist_to_intersec, ray->direction));
	info.normal = calculate_sphere_normal(sphere, info.intersec_point);
	if (sphere->bump_texture && sphere->bump_texture->pixels)
		info.normal = apply_bump_map(sphere, info.intersec_point,
				info.normal, sphere->bump_texture);
	if (sphere->has_checker)
	{
		init_sphere_struct(&sphere_object, sphere);
		info.color = object_pattern(info.intersec_point, &sphere_object, 10.0f);
	}
	else
		info.color = sphere->color;
	return (info);
}
