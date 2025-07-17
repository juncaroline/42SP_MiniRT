/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:44:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/17 12:55:34 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static void	normalize_uv_coordinates(float *u, float *v)
{
	if (*u < 0.0f)
		*u += 1.0f;
	if (*u > 1.0f)
		*u -= 1.0f;
	if (*v < 0.0f)
		*v += 1.0f;
	if (*v > 1.0f)
		*v -= 1.0f;
}

void	uv_map_sphere(t_vector3d point, t_sphere *sphere, float *u,
	float *v)
{
	t_vector3d	local;

	if (!sphere || !u || !v)
		return ;
	local = normalize(subtract_vectors(point, sphere->sphere_center));
	*u = 0.5f + atan2f(local.z, local.x) / (2 * M_PI);
	*v = 0.5f - asinf(local.y) / M_PI;
	*u = fmodf(*u + 0.25f, 1.0f);
	*v = fmodf(*v + 0.0f, 1.0f);
	normalize_uv_coordinates(u, v);
}

void	uv_map_plane(t_vector3d point, t_plane *plane, float *u, float *v)
{
	t_vector3d	local;
	t_vector3d	temp;
	t_vector3d	tangent;
	t_vector3d	bitangent;

	if (!plane || !u || !v)
		return ;
	if (fabsf(plane->vector.x) > 0.9f)
		temp = (t_vector3d){0, 1, 0};
	else
		temp = (t_vector3d){1, 0, 0};
	tangent = normalize(cross_product(temp, plane->vector));
	bitangent = cross_product(plane->vector, tangent);
	local = subtract_vectors(point, plane->plane_point);
	*u = dot_product(local, tangent);
	*v = dot_product(local, bitangent);
	*u = fmodf(*u + 1000.0f, 2.0f) / 2.0f;
	*v = fmodf(*v + 1000.0f, 2.0f) / 2.0f;
}

void	uv_map_cylinder(t_vector3d point, t_cylinder *cylinder, float *u,
	float *v)
{
	t_vector3d	local;
	t_vector3d	projected;
	float		theta;
	float		height;
	float		radius;

	if (!cylinder || !u || !v)
		return ;
	local = subtract_vectors(point, cylinder->cylinder_center);
	height = dot_product(local, cylinder->vector);
	projected = subtract_vectors(local, scalar_multiplication(height,
				cylinder->vector));
	radius = sqrt(projected.x * projected.x + projected.y * projected.y
			+ projected.z * projected.z);
	if (radius > 0.0001f)
		projected = scalar_multiplication(1.0f / radius, projected);
	theta = atan2f(projected.z, projected.x);
	*u = (theta + M_PI) / (2.0f * M_PI);
	*u = fmodf(*u + 0.5f, 1.0f);
	*v = (height + cylinder->height / 2.0f) / cylinder->height;
	*v = fmodf(*v + 0.5f, 1.0f);
	normalize_uv_coordinates(u, v);
}

void	uv_map_cone(t_vector3d point, t_cone *cone, float *u, float *v)
{
	t_vector3d	local;
	t_vector3d	projected;
	float		theta;
	float		height;
	float		radius;

	if (!cone || !u || !v)
		return ;
	local = subtract_vectors(point, cone->cone_center);
	height = dot_product(local, cone->vector);
	projected = subtract_vectors(local, scalar_multiplication(height,
				cone->vector));
	radius = sqrt(projected.x * projected.x + projected.y * projected.y
			+ projected.z * projected.z);
	if (radius > 0.0001f)
		projected = scalar_multiplication(1.0f / radius, projected);
	theta = atan2f(projected.z, projected.x);
	*u = (theta + M_PI) / (2.0f * M_PI);
	*u = fmodf(*u + 0.5f, 1.0f);
	*v = height / cone->height;
	*v = fmodf(*v + 0.5f, 1.0f);
	normalize_uv_coordinates(u, v);
}
