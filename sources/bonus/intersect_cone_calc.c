/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/02 15:12:56 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	init_cone_projection(t_ray *ray, t_cone *cone,
	t_cone_projection *proj)
{
	t_vector3d	direction;
	t_vector3d	cone_vertex;

	direction = normalize(cone->vector);
	cone_vertex = add_vectors(cone->cone_center, 
		scalar_multiplication(cone->height, direction));
	proj->oc = subtract_vectors(ray->origin, cone_vertex);
	proj->v_dot_d = dot_product(ray->direction, direction);
	proj->oc_dot_d = dot_product(proj->oc, direction);
	proj->k = (cone->diameter / 2.0f) / cone->height;
	proj->k = proj->k * proj->k;
}

bool	solve_cone_quadratic(t_cone_projection *proj,
	t_cone *cone, t_cone_quad *quad, t_ray *ray)
{
	float	cos_squared;
	float	radius;
	
	radius = cone->diameter / 2.0f;
	cos_squared = (cone->height * cone->height) / 
		(cone->height * cone->height + radius * radius);
	quad->a = proj->v_dot_d * proj->v_dot_d - cos_squared * 
		dot_product(ray->direction, ray->direction);
	quad->b = 2.0f * (proj->v_dot_d * proj->oc_dot_d - cos_squared * 
		dot_product(ray->direction, proj->oc));
	quad->c = proj->oc_dot_d * proj->oc_dot_d - cos_squared * 
		dot_product(proj->oc, proj->oc);
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
	t_vector3d	cone_vertex;
	t_vector3d	direction;
	t_vector3d	vector_from_vertex;

	direction = normalize(cone->vector);
	cone_vertex = add_vectors(cone->cone_center, 
		scalar_multiplication(cone->height, direction));
	intersec.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	vector_from_vertex = subtract_vectors(intersec.intersec_point, cone_vertex);
	intersec.height_projection = dot_product(vector_from_vertex, direction);
	if (intersec.height_projection > 0.0f || intersec.height_projection < -cone->height)
		return (false);
	return (true);
}

t_vector3d	calculate_cone_normal(t_cone *cone, t_vector3d point)
{
	t_vector3d	vector_to_point;
	t_vector3d	normal;
	t_vector3d	direction;
	t_vector3d	cone_vertex;
	float		height_projection;
	float		cos_squared;
	t_vector3d	axis_component;
	t_vector3d	radial_component;

	direction = normalize(cone->vector);
	cone_vertex = add_vectors(cone->cone_center, 
		scalar_multiplication(cone->height, direction));
	vector_to_point = subtract_vectors(point, cone_vertex);
	height_projection = dot_product(vector_to_point, direction);
	float radius = cone->diameter / 2.0f;
	cos_squared = (cone->height * cone->height) / 
		(cone->height * cone->height + radius * radius);
	axis_component = scalar_multiplication(height_projection, direction);
	radial_component = subtract_vectors(vector_to_point, axis_component);
	normal = subtract_vectors(radial_component, 
		scalar_multiplication(cos_squared * height_projection, direction));
	
	return (normalize(normal));
}
