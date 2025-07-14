/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/14 19:02:03 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static t_sphere_quad	intersect_sphere_quad(t_ray *ray, t_sphere *sphere)
{
	t_vector3d		l;
	t_sphere_quad	quad;

	if (!ray || !sphere)
	{
		ft_bzero(&quad, sizeof(t_sphere_quad));
		quad.discriminant = -1.0f; // Indica erro
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
		return;
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

t_vector3d	apply_bump_mapping(t_sphere *sphere, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	float		u;
	float		v;
	int			texture_x;
	int			texture_y;
	int			i;
	uint8_t		height_value;
	float		bump_strength;
	t_vector3d	tangent;
	t_vector3d	bitangent;
	t_vector3d	bump_normal;
	float		du;
	float		dv;
	int			x1;
	int			y1;
	uint8_t		h1;
	uint8_t		h2;

	if (!sphere || !bump_texture || !bump_texture->pixels)
		return (normal);
	if (bump_texture->width == 0 || bump_texture->height == 0)
		return (normal);
	uv_map(point, sphere, &u, &v);
	texture_x = (int)(u * (bump_texture->width - 1));
	texture_y = (int)(v * (bump_texture->height - 1));
	if (texture_x < 0 || texture_x >= (int)bump_texture->width ||
		texture_y < 0 || texture_y >= (int)bump_texture->height)
		return (normal);
	i = (texture_y * bump_texture->width + texture_x) * 4;
	if (i < 0 || i + 2 >= (int)(bump_texture->width * bump_texture->height * 4))
		return (normal);
	height_value = bump_texture->pixels[i];
	bump_strength = 0.3f;
	x1 = texture_x + 1;
	y1 = texture_y + 1;
	if (x1 >= (int)bump_texture->width)
		x1 = texture_x;
	if (y1 >= (int)bump_texture->height)
		y1 = texture_y;
	int i1 = (texture_y * bump_texture->width + x1) * 4;
	int i2 = (y1 * bump_texture->width + texture_x) * 4;
	if (i1 < 0 || i1 >= (int)(bump_texture->width * bump_texture->height * 4) ||
		i2 < 0 || i2 >= (int)(bump_texture->width * bump_texture->height * 4))
		return (normal);
	h1 = bump_texture->pixels[i1];
	h2 = bump_texture->pixels[i2];
	// printf("u: %.2f v: %.2f | h: %d h1: %d h2: %d | du: %.4f dv: %.4f\n",
	// 	u, v, height_value, h1, h2, du, dv);
	du = (float)(h1 - height_value) / 255.0f * bump_strength;
	dv = (float)(h2 - height_value) / 255.0f * bump_strength;
	tangent = (t_vector3d){-sinf(u * 2 * M_PI), 0, cosf(u * 2 * M_PI)};
	bitangent = cross_product(normal, tangent);
	bump_normal = add_vectors(normal, scalar_multiplication(du, tangent));
	bump_normal = add_vectors(bump_normal, scalar_multiplication(dv, bitangent));
	return (normalize(bump_normal));
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
	if (scene && scene->bump_texture && scene->bump_texture->pixels)
		info.normal = apply_bump_mapping(sphere, info.intersec_point, 
			info.normal, scene->bump_texture);
	if (sphere->has_checker)
	{
		sphere_object.type = SPHERE;
		sphere_object.data = (void *)sphere;
		sphere_object.white = (t_rgb_color){255, 255, 255};
		sphere_object.black = (t_rgb_color){0, 0, 0};
		info.color = object_pattern(info.intersec_point,
				&sphere_object, 10.0f);
	}
	else
		info.color = sphere->color;
	return (info);
}
