/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/21 13:27:33 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

t_plane	create_cylinder_cap_plane(t_cylinder *cylinder, bool is_top_cap)
{
	t_vector3d	center;
	t_vector3d	normal;
	t_plane		plane;

	ft_bzero(&plane, sizeof(t_plane));
	normal = cylinder->vector;
	if (is_top_cap == false)
	{
		center = cylinder->cylinder_center;
		normal = scalar_multiplication(-1.0f, normal);
	}
	else
		center = add_vectors(cylinder->cylinder_center,
				scalar_multiplication(cylinder->height, cylinder->vector));
	plane.plane_point = center;
	plane.vector = normal;
	plane.color = cylinder->color;
	plane.surface = cylinder->surface;
	return (plane);
}

bool	is_intersection_within_cap_radius(t_vector3d intersection_point,
	t_vector3d cap_center, float cylinder_diameter)
{
	t_vector3d	delta;
	float		radius;
	float		distance_squared;

	delta = subtract_vectors(intersection_point, cap_center);
	radius = cylinder_diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	return (distance_squared <= radius * radius + EPSILON);
}

void	compute_cylinder_cap_intersections(t_ray *ray, t_cylinder *cylinder,
	t_intersec_info *bottom_cap, t_intersec_info *top_cap)
{
	bool	hit_bottom;
	bool	hit_top;

	ft_bzero(bottom_cap, sizeof(t_intersec_info));
	ft_bzero(top_cap, sizeof(t_intersec_info));
	hit_bottom = ray_intersects_cylinder_cap(ray, cylinder, false, bottom_cap);
	hit_top = ray_intersects_cylinder_cap(ray, cylinder, true, top_cap);
	if (!hit_bottom)
		bottom_cap->intersection = false;
	if (!hit_top)
		top_cap->intersection = false;
}

t_intersec_info	select_closest_intersection(
	t_intersec_info surface, t_intersec_info bottom_cap,
	t_intersec_info top_cap, t_rgb_color color)
{
	float				closest_distance;
	t_intersec_info		closest_intersection;

	closest_intersection.intersection = false;
	closest_distance = INFINITY;
	if (surface.intersection && surface.dist_to_intersec < closest_distance)
	{
		closest_distance = surface.dist_to_intersec;
		closest_intersection = surface;
	}
	if (bottom_cap.intersection && bottom_cap.dist_to_intersec
		< closest_distance)
	{
		closest_distance = bottom_cap.dist_to_intersec;
		closest_intersection = bottom_cap;
	}
	if (top_cap.intersection && top_cap.dist_to_intersec < closest_distance)
	{
		closest_distance = top_cap.dist_to_intersec;
		closest_intersection = top_cap;
	}
	return (closest_intersection);
}

t_intersec_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_intersec_info	surface_intersection;
	t_intersec_info	bottom_cap_intersection;
	t_intersec_info	top_cap_intersection;

	surface_intersection = ray_intersects_cylinder_surface(ray, cylinder);
	compute_cylinder_cap_intersections(ray, cylinder,
		&bottom_cap_intersection, &top_cap_intersection);
	return (select_closest_intersection(surface_intersection,
			bottom_cap_intersection, top_cap_intersection, cylinder->color));
}
