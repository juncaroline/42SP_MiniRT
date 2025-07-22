/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_calc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:29:15 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/21 16:03:13 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

float	compute_cylinder_u_coord(t_surface_mapping mapping)
{
	float		u;
	t_vector3d	radial_normalized;
	t_vector3d	radial;
	float		radial_length;

	radial = mapping.local;
	radial_length = mapping.du;
	if (radial_length < EPSILON)
		return (0.0f);
	radial_normalized = scalar_multiplication(1.0f / radial_length, radial);
	mapping.theta = atan2f(dot_product(radial_normalized, mapping.bitangent),
			dot_product(radial_normalized, mapping.tangent));
	u = (mapping.theta + M_PI) / (2.0f * M_PI);
	if (u < 0.0f)
		u += 1.0f;
	if (u > 1.0f)
		u -= 1.0f;
	return (u);
}

float	compute_cylinder_v_coord(t_surface_mapping mapping,
	t_cylinder *cylinder)
{
	float	v;

	v = (mapping.height + cylinder->height / 2.0f) / cylinder->height;
	if (v < 0.0f)
		v = 0.0f;
	if (v > 1.0f)
		v = 1.0f;
	return (v);
}

static void	setup_cone_tangent_space(t_surface_mapping *mapping,
	t_vector3d axis)
{
	if (fabsf(axis.y) < 0.9f)
		mapping->tangent = normalize(cross_product(axis,
					(t_vector3d){0, 1, 0}));
	else
		mapping->tangent = normalize(cross_product(axis,
					(t_vector3d){1, 0, 0}));
	mapping->bitangent = cross_product(axis, mapping->tangent);
}

float	compute_cone_u_coord(t_surface_mapping mapping, t_vector3d axis)
{
	float		u;
	float		radial_length;
	t_vector3d	radial;

	radial = mapping.local;
	radial_length = mapping.du;
	if (radial_length < EPSILON)
		return (0.0f);
	setup_cone_tangent_space(&mapping, axis);
	radial = scalar_multiplication(1.0f / radial_length, radial);
	mapping.theta = atan2f(dot_product(radial, mapping.bitangent),
			dot_product(radial, mapping.tangent));
	u = (mapping.theta + M_PI) / (2.0f * M_PI);
	if (u < 0.0f)
		u += 1.0f;
	if (u > 1.0f)
		u -= 1.0f;
	return (u);
}

float	compute_cone_v_coord(t_surface_mapping mapping, t_cone *cone)
{
	float	v;

	v = mapping.height / cone->height;
	if (v < 0.0f)
		v = 0.0f;
	if (v > 1.0f)
		v = 1.0f;
	return (v);
}
