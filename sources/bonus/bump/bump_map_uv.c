/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:44:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/18 18:19:53 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	uv_map_sphere(t_vector3d point, t_sphere *sphere, float *u,
	float *v)
{
	t_vector3d	local;
	float		theta;
	float		phi;

	if (!sphere || !u || !v)
		return ;
	local = normalize(subtract_vectors(point, sphere->sphere_center));
	theta = atan2f(local.z, local.x);
	phi = asinf(local.y);
	*u = (theta + M_PI) / (2.0f * M_PI);
	*v = (phi + M_PI / 2.0f) / M_PI;
	if (*u < 0.0f)
		*u += 1.0f;
	if (*u > 1.0f)
		*u -= 1.0f;
	if (*v < 0.0f)
		*v = 0.0f;
	if (*v > 1.0f)
		*v = 1.0f;
}

void	uv_map_plane(t_vector3d point, t_plane *plane, float *u, float *v)
{
	t_surface_mapping	bump;
	float				scale_factor;

	if (!plane || !u || !v)
		return ;
	calculate_plane_uv(point, plane, &bump);
	*u = dot_product(bump.local, bump.tangent);
	*v = dot_product(bump.local, bump.bitangent);
	scale_factor = 0.1f;
	*u = *u * scale_factor;
	*v = *v * scale_factor;
	*u = *u - floorf(*u);
	*v = *v - floorf(*v);
	if (*u < 0.0f)
		*u += 1.0f;
	if (*v < 0.0f)
		*v += 1.0f;
}

void	uv_map_cylinder(t_vector3d point, t_cylinder *cylinder, float *u,
	float *v)
{
	t_surface_mapping	bump;

	if (!cylinder || !u || !v)
		return ;
	calculate_cylinder_uv(point, cylinder, &bump);
	*u = (bump.theta + M_PI) / (2.0f * M_PI);
	if (*u < 0.0f)
		*u += 1.0f;
	if (*u > 1.0f)
		*u -= 1.0f;
	*v = (bump.height + cylinder->height / 2.0f) / cylinder->height;
	if (*v < 0.0f)
		*v += 1.0f;
	if (*v > 1.0f)
		*v -= 1.0f;
}

void	uv_map_cone(t_vector3d point, t_cone *cone, float *u, float *v)
{
	t_surface_mapping	bump;

	if (!cone || !u || !v)
		return ;
	calculate_cone_uv(point, cone, &bump);
	*u = (bump.theta + M_PI) / (2.0f * M_PI);
	if (*u < 0.0f)
		*u += 1.0f;
	if (*u > 1.0f)
		*u -= 1.0f;
	*v = bump.height / cone->height;
	if (*v < 0.0f)
		*v = 0.0f;
	if (*v > 1.0f)
		*v = 1.0f;
}
