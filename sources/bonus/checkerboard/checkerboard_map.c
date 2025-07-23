/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:36:16 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 10:27:24 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

t_rgb_color	checkerboard_pattern(float u, float v, float scale,
	t_object *object)
{
	int	x;
	int	y;

	x = floor(u * scale);
	y = floor(v * scale);
	if ((x + y) % 2 == 0)
		return (object->white);
	else
		return (object->black);
}

void	get_sphere_coordinates(t_vector3d point, t_sphere *sphere,
	float *u, float *v)
{
	t_vector3d	local;
	float		theta;
	float		phi;

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

void	get_cylinder_coordinates(t_vector3d point, t_cylinder *cylinder,
	float *u, float *v)
{
	t_vector3d			axis;
	t_vector3d			radial;
	t_surface_mapping	mapping;
	t_vector3d			center_to_intersection;
	float				radial_length;

	ft_bzero(&mapping, sizeof(t_surface_mapping));
	axis = normalize(cylinder->vector);
	center_to_intersection = subtract_vectors(point, cylinder->cylinder_center);
	mapping.height = dot_product(center_to_intersection, axis);
	radial = subtract_vectors(center_to_intersection,
			scalar_multiplication(mapping.height, axis));
	radial_length = sqrtf(dot_product(radial, radial));
	mapping.local = radial;
	mapping.du = radial_length;
	if (fabsf(axis.y) < 0.9f)
		mapping.tangent = normalize(cross_product(axis,
					(t_vector3d){0, 1, 0}));
	else
		mapping.tangent = normalize(cross_product(axis,
					(t_vector3d){1, 0, 0}));
	mapping.bitangent = cross_product(axis, mapping.tangent);
	*u = compute_cylinder_u_coord(mapping);
	*v = compute_cylinder_v_coord(mapping, cylinder);
}

void	get_cone_coordinates(t_vector3d point, t_cone *cone, float *u,
	float *v)
{
	t_surface_mapping	checker;
	t_vector3d			center_to_intersection;
	t_vector3d			radial;
	t_vector3d			axis;
	float				radial_length;

	ft_bzero(&checker, sizeof(t_surface_mapping));
	axis = normalize(cone->vector);
	center_to_intersection = subtract_vectors(point, cone->cone_center);
	checker.height = dot_product(center_to_intersection, axis);
	radial = subtract_vectors(center_to_intersection,
			scalar_multiplication(checker.height, axis));
	radial_length = sqrtf(dot_product(radial, radial));
	checker.local = radial;
	checker.du = radial_length;
	*u = compute_cone_u_coord(checker, axis);
	*v = compute_cone_v_coord(checker, cone);
}
