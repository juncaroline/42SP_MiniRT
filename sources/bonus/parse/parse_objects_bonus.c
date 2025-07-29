/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:26:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/29 15:03:10 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

bool	parse_sphere(char **tokens, int count, t_sphere *sphere)
{
	if (count != 4 && count != 5)
		return (parse_error("'sp' expects 3 or 4 parameters"));
	sphere->sphere_center = parse_coordinates(tokens[1]);
	sphere->diameter = parse_measurements(tokens[2]);
	sphere->surface.has_checker = false;
	sphere->surface.bump_texture = NULL;
	sphere->surface.texture_path = NULL;
	sphere->surface.bump = false;
	if (!parse_rgb(tokens[3], &sphere->color))
		return (false);
	if (sphere->diameter <= 0)
		return (false);
	if (count == 5 && ft_strncmp(tokens[4], "checker", 7) == 0)
		sphere->surface.has_checker = true;
	else if (count == 5 && ft_strncmp(tokens[4], "texture:", 8) == 0)
		sphere->surface.texture_path = ft_strdup(tokens[4] + 8);
	else if (count == 5 && ft_strncmp(tokens[4], "bump", 4) == 0)
		sphere->surface.bump = true;
	else if (count == 5 && ft_strncmp(tokens[4], "checker", 7) != 0
		&& ft_strncmp(tokens[4], "texture:", 8) != 0
		&& ft_strncmp(tokens[4], "bump", 4) != 0)
		return (parse_error("Invalid sphere bonus parameter"));
	return (true);
}

bool	parse_plane(char **tokens, int count, t_plane *plane)
{
	if (count != 4 && count != 5)
		return (parse_error("'pl' expects 3 or 4 parameters"));
	plane->plane_point = parse_coordinates(tokens[1]);
	plane->vector = parse_normalized_vector(tokens[2]);
	plane->surface.has_checker = false;
	plane->surface.bump_texture = NULL;
	plane->surface.texture_path = NULL;
	plane->surface.bump = false;
	if (!parse_rgb(tokens[3], &plane->color))
		return (false);
	if (!is_normalized_vector(plane->vector))
		return (false);
	if (count == 5 && ft_strncmp(tokens[4], "checker", 7) == 0)
		plane->surface.has_checker = true;
	else if (count == 5 && ft_strncmp(tokens[4], "texture:", 8) == 0)
		plane->surface.texture_path = ft_strdup(tokens[4] + 8);
	else if (count == 5 && ft_strncmp(tokens[4], "bump", 4) == 0)
		plane->surface.bump = true;
	else if (count == 5 && ft_strncmp(tokens[4], "checker", 7) != 0
		&& ft_strncmp(tokens[4], "texture:", 8) != 0
		&& ft_strncmp(tokens[4], "bump", 4) != 0)
		return (parse_error("Invalid plane bonus parameter"));
	return (true);
}

static bool	parse_cylinder_bonus(t_cylinder *cylinder, char **tokens, int count)
{
	cylinder->surface.has_checker = false;
	cylinder->surface.bump_texture = NULL;
	cylinder->surface.texture_path = NULL;
	cylinder->surface.bump = false;
	if (count == 7 && ft_strncmp(tokens[6], "checker", 7) == 0)
		cylinder->surface.has_checker = true;
	else if (count == 7 && ft_strncmp(tokens[6], "texture:", 8) == 0)
		cylinder->surface.texture_path = ft_strdup(tokens[6] + 8);
	else if (count == 7 && ft_strncmp(tokens[6], "bump", 4) == 0)
		cylinder->surface.bump = true;
	else if (count == 7 && ft_strncmp(tokens[6], "checker", 7) != 0
		&& ft_strncmp(tokens[6], "texture:", 8) != 0
		&& ft_strncmp(tokens[6], "bump", 4) != 0)
		return (parse_error("Invalid cylinder bonus parameter"));
	return (true);
}

bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder)
{
	if (count != 6 && count != 7)
		return (parse_error("'cy' expects 5 or 6 parameters"));
	cylinder->cylinder_center = parse_coordinates(tokens[1]);
	cylinder->vector = parse_normalized_vector(tokens[2]);
	cylinder->diameter = parse_measurements(tokens[3]);
	cylinder->height = parse_measurements(tokens[4]);
	if (!parse_rgb(tokens[5], &cylinder->color))
		return (false);
	if (!is_normalized_vector(cylinder->vector) || cylinder->diameter <= 0.0
		|| cylinder->height <= 0.0)
		return (false);
	return (parse_cylinder_bonus(cylinder, tokens, count));
}
