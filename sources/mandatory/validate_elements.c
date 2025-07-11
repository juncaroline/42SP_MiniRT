/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/01 16:43:56 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

static bool	handle_sphere(char **tokens, t_scene *scene)
{
	t_sphere	new_sphere;
	int			count;

	count = count_tokens(tokens);
	if (!parse_sphere(tokens, count, &new_sphere))
		return (false);
	if (!add_sphere(scene, &new_sphere, 1))
		return (false);
	return (true);
}

static bool	handle_plane(char **tokens, t_scene *scene)
{
	t_plane	new_plane;
	int		count;

	count = count_tokens(tokens);
	if (!parse_plane(tokens, count, &new_plane))
		return (false);
	if (!add_plane(scene, &new_plane, 1))
		return (false);
	return (true);
}

static bool	handle_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	new_cylinder;
	int			count;

	count = count_tokens(tokens);
	if (!parse_cylinder(tokens, count, &new_cylinder))
		return (false);
	if (!add_cylinder(scene, &new_cylinder, 1))
		return (false);
	return (true);
}

bool	validate_elements(char **tokens, t_scene *scene)
{
	int	count;

	count = count_tokens(tokens);
	if (ft_strcmp(tokens[0], "A") == 0)
		return (parse_ambient(tokens, count, &scene->ambient));
	else if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_camera(tokens, count, &scene->camera));
	else if (ft_strcmp(tokens[0], "L") == 0)
		return (parse_light(tokens, count, &scene->light));
	else if (ft_strcmp(tokens[0], "sp") == 0)
		return (handle_sphere(tokens, scene));
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (handle_plane(tokens, scene));
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (handle_cylinder(tokens, scene));
	else
	{
		printf("Unknown element '%s'\n", tokens[0]);
		return (false);
	}
	return (true);
}
