/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_aux2_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:22:30 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 14:10:08 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

void	init_cylinder_struct(t_object *object, t_cylinder *cylinder)
{
	object->type = CYLINDER;
	object->data = (void *)cylinder;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
}

void	get_top_cap_coord(t_vector3d point, t_cylinder *cylinder,
	float *coord1, float *coord2)
{
	t_vector3d	center;
	t_vector3d	local;
	t_vector3d	u;
	t_vector3d	v;
	float		radius;

	center = add_vectors(cylinder->cylinder_center,
			scalar_multiplication(cylinder->height, cylinder->vector));
	local = subtract_vectors(point, center);
	radius = cylinder->diameter / 2.0f;
	if (fabs(cylinder->vector.x) < 0.9f)
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){0.0f, 1.0f, 0.0f}));
	v = cross_product(cylinder->vector, u);
	*coord1 = dot_product(local, u) / radius;
	*coord2 = dot_product(local, v) / radius;
}

void	get_bottom_cap_coord(t_vector3d point, t_cylinder *cylinder,
	float *coord1, float *coord2)
{
	t_vector3d	local;
	t_vector3d	u;
	t_vector3d	v;
	float		radius;

	local = subtract_vectors(point, cylinder->cylinder_center);
	radius = cylinder->diameter / 2.0f;
	if (fabs(cylinder->vector.x) < 0.9f)
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){1.0f, 0.0f, 0.0f}));
	else
		u = normalize(cross_product(cylinder->vector,
					(t_vector3d){0.0f, 1.0f, 0.0f}));
	v = cross_product(cylinder->vector, u);
	*coord1 = dot_product(local, u) / radius;
	*coord2 = dot_product(local, v) / radius;
}

void	apply_cylinder_cap_effects(t_cylinder *cylinder, t_intersec_info *info,
	bool is_top_cap)
{
	t_object	cylinder_object;
	t_vector3d	uv_coords;

	if (cylinder->surface.has_checker)
	{
		init_cylinder_struct(&cylinder_object, cylinder);
		uv_coords = calculate_cap_uv_coordinates(cylinder, info, is_top_cap);
		info->color = checkerboard_pattern(uv_coords.x, uv_coords.y, 2.0f,
				&cylinder_object);
	}
	else
		info->color = cylinder->color;
	if (cylinder->surface.bump_texture
		&& cylinder->surface.bump_texture->pixels)
		info->normal = insert_cylinder_bump_map(cylinder,
				info->intersec_point, info->normal,
				cylinder->surface.bump_texture);
	if (cylinder->surface.bump)
		info->normal = apply_bump_map(*info);
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
	apply_cylinder_cap_effects(cylinder, info, is_top_cap);
	return (true);
}
