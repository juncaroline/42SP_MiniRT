/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:57:49 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 14:30:35 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

t_vector3d	calculate_cone_normal(t_cone *cone, t_vector3d point,
	t_cone_intersec *base)
{
	t_vector3d		normal;
	t_cone_intersec	intersec;
	t_quadratic		quad;
	t_vector3d		axis_component;
	t_vector3d		radial_component;

	init_cone_base(cone, base);
	intersec.vector_to_point = subtract_vectors(point, base->cone_vertex);
	intersec.height_projection = dot_product(intersec.vector_to_point,
			base->direction);
	quad.radius = cone->diameter / 2.0f;
	quad.cos_squared = (cone->height * cone->height)
		/ (cone->height * cone->height + quad.radius * quad.radius);
	axis_component = scalar_multiplication(intersec.height_projection,
			base->direction);
	radial_component = subtract_vectors(intersec.vector_to_point,
			axis_component);
	normal = subtract_vectors(radial_component,
			scalar_multiplication(quad.cos_squared * intersec.height_projection,
				base->direction));
	return (normalize(normal));
}

void	compute_cone_cap_intersections(t_ray *ray, t_cone *cone,
	t_intersec_info *bottom_cap, t_intersec_info *top_cap)
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

t_intersec_info	select_closest_intersection_cone(t_intersec_info surface_info,
	t_intersec_info base_info, t_intersec_info top_info)
{
	float				closest_distance;
	t_intersec_info		closest_intersection;

	ft_bzero(&closest_intersection, sizeof(t_intersec_info));
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
	return (closest_intersection);
}

t_intersec_info	intersect_cone(t_ray *ray, t_cone *cone)
{
	t_intersec_info	surface_info;
	t_intersec_info	base_info;
	t_intersec_info	top_info;
	t_cone_intersec	base;

	surface_info = ray_intersects_cone_surface(ray, cone, &base);
	compute_cone_cap_intersections(ray, cone, &base_info, &top_info);
	return (select_closest_intersection_cone(surface_info, base_info,
			top_info));
}
