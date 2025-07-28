/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 14:46:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

bool	validate_scene_objects(char **tokens, t_scene *scene)
{
	int	count;

	count = count_tokens(tokens);
	if (ft_strcmp(tokens[0], "sp") == 0)
		return (handle_sphere(tokens, scene));
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (handle_plane(tokens, scene));
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (handle_cylinder(tokens, scene));
	return (true);
}

bool	count_scene_elements(char **tokens, int count, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0)
	{
		if (scene->has_ambient)
			return (parse_error("Only one element 'A' is allowed"));
		scene->has_ambient = true;
		return (parse_ambient(tokens, count, &scene->ambient));
	}
	else if (ft_strcmp(tokens[0], "C") == 0)
	{
		if (scene->has_camera)
			return (parse_error("Only one element 'C' is allowed"));
		scene->has_camera = true;
		return (parse_camera(tokens, count, &scene->camera));
	}
	else if (ft_strcmp(tokens[0], "L") == 0)
	{
		if (scene->has_light)
			return (parse_error("Only one element 'L' is allowed"));
		scene->has_light = true;
		return (parse_light(tokens, count, &scene->light));
	}
	return (parse_error("Invalid scene element"));
}

bool	validate_line(char **tokens, t_scene *scene)
{
	int	count;

	count = count_tokens(tokens);
	if (ft_strcmp(tokens[0], "A") == 0 || ft_strcmp(tokens[0], "C") == 0
		|| ft_strcmp(tokens[0], "L") == 0)
		return (count_scene_elements(tokens, count, scene));
	else if (ft_strcmp(tokens[0], "sp") == 0 || ft_strcmp(tokens[0], "pl") == 0
		|| ft_strcmp(tokens[0], "cy") == 0)
		return (validate_scene_objects(tokens, scene));
	else
		return (parse_error("Invalid scene element"));
}
