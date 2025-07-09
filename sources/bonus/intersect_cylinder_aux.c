/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/09 17:30:24 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

t_plane	create_cylinder_cap_plane(t_cylinder *cylinder, bool is_top_cap)
{
	t_vector3d	center;
	t_vector3d	normal;
	t_plane		plane;

	ft_bzero(&plane, sizeof(t_plane));
	normal = cylinder->vector;
	if (is_top_cap == false)
	{
		center = cylinder->cylinder_center;
		normal = scalar_multiplication(-1.0f, normal);
	}
	else
		center = add_vectors(cylinder->cylinder_center,
				scalar_multiplication(cylinder->height, cylinder->vector));
	plane.plane_point = center;
	plane.vector = normal;
	plane.color = cylinder->color;
	plane.has_checker = false;
	return (plane);
}

bool	is_intersection_within_cap_radius(t_vector3d intersection_point,
	t_vector3d cap_center, float cylinder_diameter)
{
	t_vector3d	delta;
	float		radius;
	float		distance_squared;

	delta = subtract_vectors(intersection_point, cap_center);
	radius = cylinder_diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	return (distance_squared <= radius * radius + EPSILON);
}

static void	get_top_cap_coordinates(t_vector3d point, t_cylinder *cylinder,
	float *coord1, float *coord2)
{
	t_vector3d	center;
	t_vector3d	local;
	t_vector3d	u;
	t_vector3d	v;
	float		radius;

	center = add_vectors(cylinder->cylinder_center,
		scalar_multiplication(cylinder->height, cylinder->vector));
	local = subtract_vectors(point, center);
	radius = cylinder->diameter / 2.0f;
	if (fabs(cylinder->vector.x) < 0.9f)
		u = normalize(cross_product(cylinder->vector, (t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u = normalize(cross_product(cylinder->vector, (t_vector3d){0.0f, 1.0f, 0.0f}));
	v = cross_product(cylinder->vector, u);
	*coord1 = dot_product(local, u) / radius;
	*coord2 = dot_product(local, v) / radius;
}

static void	get_bottom_cap_coordinates(t_vector3d point, t_cylinder *cylinder,
	float *coord1, float *coord2)
{
	t_vector3d	local;
	t_vector3d	u;
	t_vector3d	v;
	float		radius;

	local = subtract_vectors(point, cylinder->cylinder_center);
	radius = cylinder->diameter / 2.0f;
	if (fabs(cylinder->vector.x) < 0.9f)
		u = normalize(cross_product(cylinder->vector, (t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u = normalize(cross_product(cylinder->vector, (t_vector3d){0.0f, 1.0f, 0.0f}));
	v = cross_product(cylinder->vector, u);
	*coord1 = dot_product(local, u) / radius;
	*coord2 = dot_product(local, v) / radius;
}

bool	ray_intersects_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
	bool is_top_cap, t_intersec_info *info)
{
	t_plane			plane;
	t_intersec_info	cap_info;
	t_object		cylinder_object;
	float			coord1;
	float			coord2;

	plane = create_cylinder_cap_plane(cylinder, is_top_cap);
	cap_info = intersect_plane(ray, &plane);
	if (cap_info.intersection == false || cap_info.dist_to_intersec <= EPSILON)
		return (false);
	if (!is_intersection_within_cap_radius(cap_info.intersec_point,
			plane.plane_point, cylinder->diameter))
		return (false);
	*info = cap_info;
	if (cylinder->has_checker)
	{
		cylinder_object.type = CYLINDER;
		cylinder_object.data = (void *)cylinder;
		cylinder_object.white = (t_rgb_color){255, 255, 255};
		cylinder_object.black = (t_rgb_color){0, 0, 0};
		if (is_top_cap)
			get_top_cap_coordinates(cap_info.intersec_point, cylinder,
				&coord1, &coord2);
		else
			get_bottom_cap_coordinates(cap_info.intersec_point, cylinder,
				&coord1, &coord2);
		info->color = checkerboard_object_pattern(cap_info.intersec_point,
				&cylinder_object, 10.0f);
	}
	else
		info->color = cylinder->color;
	return (true);
}

t_intersec_info	ray_intersects_cylinder_surface(t_ray *ray,
	t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	t_intersec_info			info;
	bool					hit_surface;
	t_object				cylinder_object;

	ft_bzero(&info, sizeof(t_intersec_info));
	init_cylinder_projection(ray, cylinder, &proj);
	hit_surface = solve_cylinder_quadratic(&proj, cylinder, &quad);
	if (hit_surface && validate_cylinder_intersec(ray, cylinder, &quad))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cylinder_normal(cylinder, info.intersec_point);
		if (cylinder->has_checker)
		{
			cylinder_object.type = CYLINDER;
			cylinder_object.data = (void *)cylinder;
			cylinder_object.white = (t_rgb_color){255, 255, 255};
			cylinder_object.black = (t_rgb_color){0, 0, 0};
			info.color = checkerboard_object_pattern(info.intersec_point,
					&cylinder_object, 10.0f);
		}
		else
			info.color = cylinder->color;
	}
	return (info);
}
