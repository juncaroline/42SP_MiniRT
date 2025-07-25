/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 17:13:39 by cabo-ram         ###   ########.fr       */
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
	return (true);
}
