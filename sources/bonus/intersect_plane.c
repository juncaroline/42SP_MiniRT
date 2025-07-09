/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:15 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/08 16:41:38 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

t_vector3d	calculate_plane_normal(t_plane *plane, t_vector3d point)
{
	(void)point;
	return (normalize(plane->vector));
}

t_intersec_info	intersect_plane(t_ray *ray, t_plane *plane)
{
	t_intersec_info	info;
	float			denominator;
	float			numerator;
	t_vector3d		diff;
	t_object		plane_object;

	info.intersection = false;
	info.dist_to_intersec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.color = (t_rgb_color){0, 0, 0};
	info.object = NULL;
	diff = subtract_vectors(plane->plane_point, ray->origin);
	denominator = dot_product(ray->direction, plane->vector);
	if (fabs(denominator) < EPSILON)
		return (info);
	numerator = dot_product(diff, plane->vector);
	info.dist_to_intersec = numerator / denominator;
	if (info.dist_to_intersec < 0.0f)
		return (info);
	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(info.dist_to_intersec, ray->direction));
	info.normal = calculate_plane_normal(plane, info.intersec_point);
	if (plane->has_checker)
	{
		plane_object.type = PLANE;
		plane_object.data = (void *)plane;
		plane_object.white = (t_rgb_color){255, 255, 255};
		plane_object.black = (t_rgb_color){0, 0, 0};
		info.color = checkerboard_object_pattern(info.intersec_point,
				&plane_object, 1.0f);
	}
	else
		info.color = plane->color;
	return (info);
}
