/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:14:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/16 19:24:29 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

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

static void	verify_has_checker(t_cone *cone, t_intersec_info *info)
{
	t_object		cone_object;

	if (cone->has_checker)
	{
		init_cone_struct(&cone_object, cone);
		info->color = object_pattern(info->intersec_point,
				&cone_object, 10.0f);
	}
	else
		info->color = cone->color;
}

bool	ray_intersects_cone_cap(t_ray *ray, t_cone *cone,
	bool is_covered, t_intersec_info *info)
{
	t_plane			cap_plane;
	t_intersec_info	cap_info;
	t_vector3d		cap_center;
	t_cone_intersec	base;
	t_object		cone_object;

	if (is_covered == true)
		return (false);
	cap_plane = create_cone_plane(cone, is_covered, &base);
	cap_info = intersect_plane(ray, &cap_plane);
	if (!cap_info.intersection || cap_info.dist_to_intersec <= EPSILON)
		return (false);
	cap_center = cap_plane.plane_point;
	if (!is_intersection_within_cone_cap_radius(cap_info.intersec_point,
			cap_center, cone->diameter))
		return (false);
	*info = cap_info;
	verify_has_checker(cone, info);
	return (true);
}

static bool	compute_cone_intersection(t_ray *ray, t_cone *cone,
	t_cone_intersec *base, t_cone_quad *quad)
{
	t_cone_projection	proj;
	bool				hit_surface;

	init_cone_projection(ray, cone, &proj, base);
	hit_surface = solve_cone_quadratic(&proj, cone, quad, ray);
	return (hit_surface && validate_cone_intersec(ray, cone, quad, base));
}

t_vector3d	calculate_cone_bump_map(t_cone *cone, t_vector3d point,
	t_vector3d normal, mlx_texture_t *bump_texture)
{
	t_bumpmap	bump;
	t_object	cone_object;

	init_cone_struct(&cone_object, cone);
	if (!init_bump_mapping(&cone_object, point, bump_texture, &bump))
		return (normal);
	if (!calculate_bump_gradients(bump_texture, &bump))
		return (normal);
	return (calc_vectors_cone(normal, &bump, cone));
}

t_intersec_info	ray_intersects_cone_surface(t_ray *ray,
	t_cone *cone, t_cone_intersec *base)
{
	t_cone_quad			quad;
	t_intersec_info		info;
	t_object			cone_object;

	ft_bzero(&info, sizeof(t_intersec_info));
	if (compute_cone_intersection(ray, cone, base, &quad))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cone_normal(cone, info.intersec_point, base);
		if (cone->bump_texture && cone->bump_texture->pixels)
			info.normal = calculate_cone_bump_map(cone, info.intersec_point,
					info.normal, cone->bump_texture);
		if (cone->has_checker)
		{
			init_cone_struct(&cone_object, cone);
			info.color = object_pattern(info.intersec_point,
					&cone_object, 10.0f);
		}
		else
			info.color = cone->color;
	}
	return (info);
}
