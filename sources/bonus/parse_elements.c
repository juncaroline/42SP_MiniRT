/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:51 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/14 11:10:40 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

bool	parse_ambient(char **tokens, int count, t_ambient *ambient)
{
	if (count != 3)
	{
		printf("Error: 'A' expects 2 parameters, received %d\n", count - 1);
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
	if (count != 4)
	{
		printf("Error: 'C' expects 3 parameters, received %d\n", count - 1);
		return (false);
	}
	camera->camera_position = parse_coordinates(tokens[1]);
	camera->camera_direction = parse_normalized_vector(tokens[2]);
	camera->fov = parse_fov(tokens[3]);
	if (!is_normalized_vector(camera->camera_direction) || (camera->fov < 0.0
			|| camera->fov > 180.0))
		return (false);
	return (true);
}

bool	parse_light(char **tokens, int count, t_light *light)
{
	if (count != 4 && count != 5)
	{
		printf("Erro: 'L' espera 3 ou 4 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	light->light_point = parse_coordinates(tokens[1]);
	light->ratio = parse_ratio(tokens[2]);
	light->color = parse_rgb(tokens[3]);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		return (false);
	if (count == 5)
	{
		if (!is_rgb_color(light->color))
			return (false);
	}
	return (true);
}
