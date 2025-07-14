/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/14 11:11:55 by cabo-ram         ###   ########.fr       */
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
	else if (ft_strncmp(content + i, "cn", 2) == 0)
		printf("Detected cone\n");
	else
		printf("Unknown element: %s\n", content);
}

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
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
