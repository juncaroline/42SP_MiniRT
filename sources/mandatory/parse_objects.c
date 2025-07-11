/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 16:21:48 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	parse_sphere(char **tokens, int count, t_sphere *sphere)
{
	t_vector3d	center;
	float		diameter;
	t_rgb_color	color;

	if (count != 4)
	{
		printf("Erro: 'sp' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	center = parse_coordinates(tokens[1]);
	diameter = parse_measurements(tokens[2]);
	color = parse_rgb(tokens[3]);
	if (diameter <= 0 || !is_rgb_color(color))
		return (false);
	sphere->sphere_center = center;
	sphere->diameter = diameter;
	sphere->color = color;
	return (true);
}

bool	parse_plane(char **tokens, int count, t_plane *plane)
{
	t_vector3d	plane_point;
	t_vector3d	plane_normal;
	t_rgb_color	color;

	if (count != 4)
	{
		printf("Erro: 'pl' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	plane_point = parse_coordinates(tokens[1]);
	plane_normal = parse_normalized_vector(tokens[2]);
	color = parse_rgb(tokens[3]);
	if (!is_normalized_vector(plane_normal) || !is_rgb_color(color))
		return (false);
	plane->plane_point = plane_point;
	plane->vector = plane_normal;
	plane->color = color;
	return (true);
}

bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder)
{
	t_vector3d	cylinder_center;
	t_vector3d	cylinder_normal;
	float		diameter;
	float		height;
	t_rgb_color	color;

	if (count != 6)
	{
		printf("Erro: 'cy' espera 5 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	cylinder_center = parse_coordinates(tokens[1]);
	cylinder_normal = parse_normalized_vector(tokens[2]);
	diameter = parse_measurements(tokens[3]);
	height = parse_measurements(tokens[4]);
	color = parse_rgb(tokens[5]);
	if (!is_normalized_vector(cylinder_normal) || diameter <= 0.0
		|| height <= 0.0 || !is_rgb_color(color))
		return (false);
	cylinder->cylinder_center = cylinder_center;
	cylinder->vector = cylinder_normal;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;
	return (true);
}
