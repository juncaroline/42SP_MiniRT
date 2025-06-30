/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 10:49:11 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
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

static bool	solve_cylinder_quadratic(t_cylinder_projection *proj,
	t_cylinder *cylinder, t_cylinder_quad *quad)
{
	quad->radius = cylinder->diameter / 2.0f;
	quad->a = dot_product(proj->d_perpendicular, proj->d_perpendicular);
	quad->b = 2.0f * dot_product(proj->d_perpendicular, proj->oc_perpendicular);
	quad->c = dot_product(proj->oc_perpendicular, proj->oc_perpendicular)
		- quad->radius * quad->radius;
	quad->discriminant = quad->b * quad->b - 4.0f * quad->a * quad->c;

	if (quad->discriminant < 0.0f)
		return (false);
	if (fabs(quad->a) < 1e-6)
		return (false);
	quad->sqrt_discriminant = sqrtf(quad->discriminant);
	quad->nearest = (-quad->b - quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->farther = (-quad->b + quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->t_hit = -1.0f;
	if (quad->nearest > 1e-6)
		quad->t_hit = quad->nearest;
	else if (quad->farther > 1e-6)
		quad->t_hit = quad->farther;
	else
		return (false);
	return (true);
}

static bool	validate_cylinder_intersec(t_ray *ray, t_cylinder *cylinder,
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

static bool	intersect_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
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
	if (cap_info.intersection == false || cap_info.dist_to_intersec <= 1e-6)
		return (false);
	delta = subtract_vectors(cap_info.intersec_point, center);
	radius = cylinder->diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	if (distance_squared > radius * radius + 1e-6)
		return (false);
	*info = cap_info;
	return (true);
}

t_vector3d	calculate_cylinder_normal(t_cylinder *cylinder, t_vector3d point)
{
	t_vector3d	point_to_axis;
	t_vector3d	axis_point;
	t_vector3d	normal;
	t_vector3d	projection;

	point_to_axis = subtract_vectors(point, cylinder->cylinder_center);
	axis_point = scalar_multiplication(dot_product(point_to_axis,
			cylinder->vector), cylinder->vector);
	normal = subtract_vectors(point_to_axis, axis_point);
	float length_squared = dot_product(normal, normal);
	printf("normal antes do fallback: ");
	print_vector("", normal);
	printf("length_squared: %f\n", length_squared);
	if (length_squared < 1e-12)
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

t_intersection_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	t_intersection_info		info;
	t_intersection_info		cap_inf;
	t_intersection_info		cap_sup;
	bool					hit_lateral;
	bool					hit_cap_inf;
	bool					hit_cap_sup;
	float					best_dist;
	t_intersection_info		best_info;

	info.intersection = false;
	best_info.intersection = false;
	init_cylinder_projection(ray, cylinder, &proj);
	hit_lateral = solve_cylinder_quadratic(&proj, cylinder, &quad);

	if (hit_lateral && validate_cylinder_intersec(ray, cylinder, &quad))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cylinder_normal(cylinder, info.intersec_point);
	}
	hit_cap_inf = intersect_cylinder_cap(ray, cylinder, false, &cap_inf);
	hit_cap_sup = intersect_cylinder_cap(ray, cylinder, true, &cap_sup);
	best_dist = INFINITY;
	if (info.intersection && info.dist_to_intersec < best_dist)
	{
		best_dist = info.dist_to_intersec;
		best_info = info;
	}
	if (hit_cap_inf && cap_inf.dist_to_intersec < best_dist)
	{
		best_dist = cap_inf.dist_to_intersec;
		best_info = cap_inf;
	}
	if (hit_cap_sup && cap_sup.dist_to_intersec < best_dist)
	{
		best_dist = cap_sup.dist_to_intersec;
		best_info = cap_sup;
	}
	return (best_info);
}

// bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
// {
// 	t_cylinder_projection	proj;
// 	t_cylinder_quad			quad;
	
// 	init_cylinder_projection(ray, cylinder, &proj);
	
// 	if (!solve_cylinder_quadratic(&proj, cylinder, &quad))
// 		return (false);
	
// 	if (!validate_cylinder_intersec(ray, cylinder, &quad))
// 		return (false);
	
// 	*t = quad.t_hit;
// 	return (true);
// }
