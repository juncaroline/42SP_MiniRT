/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/11 14:48:13 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	parse_sphere(char **tokens, int count, t_sphere *sphere)
{
	if (count != 4)
	{
		printf("Error: 'sp'expects 3 parameters, received %d\n", count - 1);
		return (false);
	}
	sphere->sphere_center = parse_coordinates(tokens[1]);
	sphere->diameter = parse_measurements(tokens[2]);
	sphere->color = parse_rgb(tokens[3]);
	if (sphere->diameter <= 0 || !is_rgb_color(sphere->color))
		return (false);
	return (true);
}

bool	parse_plane(char **tokens, int count, t_plane *plane)
{
	if (count != 4)
	{
		printf("Error: 'pl' expects 3 parameters, received %d\n", count - 1);
		return (false);
	}
	plane->plane_point = parse_coordinates(tokens[1]);
	plane->vector = parse_normalized_vector(tokens[2]);
	plane->color = parse_rgb(tokens[3]);
	if (!is_normalized_vector(plane->vector) || !is_rgb_color(plane->color))
		return (false);
	return (true);
}

bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder)
{
	if (count != 6)
	{
		printf("Error: 'cy' expects 5 parameters, received %d\n", count - 1);
		return (false);
	}
	cylinder->cylinder_center = parse_coordinates(tokens[1]);
	cylinder->vector = parse_normalized_vector(tokens[2]);
	cylinder->diameter = parse_measurements(tokens[3]);
	cylinder->height = parse_measurements(tokens[4]);
	cylinder->color = parse_rgb(tokens[5]);
	if (!is_normalized_vector(cylinder->vector) || cylinder->diameter <= 0.0
		|| cylinder->height <= 0.0 || !is_rgb_color(cylinder->color))
		return (false);
	return (true);
}
