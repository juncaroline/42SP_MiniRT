/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/09 11:41:52 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	compute_cylinder_cap_intersections(t_ray *ray, t_cylinder *cylinder,
	t_intersec_info *bottom_cap, t_intersec_info *top_cap)
{
	bool	hit_bottom;
	bool	hit_top;

	bottom_cap->intersection = false;
	bottom_cap->dist_to_intersec = 0.0f;
	bottom_cap->intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	bottom_cap->normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	bottom_cap->color = (t_rgb_color){0, 0, 0};
	bottom_cap->object = NULL;
	top_cap->intersection = false;
	top_cap->dist_to_intersec = 0.0f;
	top_cap->intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	top_cap->normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	top_cap->color = (t_rgb_color){0, 0, 0};
	top_cap->object = NULL;
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
	float					closest_distance;
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
