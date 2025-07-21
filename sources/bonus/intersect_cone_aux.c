/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/21 12:32:49 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static bool	compute_cone_intersection(t_ray *ray, t_cone *cone,
	t_cone_intersec *base, t_quadratic *quad)
{
	t_cone_projection	proj;
	bool				hit_surface;

	init_cone_projection(ray, cone, &proj, base);
	hit_surface = solve_cone_quadratic(&proj, cone, quad, ray);
	return (hit_surface && validate_cone_intersec(ray, cone, quad, base));
}

t_vector3d	insert_cone_bump_map(t_cone *cone, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_surface_mapping	bump;
	t_object			cone_object;

	init_cone_struct(&cone_object, cone);
	if (!init_bump_mapping(&cone_object, point, bump_texture, &bump))
		return (normal);
	if (!calculate_bump_gradients(bump_texture, &bump))
		return (normal);
	return (calc_vectors_cone(normal, &bump, cone));
}

static void	apply_cone_surface_effects(t_cone *cone,
	t_intersec_info *info)
{
	t_object	cone_object;

	if (cone->surface.bump_texture && cone->surface.bump_texture->pixels)
		info->normal = insert_cone_bump_map(cone, info->intersec_point,
				info->normal, cone->surface.bump_texture);
	if (cone->surface.has_checker)
	{
		init_cone_struct(&cone_object, cone);
		info->color = object_pattern(info->intersec_point, &cone_object,
				10.0f);
	}
	else
		info->color = cone->color;
	if (cone->surface.bump)
		info->normal = apply_bump_map(*info);
}

t_intersec_info	ray_intersects_cone_surface(t_ray *ray,
	t_cone *cone, t_cone_intersec *base)
{
	t_quadratic		quad;
	t_intersec_info	info;
	t_object		cone_object;

	ft_bzero(&info, sizeof(t_intersec_info));
	if (compute_cone_intersection(ray, cone, base, &quad))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cone_normal(cone, info.intersec_point, base);
		apply_cone_surface_effects(cone, &info);
	}
	return (info);
}
