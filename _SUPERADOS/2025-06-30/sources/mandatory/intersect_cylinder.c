/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 14:25:26 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector3d	calculate_cylinder_normal(t_cylinder *cylinder, t_vector3d point)
{
	t_vector3d	point_to_axis;
	t_vector3d	axis_point;
	t_vector3d	normal;
	t_vector3d	projection;
	float		length_squared;

	point_to_axis = subtract_vectors(point, cylinder->cylinder_center);
	axis_point = scalar_multiplication(dot_product(point_to_axis,
				cylinder->vector), cylinder->vector);
	normal = subtract_vectors(point_to_axis, axis_point);
	length_squared = dot_product(normal, normal);
	if (length_squared < CLOSE_TO_ZERO_EPSILON)
	{
		if (fabs(cylinder->vector.x) < 0.9)
			normal = (t_vector3d){1.0f, 0.0f, 0.0f};
		else
			normal = (t_vector3d){0.0f, 1.0f, 0.0f};
		projection = scalar_multiplication(dot_product(normal,
				cylinder->vector), cylinder->vector);
		normal = subtract_vectors(normal, projection);
	}
	normal = normalize(normal);
	return (normal);
}

t_intersection_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	t_intersection_info		info;
	t_intersection_info		cap_inf;
	t_intersection_info		cap_sup;
	bool					hit_lateral;
	bool					hit_cap_inf;
	bool					hit_cap_sup;
	float					best_dist;
	t_intersection_info		best_info;

	info.intersection = false;
	best_info.intersection = false;
	init_cylinder_projection(ray, cylinder, &proj);
	hit_lateral = solve_cylinder_quadratic(&proj, cylinder, &quad);
	if (hit_lateral && validate_cylinder_intersec(ray, cylinder, &quad))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cylinder_normal(cylinder, info.intersec_point);
	}
	hit_cap_inf = intersect_cylinder_cap(ray, cylinder, false, &cap_inf);
	hit_cap_sup = intersect_cylinder_cap(ray, cylinder, true, &cap_sup);
	best_dist = INFINITY;
	if (info.intersection && info.dist_to_intersec < best_dist)
	{
		best_dist = info.dist_to_intersec;
		best_info = info;
	}
	if (hit_cap_inf && cap_inf.dist_to_intersec < best_dist)
	{
		best_dist = cap_inf.dist_to_intersec;
		best_info = cap_inf;
	}
	if (hit_cap_sup && cap_sup.dist_to_intersec < best_dist)
	{
		best_dist = cap_sup.dist_to_intersec;
		best_info = cap_sup;
	}
	return (best_info);
}

// bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
// {
// 	t_cylinder_projection	proj;
// 	t_cylinder_quad			quad;
	
// 	init_cylinder_projection(ray, cylinder, &proj);
	
// 	if (!solve_cylinder_quadratic(&proj, cylinder, &quad))
// 		return (false);
	
// 	if (!validate_cylinder_intersec(ray, cylinder, &quad))
// 		return (false);
	
// 	*t = quad.t_hit;
// 	return (true);
// }
