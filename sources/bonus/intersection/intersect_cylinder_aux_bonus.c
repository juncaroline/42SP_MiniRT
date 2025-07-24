/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_aux_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 12:06:04 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

bool	ray_intersects_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
	bool is_top_cap, t_intersec_info *info)
{
	t_plane			plane;
	t_intersec_info	cap_info;

	plane = create_cylinder_cap_plane(cylinder, is_top_cap);
	cap_info = intersect_plane(ray, &plane);
	if (cap_info.intersection == false || cap_info.dist_to_intersec <= EPSILON)
		return (false);
	if (!is_intersection_within_cap_radius(cap_info.intersec_point,
			plane.plane_point, cylinder->diameter))
		return (false);
	*info = cap_info;
	apply_cylinder_cap_effects(cylinder, info, is_top_cap);
	return (true);
}

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

	// Salva a normal original antes de qualquer modificação
	original_normal = info->normal;
	
	// Aplica primeiro o checkerboard com a normal original
	if (cylinder->surface.has_checker)
	{
		init_cylinder_struct(&cylinder_object, cylinder);
		info->color = object_pattern(info->intersec_point, &cylinder_object,
				10.0f);
	}
	else
		info->color = cylinder->color;
	
	// Depois aplica os efeitos de bump mapping
	if (cylinder->surface.bump_texture && cylinder->surface.bump_texture->pixels)
		info->normal = insert_cylinder_bump_map(cylinder, info->intersec_point,
				info->normal, cylinder->surface.bump_texture);
	if (cylinder->surface.bump)
		info->normal = apply_bump_map(*info);
}

void	apply_cylinder_cap_effects(t_cylinder *cylinder, t_intersec_info *info,
	bool is_top_cap)
{
	t_object	cylinder_object;
	t_vector3d	center;
	t_vector3d	local;
	float		u, v, radius, distance, angle;

	// Aplica primeiro o checkerboard usando coordenadas polares para a base
	if (cylinder->surface.has_checker)
	{
		init_cylinder_struct(&cylinder_object, cylinder);
		
		// Calcula o centro da base
		if (is_top_cap)
			center = add_vectors(cylinder->cylinder_center,
					scalar_multiplication(cylinder->height, cylinder->vector));
		else
			center = cylinder->cylinder_center;
		
		// Converte para coordenadas polares
		local = subtract_vectors(info->intersec_point, center);
		radius = cylinder->diameter / 2.0f;
		distance = sqrtf(local.x * local.x + local.z * local.z) / radius;
		angle = atan2f(local.z, local.x);
		
		u = distance;
		v = (angle + M_PI) / (2.0f * M_PI);
		
		// Aplica checkerboard com as coordenadas polares
		info->color = checkerboard_pattern(u, v, 10.0f, &cylinder_object);
	}
	else
		info->color = cylinder->color;
	
	// Depois aplica os efeitos de bump mapping
	if (cylinder->surface.bump_texture
		&& cylinder->surface.bump_texture->pixels)
		info->normal = insert_cylinder_bump_map(cylinder,
				info->intersec_point, info->normal,
				cylinder->surface.bump_texture);
	if (cylinder->surface.bump)
		info->normal = apply_bump_map(*info);
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
