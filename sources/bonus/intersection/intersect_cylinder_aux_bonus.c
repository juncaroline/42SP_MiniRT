/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_aux_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 14:09:59 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

t_vector3d	insert_cylinder_bump_map(t_cylinder *cylinder, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_surface_mapping	bump;
	t_object			cylinder_object;

	ft_bzero(&bump, sizeof(t_surface_mapping));
	init_cylinder_struct(&cylinder_object, cylinder);
	if (!init_bump_mapping(&cylinder_object, point, bump_texture, &bump))
		return (normal);
	if (!calculate_bump_gradients(bump_texture, &bump))
		return (normal);
	return (calc_vectors_cylinder(normal, &bump, cylinder));
}

void	apply_cylinder_surface_effects(t_cylinder *cylinder,
	t_intersec_info *info)
{
	t_object	cylinder_object;
	t_vector3d	original_normal;

	original_normal = info->normal;
	if (cylinder->surface.has_checker)
	{
		init_cylinder_struct(&cylinder_object, cylinder);
		info->color = object_pattern(info->intersec_point, &cylinder_object,
				10.0f);
	}
	else
		info->color = cylinder->color;
	if (cylinder->surface.bump_texture
		&& cylinder->surface.bump_texture->pixels)
		info->normal = insert_cylinder_bump_map(cylinder, info->intersec_point,
				info->normal, cylinder->surface.bump_texture);
	if (cylinder->surface.bump)
		info->normal = apply_bump_map(*info);
}

t_vector3d	calculate_cap_uv_coordinates(t_cylinder *cylinder,
	t_intersec_info *info, bool is_top_cap)
{
	t_vector3d	center;
	t_vector3d	local;
	t_vector3d	u_axis;
	t_vector3d	v_axis;
	t_vector3d	uv;

	if (is_top_cap)
		center = add_vectors(cylinder->cylinder_center,
				scalar_multiplication(cylinder->height, cylinder->vector));
	else
		center = cylinder->cylinder_center;
	local = subtract_vectors(info->intersec_point, center);
	if (fabs(cylinder->vector.x) < 0.9f)
		u_axis = normalize(cross_product(cylinder->vector,
					(t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u_axis = normalize(cross_product(cylinder->vector,
					(t_vector3d){0.0f, 1.0f, 0.0f}));
	v_axis = cross_product(cylinder->vector, u_axis);
	uv.x = dot_product(local, u_axis);
	uv.y = dot_product(local, v_axis);
	uv.z = 0.0f;
	return (uv);
}

static void	verify_intersection(t_ray *ray, t_cylinder *cylinder,
	t_quadratic *quad, t_intersec_info *info)
{
	info->intersection = true;
	info->dist_to_intersec = quad->t_hit;
	info->intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	info->normal = calculate_cylinder_normal(cylinder, info->intersec_point);
	apply_cylinder_surface_effects(cylinder, info);
}

t_intersec_info	ray_intersects_cylinder_surface(t_ray *ray,
	t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_quadratic				quad;
	t_intersec_info			info;
	bool					hit_surface;

	ft_bzero(&info, sizeof(t_intersec_info));
	init_cylinder_projection(ray, cylinder, &proj);
	hit_surface = solve_cylinder_quadratic(&proj, cylinder, &quad);
	if (hit_surface && validate_cylinder_intersec(ray, cylinder, &quad))
		verify_intersection(ray, cylinder, &quad, &info);
	return (info);
}
