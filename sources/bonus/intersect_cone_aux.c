/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/02 18:40:39 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

// t_plane	create_cone_cap_plane(t_cone *cone, bool is_covered, t_cone_base *base)
// {
// 	t_vector3d	center;
// 	t_vector3d	normal;
// 	t_plane		plane;

// 	normal = base->direction;
// 	if (is_covered == false)
// 	{
// 		center = base->cone_vertex;
// 		normal = scalar_multiplication(-1.0f, normal);
// 	}
// 	else
// 	{
// 		center = cone->cone_center;
// 		normal = normal;
// 	}
// 	plane.plane_point = center;
// 	plane.vector = normal;
// 	return (plane);
// }

// t_plane	create_cone_cap_plane(t_cone *cone, bool is_covered, t_cone_base *base)
// {
// 	t_vector3d	center;
// 	t_vector3d	normal;
// 	t_plane		plane;

// 	base->direction = normalize(cone->vector);
// 	// normal = base->direction;
// 	if (is_covered == false)
// 	{
// 		base->cone_vertex = subtract_vectors(cone->cone_center,
// 			scalar_multiplication(cone->height, base->direction));
// 	}
// 	else
// 	{
// 		base->cone_vertex = add_vectors(cone->cone_center,
// 			scalar_multiplication(cone->height, base->direction));
// 	}
// 	center = add_vectors(base->cone_vertex,
// 		scalar_multiplication(cone->height, base->direction));
// 	// plane.plane_point = center;
// 	// plane.vector = normal;
// 	return (plane);
// }

t_plane	create_cone_cap_plane(t_cone *cone, bool is_covered)
{
	t_vector3d	center;
	t_vector3d	normal;
	t_vector3d	cone_vertex;
	t_vector3d	direction;
	t_plane		plane;

	direction = normalize(cone->vector);
	cone_vertex = add_vectors(cone->cone_center, 
		scalar_multiplication(cone->height, direction));
	normal = direction;
	if (is_covered == false)
	{
		center = cone->cone_center;
		normal = scalar_multiplication(-1.0f, normal);
	}
	else
	{
		center = cone_vertex;
		normal = normal;
	}
	plane.plane_point = center;
	plane.vector = normal;
	return (plane);
}

bool	is_intersection_within_cone_cap_radius(t_vector3d intersection_point,
	t_vector3d cap_center, float cone_diameter)
{
	t_vector3d	delta;
	float		radius;
	float		distance_squared;

	delta = subtract_vectors(intersection_point, cap_center);
	radius = cone_diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	return (distance_squared <= radius * radius + EPSILON);
}

bool	ray_intersects_cone_cap(t_ray *ray, t_cone *cone,
	bool is_covered, t_intersection_info *info)
{
	t_plane				cap_plane;
	t_intersection_info	cap_info;
	t_vector3d			cap_center;
	t_cone_base			base;

	if (!ray || !cone || !info)
		return (false);
	init_cone_base(cone, &base);
	cap_plane = create_cone_cap_plane(cone, is_covered);
	cap_info = intersect_plane(ray, &cap_plane);
	if (!cap_info.intersection || cap_info.dist_to_intersec <= EPSILON)
		return (false);
	cap_center = cap_plane.plane_point;
	if (!is_intersection_within_cone_cap_radius(cap_info.intersec_point,
			cap_center, cone->diameter))
		return (false);
	*info = cap_info;
	return (true);
}

t_intersection_info	ray_intersects_cone_surface(t_ray *ray,
	t_cone *cone, t_cone_base *base)
{
	t_cone_projection	proj;
	t_cone_quad			quad;
	t_intersection_info	info;
	bool				hit_surface;
	t_cone_data			data;

	info.intersection = false;
	if (!ray || !cone || !base)
		return (info);
	data.cone = cone;
	data.base = *base;
	data.ray = ray;
	init_cone_projection(ray, cone, &proj, base);
	hit_surface = solve_cone_quadratic(&proj, cone, &quad, ray);
	if (hit_surface && validate_cone_intersec(&quad, &data))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cone_normal(cone, info.intersec_point,
				base, &quad);
	}
	return (info);
}
