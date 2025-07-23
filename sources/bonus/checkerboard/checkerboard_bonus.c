/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:30:07 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/08 11:30:07 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

void	get_plane_coordinates(t_vector3d point, t_plane *plane,
	float *u, float *v)
{
	t_surface_mapping	checker;
	t_vector3d			temp;
	float				scale_factor;

	checker.normal = normalize(plane->vector);
	if (fabsf(checker.normal.y) < 0.9f)
		temp = (t_vector3d){0, 1, 0};
	else
		temp = (t_vector3d){1, 0, 0};
	checker.tangent = normalize(cross_product(temp, checker.normal));
	checker.bitangent = cross_product(checker.normal, checker.tangent);
	checker.local = subtract_vectors(point, plane->plane_point);
	*u = dot_product(checker.local, checker.tangent);
	*v = dot_product(checker.local, checker.bitangent);
	scale_factor = 0.5f;
	*u = *u * scale_factor;
	*v = *v * scale_factor;
}

t_rgb_color	object_pattern(t_vector3d point, t_object *object,
	float scale)
{
	float	u;
	float	v;

	if (object->type == SPHERE)
		get_sphere_coordinates(point, (t_sphere *)object->data, &u, &v);
	else if (object->type == PLANE)
		get_plane_coordinates(point, (t_plane *)object->data, &u, &v);
	else if (object->type == CYLINDER)
		get_cylinder_coordinates(point, (t_cylinder *)object->data, &u, &v);
	else if (object->type == CONE)
		get_cone_coordinates(point, (t_cone *)object->data, &u, &v);
	else
	{
		u = point.x;
		v = point.z;
	}
	return (checkerboard_pattern(u, v, scale, object));
}
