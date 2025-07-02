/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:57:49 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/02 12:45:15 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	compute_cone_cap_intersections(t_ray *ray, t_cone *cone,
	t_intersection_info *bottom_cap, t_intersection_info *top_cap)
{
	bool	hit_base;
	bool	hit_top;

	hit_base = ray_intersects_cone_cap(ray, cone, false, bottom_cap);
	hit_top = ray_intersects_cone_cap(ray, cone, true, top_cap);
	if (!hit_base)
		bottom_cap->intersection = false;
	if (!hit_top)
		top_cap->intersection = false;
}

t_intersection_info	select_closest_intersection_cone(
	t_intersection_info surface_info, t_intersection_info base_info,
	t_intersection_info top_info, t_rgb_color color)
{
	float					closest_distance;
	t_intersection_info		closest_intersection;

	closest_intersection.intersection = false;
	closest_distance = INFINITY;
	if (surface_info.intersection && surface_info.dist_to_intersec
		< closest_distance)
	{
		closest_distance = surface_info.dist_to_intersec;
		closest_intersection = surface_info;
	}
	if (base_info.intersection && base_info.dist_to_intersec < closest_distance)
	{
		closest_distance = base_info.dist_to_intersec;
		closest_intersection = base_info;
	}
	if (top_info.intersection && top_info.dist_to_intersec < closest_distance)
	{
		closest_distance = top_info.dist_to_intersec;
		closest_intersection = top_info;
	}
	if (closest_intersection.intersection)
		closest_intersection.color = color;
	return (closest_intersection);
}

t_intersection_info	intersect_cone(t_ray *ray, t_cone *cone)
{
	t_intersection_info	surface_info;
	t_intersection_info	base_info;
	t_intersection_info	top_info;

	surface_info = ray_intersects_cone_surface(ray, cone);
	base_info.intersection = false;
	top_info.intersection = false;
	ray_intersects_cone_cap(ray, cone, false, &base_info);
	ray_intersects_cone_cap(ray, cone, true, &top_info);
	return (select_closest_intersection_cone(surface_info, base_info,
			top_info, cone->color));
}
