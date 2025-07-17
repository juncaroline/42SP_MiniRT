/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_aux2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:22:30 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/17 12:39:17 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	init_cylinder_struct(t_object *object, t_cylinder *cylinder)
{
	object->type = CYLINDER;
	object->data = (void *)cylinder;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
}

void	get_top_cap_coord(t_vector3d point, t_cylinder *cylinder,
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
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){0.0f, 1.0f, 0.0f}));
	v = cross_product(cylinder->vector, u);
	*coord1 = dot_product(local, u) / radius;
	*coord2 = dot_product(local, v) / radius;
}

void	get_bottom_cap_coord(t_vector3d point, t_cylinder *cylinder,
	float *coord1, float *coord2)
{
	t_vector3d	local;
	t_vector3d	u;
	t_vector3d	v;
	float		radius;

	local = subtract_vectors(point, cylinder->cylinder_center);
	radius = cylinder->diameter / 2.0f;
	if (fabs(cylinder->vector.x) < 0.9f)
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){0.0f, 1.0f, 0.0f}));
	v = cross_product(cylinder->vector, u);
	*coord1 = dot_product(local, u) / radius;
	*coord2 = dot_product(local, v) / radius;
}
