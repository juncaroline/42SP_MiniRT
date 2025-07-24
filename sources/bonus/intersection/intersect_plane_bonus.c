/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:15 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 13:45:01 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

t_vector3d	calculate_plane_normal(t_plane *plane, t_vector3d point)
{
	(void)point;
	return (normalize(plane->vector));
}

static void	init_plane_struct(t_object *object, t_plane *plane)
{
	object->type = PLANE;
	object->data = (void *)plane;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
}

static void	apply_plane_surface_effects(t_plane *plane, t_intersec_info *info)
{
	t_object	plane_object;
	t_vector3d	original_normal;

	original_normal = info->normal;
	if (plane->surface.has_checker)
	{
		init_plane_struct(&plane_object, plane);
		info->color = object_pattern(info->intersec_point,
				&plane_object, 1.0f);
	}
	else
		info->color = plane->color;
	if (plane->surface.bump_texture && plane->surface.bump_texture->pixels)
		info->normal = insert_plane_bump_map(plane, info->intersec_point,
				info->normal, plane->surface.bump_texture);
	if (plane->surface.bump)
		info->normal = apply_bump_map(*info);
}

t_vector3d	insert_plane_bump_map(t_plane *plane, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_surface_mapping	bump;
	t_object			plane_object;

	ft_bzero(&bump, sizeof(t_surface_mapping));
	init_plane_struct(&plane_object, plane);
	if (!init_bump_mapping(&plane_object, point, bump_texture, &bump))
		return (normal);
	if (!calculate_bump_gradients(bump_texture, &bump))
		return (normal);
	return (calc_vectors_plane(normal, &bump));
}

t_intersec_info	intersect_plane(t_ray *ray, t_plane *plane)
{
	t_intersec_info	info;
	float			denominator;
	float			numerator;
	t_vector3d		diff;
	t_object		plane_object;

	ft_bzero(&info, sizeof(t_intersec_info));
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
	apply_plane_surface_effects(plane, &info);
	return (info);
}
