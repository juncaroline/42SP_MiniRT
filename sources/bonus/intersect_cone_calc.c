/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/01 19:05:41 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	init_cone_projection(t_ray *ray, t_cone *cone,
	t_cone_projection *proj)
{
	proj->oc = subtract_vectors(ray->origin, cone->cone_vertex);
	proj->v_dot_d = dot_product(ray->direction, cone->direction);
	proj->oc_dot_d = dot_product(proj->oc, cone->direction);
	proj->k = (cone->diameter / 2.0f) / cone->height;
	proj->k = proj->k * proj->k;
}

bool	solve_cone_quadratic(t_cone_projection *proj,
	t_cone *cone, t_cone_quad *quad, t_ray *ray)
{
	quad->a = dot_product(ray->direction, ray->direction) - (1 + proj->k)
		* (proj->v_dot_d * proj->v_dot_d);
	quad->b = 2.0f * (dot_product(ray->direction, proj->oc) - (1 + proj->k)
		* proj->v_dot_d * proj->oc_dot_d);
	quad->c = dot_product(proj->oc, proj->oc) - (1 + proj->k)
		* (proj->oc_dot_d * proj->oc_dot_d);
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

bool	validate_cone_intersec(t_ray *ray, t_cone *cone,
	t_cone_quad *quad)
{
	t_cone_intersec	intersec;

	intersec.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	intersec.vector_to_point = subtract_vectors(intersec.intersec_point,
			cone->cone_vertex);
	intersec.height_projection = dot_product(intersec.vector_to_point,
			cone->direction);
	if (intersec.height_projection < 0.0f || intersec.height_projection
		> cone->height)
		return (false);
	return (true);
}

t_vector3d	calculate_cone_normal(t_cone *cone, t_vector3d point)
{
	t_vector3d	point_to_axis;
	t_vector3d	axis_point;
	t_vector3d	normal;
	t_vector3d	projection;
	float		length_squared;

	point_to_axis = subtract_vectors(point, cone->cone_center);
	axis_point = scalar_multiplication(dot_product(point_to_axis,
				cone->vector), cone->vector);
	normal = subtract_vectors(point_to_axis, axis_point);
	length_squared = dot_product(normal, normal);
	if (length_squared < CLOSE_TO_ZERO_EPSILON)
	{
		if (fabs(cone->vector.x) < 0.9)
			normal = (t_vector3d){1.0f, 0.0f, 0.0f};
		else
			normal = (t_vector3d){0.0f, 1.0f, 0.0f};
		projection = scalar_multiplication(dot_product(normal,
					cone->vector), cone->vector);
		normal = subtract_vectors(normal, projection);
	}
	normal = normalize(normal);
	return (normal);
}
