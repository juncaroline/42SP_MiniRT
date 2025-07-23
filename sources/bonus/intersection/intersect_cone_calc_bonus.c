/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_calc_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 14:30:33 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

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
	t_quadratic *quad, t_ray *ray)
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
	t_cone *cone, t_quadratic *quad, t_ray *ray)
{
	if (!proj || !cone || !quad || !ray)
		return (false);
	calculate_equation(proj, cone, quad, ray);
	return (solve_quadratic_equation(quad));
}

bool	validate_cone_intersec(t_ray *ray, t_cone *cone,
	t_quadratic *quad, t_cone_intersec *base)
{
	t_cone_intersec	intersec;
	t_vector3d		vector_from_vertex;

	init_cone_base(cone, base);
	intersec.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	vector_from_vertex = subtract_vectors(intersec.intersec_point,
			base->cone_vertex);
	intersec.height_projection = dot_product(vector_from_vertex,
			base->direction);
	if (intersec.height_projection > 0.0f || intersec.height_projection
		< -cone->height)
		return (false);
	return (true);
}
