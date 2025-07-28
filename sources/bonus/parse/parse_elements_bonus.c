/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:51 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 15:09:45 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

bool	parse_ambient(char **tokens, int count, t_ambient *ambient)
{
	if (count != 3)
		return (parse_error("'A' expects 2 parameters"));
	if (!parse_ratio(tokens[1], &ambient->ratio))
		return (false);
	if (!parse_rgb(tokens[2], &ambient->color))
		return (false);
	return (true);
}

bool	parse_camera(char **tokens, int count, t_camera *camera)
{
	if (count != 4)
		return (parse_error("'C' expects 3 parameters"));
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
	if (count != 4)
		return (parse_error("'L' expects 3 parameters"));
	light->light_point = parse_coordinates(tokens[1]);
	if (!parse_ratio(tokens[2], &light->ratio))
		return (false);
	if (!parse_rgb(tokens[3], &light->color))
		return (false);
	return (true);
}
