/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/09 15:28:57 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static t_sphere_quad	intersect_sphere_quad(t_ray *ray, t_sphere *sphere)
{
	t_vector3d		l;
	t_sphere_quad	quad;

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

	if (quad.discriminant < 0.0f)
		return (false);
	if (quad.a == 0.0f || quad.discriminant < 0.0f || isnan(quad.discriminant))
		return (false);
	nearest = (-quad.b - sqrtf(quad.discriminant)) / (2.0f * quad.a);
	farther = (-quad.b + sqrtf(quad.discriminant)) / (2.0f * quad.a);
	if (nearest < 1e-4f && farther < 1e-4f)
		return (false);
	else if (nearest < 1e-4f)
		*t = farther;
	else if (farther < 1e-4f)
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

	radius = sphere->diameter / 2.0f;
	normal = subtract_vectors(point, sphere->sphere_center);
	normal = scalar_multiplication(1.0f / radius, normal);
	return (normal);
}

t_intersec_info	intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_sphere_quad	quad;
	t_intersec_info	info;
	t_object		sphere_object;

	info.intersection = false;
	info.dist_to_intersec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.color = (t_rgb_color){0, 0, 0};
	info.object = NULL;
	quad = intersect_sphere_quad(ray, sphere);
	if (!intersect_sphere_solution(quad, &info.dist_to_intersec))
		return (info);
	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(info.dist_to_intersec, ray->direction));
	info.normal = calculate_sphere_normal(sphere, info.intersec_point);
	if (sphere->has_checker)
	{
		sphere_object.type = SPHERE;
		sphere_object.data = (void *)sphere;
		sphere_object.white = (t_rgb_color){255, 255, 255};
		sphere_object.black = (t_rgb_color){0, 0, 0};
		info.color = checkerboard_object_pattern(info.intersec_point,
				&sphere_object, 1.0f);
	}
	else
		info.color = sphere->color;
	return (info);
}
