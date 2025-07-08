/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:30:07 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/08 11:30:07 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static t_rgb_color	checkerboard_pattern(float coord1, float coord2,
	float scale, t_object *object)
{
	int	x;
	int	y;

	x = floor(coord1 * scale);
	y = floor(coord2 * scale);

	if ((x + y) % 2 == 0)
		return (object->white);
	else
		return (object->black);
}

static void	get_sphere_coordinates(t_vector3d point, t_sphere *sphere,
	float *coord1, float *coord2)
{
	t_vector3d	local;

	local = normalize(subtract_vectors(point, sphere->sphere_center));
	*coord1 = 0.5f + atan2(local.z, local.x) / (2 * M_PI);
	*coord2 = 0.5f - asin(local.y) / M_PI;
}

static void	get_cylinder_coordinates(t_vector3d point, t_cylinder *cylinder,
	float *coord1, float *coord2)
{
	t_vector3d	center_to_intersection;
	float		height;
	t_vector3d	radial;

	center_to_intersection = subtract_vectors(point, cylinder->cylinder_center);
	height = dot_product(center_to_intersection, cylinder->vector);
	radial = subtract_vectors(center_to_intersection,
		scalar_multiplication(height, cylinder->vector));
	radial = normalize(radial);
	*coord1 = 0.5f + atan2(radial.z, radial.x) / (2 * M_PI);
	*coord2 = height / cylinder->height;
}

static void	get_cone_coordinates(t_vector3d point, t_cone *cone, float *coord1,
	float *coord2)
{
	t_vector3d	center_to_intersection;
	float		height;
	t_vector3d	radial;

	center_to_intersection = subtract_vectors(point, cone->cone_center);
	height = dot_product(center_to_intersection, cone->vector);
	radial = subtract_vectors(center_to_intersection,
		scalar_multiplication(height, cone->vector));
	radial = normalize(radial);
	*coord1 = 0.5f + atan2(radial.z, radial.x) / (2 * M_PI);
	*coord2 = height / cone->height;
}

t_rgb_color	checkerboard_object_pattern(t_vector3d point, t_object *object,
	float scale)
{
	float	coord1;
	float	coord2;

	if (object->type == SPHERE)
		get_sphere_coordinates(point, (t_sphere *)object->data, &coord1,
			&coord2);
	else if (object->type == PLANE)
	{
		coord1 = point.x;
		coord2 = point.z;
	}
	else if (object->type == CYLINDER)
		get_cylinder_coordinates(point, (t_cylinder *)object->data, &coord1,
			&coord2);
	else if (object->type == CONE)
		get_cone_coordinates(point, (t_cone *)object->data, &coord1, &coord2);
	else
	{
		coord1 = point.x;
		coord2 = point.z;
	}
	return (checkerboard_pattern(coord1, coord2, scale, object));
}

// t_rgb_color	checkerboard_plane_pattern(t_vector3d point, float scale, t_object *color)
// {
// 	return (checkerboard_pattern(point.x, point.z, scale, color));
// }

// t_rgb_color	checkerboard_sphere_pattern(t_vector3d point, t_sphere *sphere,
// 	float scale, t_object *color)
// {
// 	float	coord1;
// 	float	coord2;

// 	get_sphere_coordinates(point, sphere, &coord1, &coord2);
// 	return (checkerboard_pattern(coord1, coord2, scale, color));
// }

// t_rgb_color	checkerboard_cylinder_pattern(t_vector3d point,
// 	t_cylinder *cylinder, float scale, t_object *color)
// {
// 	float	coord1;
// 	float	coord2;

// 	get_cylinder_coordinates(point, cylinder, &coord1, &coord2);
// 	return (checkerboard_pattern(coord1, coord2, scale, color));
// }

// t_rgb_color	checkerboard_cone_pattern(t_vector3d point, t_cone *cone,
// 	float scale, t_object *color)
// {
// 	float	coord1;
// 	float	coord2;

// 	get_cone_coordinates(point, cone, &coord1, &coord2);
// 	return (checkerboard_pattern(coord1, coord2, scale, color));
// }
