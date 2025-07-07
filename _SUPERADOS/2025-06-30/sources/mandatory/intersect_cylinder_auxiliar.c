/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_auxiliar.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:46:24 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/07 08:43:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
	t_cylinder_projection *proj)
{
	proj->oc = subtract_vectors(ray->origin, cylinder->cylinder_center);
	proj->oc_proj_v = dot_product(proj->oc, cylinder->vector);
	proj->oc_perpendicular = subtract_vectors(proj->oc,
			scalar_multiplication(proj->oc_proj_v, cylinder->vector));
	proj->d_proj_v = dot_product(ray->direction, cylinder->vector);
	proj->projected_d = scalar_multiplication(proj->d_proj_v,
			cylinder->vector);
	proj->d_perpendicular = subtract_vectors(ray->direction, proj->projected_d);
}

bool	solve_cylinder_quadratic(t_cylinder_projection *proj,
	t_cylinder *cylinder, t_cylinder_quad *quad)
{
	quad->radius = cylinder->diameter / 2.0f;
	quad->a = dot_product(proj->d_perpendicular, proj->d_perpendicular);
	quad->b = 2.0f * dot_product(proj->d_perpendicular, proj->oc_perpendicular);
	quad->c = dot_product(proj->oc_perpendicular, proj->oc_perpendicular)
		- quad->radius * quad->radius;
	quad->discriminant = quad->b * quad->b - 4.0f * quad->a * quad->c;
	if (quad->discriminant < EPSILON)
		return (false);
	if (fabs(quad->a) < EPSILON)
		return (false);
	quad->sqrt_discriminant = sqrtf(quad->discriminant);
	quad->nearest = (-quad->b - quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->farther = (-quad->b + quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->t_hit = -1.0f;
	if (quad->nearest > EPSILON)
		quad->t_hit = quad->nearest;
	else if (quad->farther > EPSILON)
		quad->t_hit = quad->farther;
	else
		return (false);
	return (true);
}

bool	validate_cylinder_intersec(t_ray *ray, t_cylinder *cylinder,
	t_cylinder_quad *quad)
{
	t_cylinder_intersec	intersec;

	intersec.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	intersec.vector_to_point = subtract_vectors(intersec.intersec_point,
			cylinder->cylinder_center);
	intersec.height_projection = dot_product(intersec.vector_to_point,
			cylinder->vector);
	if (intersec.height_projection < 0.0f || intersec.height_projection
		> cylinder->height)
		return (false);
	return (true);
}

bool	intersect_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
	bool top_cap, t_intersection_info *info)
{
	t_vector3d			center;
	t_vector3d			normal;
	t_plane				plane;
	t_intersection_info	cap_info;
	float				radius;
	t_vector3d			delta;
	float				distance_squared;

	normal = cylinder->vector;
	if (top_cap == false)
	{
		center = cylinder->cylinder_center;
		normal = scalar_multiplication(-1.0f, normal);
	}
	else
		center = add_vectors(cylinder->cylinder_center,
				scalar_multiplication(cylinder->height, cylinder->vector));
	plane.plane_point = center;
	plane.vector = normal;
	cap_info = intersect_plane(ray, &plane);
	if (cap_info.intersection == false || cap_info.dist_to_intersec <= EPSILON)
		return (false);
	delta = subtract_vectors(cap_info.intersec_point, center);
	radius = cylinder->diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	if (distance_squared > radius * radius + EPSILON)
		return (false);
	*info = cap_info;
	return (true);
}
