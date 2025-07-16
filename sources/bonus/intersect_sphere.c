/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/16 19:30:44 by cabo-ram         ###   ########.fr       */
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

t_vector3d	calculate_sphere_bump_map(t_sphere *sphere, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_bumpmap	bump;
	t_object	sphere_object;

	init_sphere_struct(&sphere_object, sphere);
	if (!init_bump_mapping(&sphere_object, point, bump_texture, &bump))
		return (normal);
	if (!calculate_bump_gradients(bump_texture, &bump))
		return (normal);
	return (calc_vectors_sphere(normal, &bump));
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
		info.normal = calculate_sphere_bump_map(sphere, info.intersec_point,
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
