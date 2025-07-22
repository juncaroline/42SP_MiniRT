/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_uv_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:00:54 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/18 18:21:48 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	calculate_plane_uv(t_vector3d point, t_plane *plane,
	t_surface_mapping *bump)
{
	t_vector3d	temp;

	bump->normal = normalize(plane->vector);
	if (fabsf(bump->normal.y) < 0.9f)
		temp = (t_vector3d){0, 1, 0};
	else
		temp = (t_vector3d){1, 0, 0};
	bump->tangent = normalize(cross_product(temp, bump->normal));
	bump->bitangent = cross_product(bump->normal, bump->tangent);
	bump->local = subtract_vectors(point, plane->plane_point);
}

void	calculate_cylinder_uv(t_vector3d point, t_cylinder *cylinder,
	t_surface_mapping *bump)
{
	t_vector3d	axis;
	t_vector3d	projected;
	float		radius;

	axis = normalize(cylinder->vector);
	bump->local = subtract_vectors(point, cylinder->cylinder_center);
	bump->height = dot_product(bump->local, axis);
	projected = subtract_vectors(bump->local,
			scalar_multiplication(bump->height, axis));
	radius = sqrt(dot_product(projected, projected));
	if (fabsf(axis.y) < 0.9f)
		bump->tangent = normalize(cross_product(axis, (t_vector3d){0, 1, 0}));
	else
		bump->tangent = normalize(cross_product(axis, (t_vector3d){1, 0, 0}));
	bump->bitangent = cross_product(axis, bump->tangent);
	if (radius > 0.0001f)
	{
		projected = scalar_multiplication(1.0f / radius, projected);
		bump->theta = atan2f(dot_product(projected, bump->bitangent),
				dot_product(projected, bump->tangent));
	}
	else
		bump->theta = 0.0f;
}

void	calculate_cone_uv(t_vector3d point, t_cone *cone,
	t_surface_mapping *bump)
{
	t_vector3d	axis;
	t_vector3d	projected;
	float		radius;

	axis = normalize(cone->vector);
	bump->local = subtract_vectors(point, cone->cone_center);
	bump->height = dot_product(bump->local, axis);
	projected = subtract_vectors(bump->local,
			scalar_multiplication(bump->height, axis));
	radius = sqrt(dot_product(projected, projected));
	if (fabsf(axis.y) < 0.9f)
		bump->tangent = normalize(cross_product(axis, (t_vector3d){0, 1, 0}));
	else
		bump->tangent = normalize(cross_product(axis, (t_vector3d){1, 0, 0}));
	bump->bitangent = cross_product(axis, bump->tangent);
	if (radius > 0.0001f)
	{
		projected = scalar_multiplication(1.0f / radius, projected);
		bump->theta = atan2f(dot_product(projected, bump->bitangent),
				dot_product(projected, bump->tangent));
	}
	else
		bump->theta = 0.0f;
}
