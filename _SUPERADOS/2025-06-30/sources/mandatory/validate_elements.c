/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 09:27:38 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	verify_elements(char *content, int i)
{
	if (ft_strncmp(content + i, "A", 1) == 0)
		printf("Detected ambient light\n");
	else if (ft_strncmp(content + i, "C", 1) == 0)
		printf("Detected camera\n");
	else if (ft_strncmp(content + i, "L", 1) == 0)
		printf("Detected light source\n");
	else if (ft_strncmp(content + i, "sp", 2) == 0)
		printf("Detected sphere\n");
	else if (ft_strncmp(content + i, "pl", 2) == 0)
		printf("Detected plane\n");
	else if (ft_strncmp(content + i, "cy", 2) == 0)
		printf("Detected cylinder\n");
	else
		printf("Unknown element: %s\n", content);
}

bool	validate_elements(char **tokens, t_scene *scene)
{
	int			count;
	t_sphere	new_sphere;
	t_plane		new_plane;
	t_cylinder	new_cylinder;

	count = 0;
	while (tokens[count])
		count++;
	if (ft_strcmp(tokens[0], "A") == 0)
		return (parse_ambient(tokens, count, &scene->ambient));
	else if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_camera(tokens, count, &scene->camera));
	else if (ft_strcmp(tokens[0], "L") == 0)
		return (parse_light(tokens, count, &scene->light));
	else if (ft_strcmp(tokens[0], "sp") == 0)
	{
		if (!parse_sphere(tokens, count, &new_sphere))
			return (false);
		if (!add_sphere(scene, &new_sphere, 1))
			return (false);
	}
	else if (ft_strcmp(tokens[0], "pl") == 0)
	{
		if (!parse_plane(tokens, count, &new_plane))
			return (false);
		if (!add_plane(scene, &new_plane, 1))
			return (false);
	}
	else if (ft_strcmp(tokens[0], "cy") == 0)
	{
		if (!parse_cylinder(tokens, count, &new_cylinder))
			return (false);
		if (!add_cylinder(scene, &new_cylinder, 1))
			return (false);
	}
	else if (!(ft_strcmp(tokens[0], "A") == 0 || ft_strcmp(tokens[0], "C") == 0
			|| ft_strcmp(tokens[0], "L") == 0 || ft_strcmp(tokens[0], "sp") == 0
			|| ft_strcmp(tokens[0], "pl") == 0
			|| ft_strcmp(tokens[0], "cy") == 0))
	{
		printf("Erro: Elemento desconhecido '%s'\n", tokens[0]);
		return (false);
	}
	return (true);
}
