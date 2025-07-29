/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:48:07 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/29 14:59:39 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

static bool	parse_cone_bonus(t_cone *cone, char **tokens, int count)
{
	cone->surface.has_checker = false;
	cone->surface.bump_texture = NULL;
	cone->surface.texture_path = NULL;
	cone->surface.bump = false;
	if (count == 7 && ft_strncmp(tokens[6], "checker", 7) == 0)
		cone->surface.has_checker = true;
	else if (count == 7 && ft_strncmp(tokens[6], "texture:", 8) == 0)
		cone->surface.texture_path = ft_strdup(tokens[6] + 8);
	else if (count == 7 && ft_strncmp(tokens[6], "bump", 4) == 0)
		cone->surface.bump = true;
	else if (count == 7 && ft_strncmp(tokens[6], "checker", 7) != 0
		&& ft_strncmp(tokens[6], "texture:", 8) != 0
		&& ft_strncmp(tokens[6], "bump", 4) != 0)
		return (parse_error("Invalid cone bonus parameter"));
	return (true);
}

bool	parse_cone(char **tokens, int count, t_cone *cone)
{
	if (count != 6 && count != 7)
		return (parse_error("'cn' expects 5 or 6 parameters"));
	cone->cone_center = parse_coordinates(tokens[1]);
	cone->vector = parse_normalized_vector(tokens[2]);
	cone->diameter = parse_measurements(tokens[3]);
	cone->height = parse_measurements(tokens[4]);
	if (!parse_rgb(tokens[5], &cone->color))
		return (false);
	if (!is_normalized_vector(cone->vector) || cone->diameter <= 0.0
		|| cone->height <= 0.0)
		return (false);
	return (parse_cone_bonus(cone, tokens, count));
}

void	add_object(t_scene *scene, t_object_type type, void *data)
{
	t_object	*new_array;
	t_object	*object;
	int			i;

	new_array = malloc(sizeof(t_object) * (scene->object_count + 1));
	if (!new_array)
		return ;
	i = 0;
	while (i < scene->object_count)
	{
		new_array[i] = scene->objects[i];
		i++;
	}
	object = &new_array[scene->object_count];
	object->type = type;
	object->data = data;
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
	free(scene->objects);
	scene->objects = new_array;
	scene->object_count++;
}

static void	assign_object_data(t_object *object, t_scene *scene, int *index)
{
	if (object->type == SPHERE)
	{
		object->data = &scene->sphere[index[0]];
		index[0]++;
	}
	else if (object->type == PLANE)
	{
		object->data = &scene->plane[index[1]];
		index[1]++;
	}
	else if (object->type == CYLINDER)
	{
		object->data = &scene->cylinder[index[2]];
		index[2]++;
	}
	else if (object->type == CONE)
	{
		object->data = &scene->cone[index[3]];
		index[3]++;
	}
}

void	rebuild_object_pointers(t_scene *scene)
{
	int	i;
	int	index[4];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	index[3] = 0;
	i = 0;
	while (i < scene->object_count)
	{
		assign_object_data(&scene->objects[i], scene, index);
		i++;
	}
}
