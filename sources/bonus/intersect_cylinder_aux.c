/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/10 15:38:08 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static void	init_cylinder_struct(t_object *object, t_cylinder *cylinder)
{
	object->type = CYLINDER;
	object->data = (void *)cylinder;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
}

static void	verify_has_checker(t_cylinder *cylinder, bool is_top_cap,
	t_intersec_info *info)
{
	t_object		cylinder_object;
	t_intersec_info	cap_info;
	float			coord1;
	float			coord2;

	init_cylinder_struct(&cylinder_object, cylinder);
	if (is_top_cap)
		get_top_cap_coord(info->intersec_point, cylinder,
			&coord1, &coord2);
	else
		get_bottom_cap_coord(info->intersec_point, cylinder,
			&coord1, &coord2);
	info->color = object_pattern(info->intersec_point,
			&cylinder_object, 10.0f);
}

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
	if (cylinder->has_checker)
		verify_has_checker(cylinder, is_top_cap, info);
	else
		info->color = cylinder->color;
	return (true);
}

static void	verify_intersection(t_ray *ray, t_cylinder *cylinder,
	t_cylinder_quad *quad, t_intersec_info *info)
{
	t_object				cylinder_object;

	info->intersection = true;
	info->dist_to_intersec = quad->t_hit;
	info->intersec_point = add_vectors(ray->origin,
			scalar_multiplication(quad->t_hit, ray->direction));
	info->normal = calculate_cylinder_normal(cylinder, info->intersec_point);
	if (cylinder->has_checker)
	{
		init_cylinder_struct(&cylinder_object, cylinder);
		info->color = object_pattern(info->intersec_point,
				&cylinder_object, 10.0f);
	}
	else
		info->color = cylinder->color;
}

t_intersec_info	ray_intersects_cylinder_surface(t_ray *ray,
	t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	t_intersec_info			info;
	bool					hit_surface;

	ft_bzero(&info, sizeof(t_intersec_info));
	init_cylinder_projection(ray, cylinder, &proj);
	hit_surface = solve_cylinder_quadratic(&proj, cylinder, &quad);
	if (hit_surface && validate_cylinder_intersec(ray, cylinder, &quad))
		verify_intersection(ray, cylinder, &quad, &info);
	return (info);
}
