/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/07 08:39:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	init_cone_base(t_cone *cone, t_cone_intersec *base)
{
	if (!cone || !base)
		return ;
	base->direction = normalize(cone->vector);
	base->cone_vertex = add_vectors(cone->cone_center,
			scalar_multiplication(cone->height, base->direction));
}

void	init_cone_projection(t_ray *ray, t_cone *cone,
	t_cone_projection *proj, t_cone_intersec *base)
{
	init_cone_base(cone, base);
	proj->oc = subtract_vectors(ray->origin, base->cone_vertex);
	proj->v_dot_d = dot_product(ray->direction, base->direction);
	proj->oc_dot_d = dot_product(proj->oc, base->direction);
	proj->k = (cone->diameter / 2.0f) / cone->height;
	proj->k = proj->k * proj->k;
}

void	calculate_equation(t_cone_projection *proj, t_cone *cone,
	t_cone_quad *quad, t_ray *ray)
{
	quad->radius = cone->diameter / 2.0f;
	quad->cos_squared = (cone->height * cone->height)
		/ (cone->height * cone->height + quad->radius * quad->radius);
	quad->a = proj->v_dot_d * proj->v_dot_d - quad->cos_squared
		* dot_product(ray->direction, ray->direction);
	quad->b = 2.0f * (proj->v_dot_d * proj->oc_dot_d - quad->cos_squared
			* dot_product(ray->direction, proj->oc));
	quad->c = proj->oc_dot_d * proj->oc_dot_d - quad->cos_squared
		* dot_product(proj->oc, proj->oc);
}

bool	solve_cone_quadratic(t_cone_projection *proj,
	t_cone *cone, t_cone_quad *quad, t_ray *ray)
{
	if (!proj || !cone || !quad || !ray)
		return (false);
	calculate_equation(proj, cone, quad, ray);
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
	t_cone_quad *quad, t_cone_intersec *base)
{
	t_cone_intersec	intersec;
	t_vector3d		vector_from_vertex;

	init_cone_base(cone, base);
	intersec.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	vector_from_vertex = subtract_vectors(intersec.intersec_point, base->cone_vertex);
	intersec.height_projection = dot_product(vector_from_vertex, base->direction);
	if (intersec.height_projection > 0.0f || intersec.height_projection
		< -cone->height)
		return (false);
	return (true);
}

t_vector3d	calculate_cone_normal(t_cone *cone, t_vector3d point,
	t_cone_intersec *base)
{
	t_vector3d		normal;
	t_cone_intersec	intersec;
	t_cone_quad		quad;
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
