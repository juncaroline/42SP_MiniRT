/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_aux2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:12:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/17 12:50:48 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	init_cone_struct(t_object *object, t_cone *cone)
{
	object->type = CONE;
	object->data = (void *)cone;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
}

t_plane	create_cone_plane(t_cone *cone, bool is_covered, t_cone_intersec *base)
{
	t_vector3d	center;
	t_vector3d	normal;
	t_plane		plane;

	ft_bzero(&plane, sizeof(t_plane));
	init_cone_base(cone, base);
	normal = base->direction;
	if (is_covered == false)
	{
		center = cone->cone_center;
		normal = scalar_multiplication(-1.0f, normal);
	}
	else
	{
		center = base->cone_vertex;
		normal = normal;
	}
	plane.plane_point = center;
	plane.vector = normal;
	plane.color = cone->color;
	plane.has_checker = false;
	return (plane);
}

bool	is_intersection_within_cone_cap_radius(t_vector3d intersection_point,
	t_vector3d cap_center, float cone_diameter)
{
	t_vector3d	delta;
	float		radius;
	float		distance_squared;

	delta = subtract_vectors(intersection_point, cap_center);
	radius = cone_diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	return (distance_squared <= radius * radius + EPSILON);
}
