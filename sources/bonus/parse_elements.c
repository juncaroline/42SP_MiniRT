/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:51 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/01 14:45:45 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

bool	parse_ambient(char **tokens, int count, t_ambient *ambient)
{
	if (count != 3)
	{
		printf("Erro: 'A' espera 2 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	ambient->ratio = parse_ratio(tokens[1]);
	ambient->color = parse_rgb(tokens[2]);
	if ((ambient->ratio < 0.0 || ambient->ratio > 1.0)
		|| !is_rgb_color(ambient->color))
		return (false);
	return (true);
}

bool	parse_camera(char **tokens, int count, t_camera *camera)
{
	t_vector3d	position;
	t_vector3d	dir;
	float		fov;

	if (count != 4)
	{
		printf("Erro: 'C' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	position = parse_coordinates(tokens[1]);
	dir = parse_normalized_vector(tokens[2]);
	fov = parse_fov(tokens[3]);
	if (!is_normalized_vector(dir) || (fov < 0.0 || fov > 180.0))
		return (false);
	camera->camera_position = position;
	camera->camera_direction = dir;
	camera->fov = fov;
	return (true);
}

bool	parse_light(char **tokens, int count, t_light *light)
{
	t_vector3d	light_point;
	float		ratio;
	t_rgb_color	color;

	if (count != 4 && count != 5)
	{
		printf("Erro: 'L' espera 3 ou 4 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	light_point = parse_coordinates(tokens[1]);
	ratio = parse_ratio(tokens[2]);
	color = parse_rgb(tokens[3]);
	if (ratio < 0.0 || ratio > 1.0)
		return (false);
	light->light_point = light_point;
	light->ratio = ratio;
	if (count == 5)
	{
		if (!is_rgb_color(color))
			return (false);
	}
	light->color = color;
	return (true);
}
