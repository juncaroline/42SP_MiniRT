/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:57:49 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/01 14:15:18 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	compute_cone_cap_intersections(t_ray *ray, t_cone *cone,
	t_intersection_info *bottom_cap, t_intersection_info *top_cap)
{
	bool	hit_bottom;
	bool	hit_top;

	hit_bottom = ray_intersects_cone_cap(ray, cone, false, bottom_cap);
	hit_top = ray_intersects_cone_cap(ray, cone, true, top_cap);
	if (!hit_bottom)
		bottom_cap->intersection = false;
	if (!hit_top)
		top_cap->intersection = false;
}

t_intersection_info	select_closest_intersection(
	t_intersection_info surface, t_intersection_info bottom_cap,
	t_intersection_info top_cap, t_rgb_color color)
{
	float					closest_distance;
	t_intersection_info		closest_intersection;

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
	closest_intersection.color = color;
	return (closest_intersection);
}

t_intersection_info	intersect_cone(t_ray *ray, t_cone *cone)
{
	t_intersection_info	surface_intersection;
	t_intersection_info	bottom_cap_intersection;
	t_intersection_info	top_cap_intersection;

	surface_intersection = ray_intersects_cone_surface(ray, cone);
	compute_cone_cap_intersections(ray, cone,
		&bottom_cap_intersection, &top_cap_intersection);
	return (select_closest_intersection(surface_intersection,
			bottom_cap_intersection, top_cap_intersection, cone->color));
}
