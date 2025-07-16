/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:48:57 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/16 19:31:33 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static void	uv_map_sphere(t_vector3d point, t_sphere *sphere, float *u,
	float *v)
{
	t_vector3d	local;

	if (!sphere || !u || !v)
		return ;
	local = normalize(subtract_vectors(point, sphere->sphere_center));
	*u = 0.5f + atan2f(local.z, local.x) / (2 * M_PI);
	*v = 0.5f - asinf(local.y) / M_PI;
	if (*u < 0.0f)
		*u = 0.0f;
	if (*u > 1.0f)
		*u = 1.0f;
	if (*v < 0.0f)
		*v = 0.0f;
	if (*v > 1.0f)
		*v = 1.0f;
}

static void	uv_map_plane(t_vector3d point, t_plane *plane, float *u, float *v)
{
	t_vector3d	local;
	t_vector3d	temp;
	t_vector3d	tangent;
	t_vector3d	bitangent;
	
	if (!plane || !u || !v)
		return ;
	if (fabsf(plane->vector.x) > 0.9f)
		temp = (t_vector3d){0, 1, 0};
	else
		temp = (t_vector3d){1, 0, 0};
	tangent = normalize(cross_product(temp, plane->vector));
	bitangent = cross_product(plane->vector, tangent);
	local = subtract_vectors(point, plane->plane_point);
	*u = dot_product(local, tangent);
	*v = dot_product(local, bitangent);
	*u = fmodf(*u + 1000.0f, 2.0f) / 2.0f;
	*v = fmodf(*v + 1000.0f, 2.0f) / 2.0f;
}

static void	uv_map_cylinder(t_vector3d point, t_cylinder *cylinder, float *u, float *v)
{
	t_vector3d	local;
	t_vector3d	projected;
	float		theta;
	float		height;
	
	if (!cylinder || !u || !v)
		return ;
	local = subtract_vectors(point, cylinder->cylinder_center);
	height = dot_product(local, cylinder->vector);
	projected = subtract_vectors(local, scalar_multiplication(height, cylinder->vector));
	theta = atan2f(projected.z, projected.x);
	*u = (theta + M_PI) / (2.0f * M_PI);
	*v = (height + cylinder->height / 2.0f) / cylinder->height;
	if (*u < 0.0f)
		*u = 0.0f;
	if (*u > 1.0f)
		*u = 1.0f;
	if (*v < 0.0f)
		*v = 0.0f;
	if (*v > 1.0f)
		*v = 1.0f;
}

static void	uv_map_cone(t_vector3d point, t_cone *cone, float *u, float *v)
{
	t_vector3d	local;
	t_vector3d	projected;
	float		theta;
	float		height;
	
	if (!cone || !u || !v)
		return ;
	local = subtract_vectors(point, cone->cone_center);
	height = dot_product(local, cone->vector);
	projected = subtract_vectors(local, scalar_multiplication(height, cone->vector));
	theta = atan2f(projected.z, projected.x);
	*u = (theta + M_PI) / (2.0f * M_PI);
	*v = height / cone->height;
	if (*u < 0.0f)
		*u = 0.0f;
	if (*u > 1.0f)
		*u = 1.0f;
	if (*v < 0.0f)
		*v = 0.0f;
	if (*v > 1.0f)
		*v = 1.0f;
}

static bool	get_uv_coordinates(t_object *object, t_vector3d point, float *u, float *v)
{
	if (!object || !u || !v)
		return (false);
	if (object->type == SPHERE)
		uv_map_sphere(point, (t_sphere *)object->data, u, v);
	else if (object->type == PLANE)
		uv_map_plane(point, (t_plane *)object->data, u, v);
	else if (object->type == CYLINDER)
		uv_map_cylinder(point, (t_cylinder *)object->data, u, v);
	else if (object->type == CONE)
		uv_map_cone(point, (t_cone *)object->data, u, v);
	else
		return (false);
	return (true);
}

