/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:44:17 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/18 18:19:41 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

bool	init_bump_mapping(t_object *object, t_vector3d point,
	mlx_texture_t *bump_texture, t_surface_mapping *bump)
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

bool	calculate_bump_gradients(mlx_texture_t *bump_texture,
	t_surface_mapping *bump)
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
			|| bump->i2 >= (int)(bump_texture->width * bump_texture->height
				* 4))
		return (false);
	bump->h1 = bump_texture->pixels[bump->i1];
	bump->h2 = bump_texture->pixels[bump->i2];
	bump->du = (float)(bump->h1 - bump->height_value)
		/ 255.0f * bump->bump_strength;
	bump->dv = (float)(bump->h2 - bump->height_value)
		/ 255.0f * bump->bump_strength;
	return (true);
}

bool	get_uv_coordinates(t_object *object, t_vector3d point, float *u,
	float *v)
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

static void	free_texture(mlx_texture_t **bump_texture,
	char **texture_path)
{
	if (bump_texture && *bump_texture)
	{
		mlx_delete_texture(*bump_texture);
		*bump_texture = NULL;
	}
	if (texture_path && *texture_path)
	{
		free(*texture_path);
		*texture_path = NULL;
	}
}

void	free_object_texture(t_object *object)
{
	mlx_texture_t	**bump_texture;
	char			**texture_path;

	if (!object)
		return ;
	bump_texture = get_bump_texture(object);
	texture_path = get_texture_path(object);
	free_texture(bump_texture, texture_path);
}
