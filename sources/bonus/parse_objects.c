/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/17 12:01:30 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

bool	parse_sphere(char **tokens, int count, t_sphere *sphere)
{
	if (count != 4 && count != 5)
	{
		printf("Error: 'sp'expects 3-5 parameters, received %d\n", count - 1);
		return (false);
	}
	sphere->sphere_center = parse_coordinates(tokens[1]);
	sphere->diameter = parse_measurements(tokens[2]);
	sphere->color = parse_rgb(tokens[3]);
	sphere->has_checker = false;
	sphere->bump_texture = NULL;
	sphere->texture_path = NULL;
	if (sphere->diameter <= 0 || !is_rgb_color(sphere->color))
		return (false);
	if (count >= 5 && ft_strncmp(tokens[4], "checker", 7) == 0)
		sphere->has_checker = true;
	else if (count >= 5 && ft_strncmp(tokens[4], "texture:", 8) == 0)
		sphere->texture_path = ft_strdup(tokens[4] + 8);
	return (true);
}

bool	parse_plane(char **tokens, int count, t_plane *plane)
{
	if (count != 4 && count != 5)
	{
		printf("Error: 'pl' expects 3 parameters, received %d\n", count - 1);
		return (false);
	}
	plane->plane_point = parse_coordinates(tokens[1]);
	plane->vector = parse_normalized_vector(tokens[2]);
	plane->color = parse_rgb(tokens[3]);
	plane->has_checker = false;
	plane->bump_texture = NULL;
	plane->texture_path = NULL;
	if (!is_normalized_vector(plane->vector) || !is_rgb_color(plane->color))
		return (false);
	if (count == 5 && ft_strncmp(tokens[4], "checker", 7) == 0)
		plane->has_checker = true;
	else if (count == 5 && ft_strncmp(tokens[4], "texture:", 8) == 0)
		plane->texture_path = ft_strdup(tokens[4] + 8);
	return (true);
}

bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder)
{
	if (count != 6 && count != 7)
	{
		printf("Error: 'cy' expects 5 parameters, received %d\n", count - 1);
		return (false);
	}
	cylinder->cylinder_center = parse_coordinates(tokens[1]);
	cylinder->vector = parse_normalized_vector(tokens[2]);
	cylinder->diameter = parse_measurements(tokens[3]);
	cylinder->height = parse_measurements(tokens[4]);
	cylinder->color = parse_rgb(tokens[5]);
	cylinder->has_checker = false;
	cylinder->bump_texture = NULL;
	cylinder->texture_path = NULL;
	if (!is_normalized_vector(cylinder->vector) || cylinder->diameter <= 0.0
		|| cylinder->height <= 0.0 || !is_rgb_color(cylinder->color))
		return (false);
	if (count == 7 && ft_strncmp(tokens[6], "checker", 7) == 0)
		cylinder->has_checker = true;
	else if (count == 7 && ft_strncmp(tokens[6], "texture:", 8) == 0)
		cylinder->texture_path = ft_strdup(tokens[6] + 8);
	return (true);
}

bool	parse_cone(char **tokens, int count, t_cone *cone)
{
	if (count != 6 && count != 7)
	{
		printf("Erro: 'cn' espera 5 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	cone->cone_center = parse_coordinates(tokens[1]);
	cone->vector = parse_normalized_vector(tokens[2]);
	cone->diameter = parse_measurements(tokens[3]);
	cone->height = parse_measurements(tokens[4]);
	cone->color = parse_rgb(tokens[5]);
	cone->has_checker = false;
	cone->bump_texture = NULL;
	cone->texture_path = NULL;
	if (!is_normalized_vector(cone->vector) || cone->diameter <= 0.0
		|| cone->height <= 0.0 || !is_rgb_color(cone->color))
		return (false);
	if (count == 7 && ft_strncmp(tokens[6], "checker", 7) == 0)
		cone->has_checker = true;
	else if (count == 7 && ft_strncmp(tokens[6], "texture:", 8) == 0)
		cone->texture_path = ft_strdup(tokens[6] + 8);
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
	object->white = (t_rgb_color){255, 255, 255};
	object->black = (t_rgb_color){0, 0, 0};
	free(scene->objects);
	scene->objects = new_array;
	scene->object_count++;
}
