/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 14:09:26 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

t_vector3d	insert_sphere_bump_map(t_sphere *sphere, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_surface_mapping	bump;
	t_object			sphere_object;

	ft_bzero(&bump, sizeof(t_surface_mapping));
	init_sphere_struct(&sphere_object, sphere);
	if (!init_bump_mapping(&sphere_object, point, bump_texture, &bump))
		return (normal);
	if (!calculate_bump_gradients(bump_texture, &bump))
		return (normal);
	return (calc_vectors_sphere(normal, &bump));
}

static void	apply_sphere_surface_effects(t_sphere *sphere,
	t_intersec_info *info)
{
	t_object	sphere_object;
	t_vector3d	original_normal;

	original_normal = info->normal;
	if (sphere->surface.has_checker)
	{
		init_sphere_struct(&sphere_object, sphere);
		info->color = object_pattern(info->intersec_point, &sphere_object,
				10.0f);
	}
	else
		info->color = sphere->color;
	if (sphere->surface.bump_texture && sphere->surface.bump_texture->pixels)
		info->normal = insert_sphere_bump_map(sphere, info->intersec_point,
				info->normal, sphere->surface.bump_texture);
	if (sphere->surface.bump)
		info->normal = apply_bump_map(*info);
}

t_intersec_info	intersect_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene)
{
	t_quadratic		quad;
	t_intersec_info	info;

	ft_bzero(&info, sizeof(t_intersec_info));
	if (!ray || !sphere)
		return (info);
	quad = intersect_sphere_quad(ray, sphere);
	if (!intersect_sphere_solution(quad, &info.dist_to_intersec))
		return (info);
	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(info.dist_to_intersec, ray->direction));
	info.normal = calculate_sphere_normal(sphere, info.intersec_point);
	apply_sphere_surface_effects(sphere, &info);
	return (info);
}
