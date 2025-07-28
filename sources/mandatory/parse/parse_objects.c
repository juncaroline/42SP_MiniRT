/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 11:15:58 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	parse_sphere(char **tokens, int count, t_sphere *sphere)
{
	if (count != 4)
		return (parse_error("'sp' expects 3 parameters"));
	sphere->sphere_center = parse_coordinates(tokens[1]);
	sphere->diameter = parse_measurements(tokens[2]);
	if (!parse_rgb(tokens[3], &sphere->color))
		return (false);
	if (sphere->diameter <= 0)
		return (false);
	return (true);
}

bool	parse_plane(char **tokens, int count, t_plane *plane)
{
	if (count != 4)
		return (parse_error("'pl' expects 3 parameters"));
	plane->plane_point = parse_coordinates(tokens[1]);
	plane->vector = parse_normalized_vector(tokens[2]);
	if (!parse_rgb(tokens[3], &plane->color))
		return (false);
	if (!is_normalized_vector(plane->vector))
		return (false);
	return (true);
}

bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder)
{
	if (count != 6)
		return (parse_error("'cy' expects 5 parameters"));
	cylinder->cylinder_center = parse_coordinates(tokens[1]);
	cylinder->vector = parse_normalized_vector(tokens[2]);
	cylinder->diameter = parse_measurements(tokens[3]);
	cylinder->height = parse_measurements(tokens[4]);
	if (!parse_rgb(tokens[5], &cylinder->color))
		return (false);
	if (!is_normalized_vector(cylinder->vector) || cylinder->diameter <= 0.0
		|| cylinder->height <= 0.0)
		return (false);
	return (true);
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
	free(scene->objects);
	scene->objects = new_array;
	scene->object_count++;
}
