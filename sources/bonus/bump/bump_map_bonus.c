/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:37:33 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 12:10:19 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

mlx_texture_t	**get_bump_texture(t_object *object)
{
	void	*data;

	if (!object)
		return (NULL);
	data = object->data;
	if (object->type == SPHERE)
		return (&((t_sphere *)data)->surface.bump_texture);
	else if (object->type == PLANE)
		return (&((t_plane *)data)->surface.bump_texture);
	else if (object->type == CYLINDER)
		return (&((t_cylinder *)data)->surface.bump_texture);
	else if (object->type == CONE)
		return (&((t_cone *)data)->surface.bump_texture);
	return (NULL);
}

char	**get_texture_path(t_object *object)
{
	void	*data;

	if (!object)
		return (NULL);
	data = object->data;
	if (object->type == SPHERE)
		return (&((t_sphere *)data)->surface.texture_path);
	else if (object->type == PLANE)
		return (&((t_plane *)data)->surface.texture_path);
	else if (object->type == CYLINDER)
		return (&((t_cylinder *)data)->surface.texture_path);
	else if (object->type == CONE)
		return (&((t_cone *)data)->surface.texture_path);
	return (NULL);
}

static bool	load_texture_from_path(char *texture_path,
	mlx_texture_t **bump_texture)
{
	if (!texture_path)
	{
		*bump_texture = NULL;
		return (true);
	}
	*bump_texture = mlx_load_png(texture_path);
	if (!*bump_texture)
	{
		printf("Error: Could not load texture from path: %s\n", texture_path);
		return (false);
	}
	return (true);
}

bool	load_object_texture(t_object *object)
{
	char			*texture_path;
	mlx_texture_t	**bump_texture;

	if (!object)
		return (false);
	texture_path = *get_texture_path(object);
	bump_texture = get_bump_texture(object);
	if (!bump_texture)
		return (false);
	return (load_texture_from_path(texture_path, bump_texture));
}

bool	load_scene_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (!load_object_texture(&scene->objects[i]))
			return (false);
		i++;
	}	
	return (true);
}