bool	init_bump_mapping(t_object *object, t_vector3d point,
	mlx_texture_t *bump_texture, t_bumpmap *bump)
{
	if (!object || !bump_texture || !bump_texture->pixels)
		return (false);
	if (bump_texture->width == 0 || bump_texture->height == 0)
		return (false);
	if (!get_uv_coordinates(object, point, &bump->u, &bump->v))
		return (false);
	bump->texture_x = (int)(bump->u * (bump_texture->width - 1));
	bump->texture_y = (int)(bump->v * (bump_texture->height - 1));
	if (bump->texture_x < 0 || bump->texture_x >= (int)bump_texture->width
		|| bump->texture_y < 0 || bump->texture_y >= (int)bump_texture->height)
		return (false);
	bump->i = (bump->texture_y * bump_texture->width + bump->texture_x) * 4;
	if (bump->i < 0 || bump->i + 2 >= (int)(bump_texture->width
		* bump_texture->height * 4))
		return (false);
	bump->height_value = bump_texture->pixels[bump->i];
	bump->bump_strength = 1.0f;
	return (true);
}

bool	calculate_bump_gradients(mlx_texture_t *bump_texture, t_bumpmap *bump)
{
	bump->x1 = bump->texture_x + 1;
	bump->y1 = bump->texture_y + 1;
	if (bump->x1 >= (int)bump_texture->width)
		bump->x1 = bump->texture_x;
	if (bump->y1 >= (int)bump_texture->height)
		bump->y1 = bump->texture_y;
	bump->i1 = (bump->texture_y * bump_texture->width + bump->x1) * 4;
	bump->i2 = (bump->y1 * bump_texture->width + bump->texture_x) * 4;
	
	if (bump->i1 < 0 || bump->i1 >= (int)(bump_texture->width
		* bump_texture->height * 4) || bump->i2 < 0
			|| bump->i2 >= (int)(bump_texture->width * bump_texture->height * 4))
		return (false);
	bump->h1 = bump_texture->pixels[bump->i1];
	bump->h2 = bump_texture->pixels[bump->i2];
	
	bump->du = (float)(bump->h1 - bump->height_value)
		/ 255.0f * bump->bump_strength;
	bump->dv = (float)(bump->h2 - bump->height_value)
		/ 255.0f * bump->bump_strength;
	return (true);
}

t_vector3d	calc_vectors_sphere(t_vector3d normal, t_bumpmap *bump)
{
	bump->tangent = (t_vector3d){-sinf(bump->u * 2 * M_PI), 0,
		cosf(bump->u * 2 * M_PI)};
	bump->bitangent = cross_product(normal, bump->tangent);
	bump->bump_normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->bump_normal = add_vectors(bump->bump_normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->bump_normal));
}

t_vector3d	calc_vectors_plane(t_vector3d normal, t_bumpmap *bump)
{
	t_vector3d	temp;

	if (fabsf(normal.x) > 0.9f)
		temp = (t_vector3d){0, 1, 0};
	else
		temp = (t_vector3d){1, 0, 0};
	bump->tangent = normalize(cross_product(temp, normal));
	bump->bitangent = cross_product(normal, bump->tangent);
	bump->bump_normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->bump_normal = add_vectors(bump->bump_normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->bump_normal));
}

t_vector3d	calc_vectors_cylinder(t_vector3d normal, t_bumpmap *bump, t_cylinder *cylinder)
{
	bump->tangent = normalize(cross_product(bump->bitangent, normal));
	bump->bitangent = normalize(cylinder->vector);
	bump->bump_normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->bump_normal = add_vectors(bump->bump_normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->bump_normal));
}

t_vector3d	calc_vectors_cone(t_vector3d normal, t_bumpmap *bump, t_cone *cone)
{
	bump->tangent = normalize(cross_product(bump->bitangent, normal));
	bump->bitangent = normalize(cone->vector);
	bump->bump_normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->bump_normal = add_vectors(bump->bump_normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->bump_normal));
}
