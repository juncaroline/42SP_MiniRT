/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:15 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/22 14:05:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

	info.intersection = false;
	info.dist_to_intersec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.over_point = (t_vector3d){0.0f, 0.0f, 0.0f};
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
	info.color = plane->color;
	return (info);
}
