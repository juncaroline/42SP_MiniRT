/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_calc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:46:24 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 15:32:08 by cabo-ram         ###   ########.fr       */
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
