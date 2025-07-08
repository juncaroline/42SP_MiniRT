/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/08 19:00:21 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

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

// static bool	handle_plane(char **tokens, t_scene *scene)
// {
// 	t_plane	new_plane;
// 	int		count;
// 	int		add;

// 	count = count_tokens(tokens);
// 	if (!parse_plane(tokens, count, &new_plane))
// 		return (false);
// 	add = scene->plane_count;
// 	if (!add_plane(scene, &new_plane, 1))
// 		return (false);
// 	add_object(scene, PLANE, &scene->plane[add]);
// 	return (true);
// }

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

static bool	handle_cone(char **tokens, t_scene *scene)
{
	t_cone	new_cone;
	int		count;

	// new_cone = ft_calloc(1, sizeof(t_cone));
	// if (!new_cone)
	// {
	// 	printf("Memory allocation failed for new cone\n");
	// 	return (false);
	// }
	count = count_tokens(tokens);
	if (!parse_cone(tokens, count, &new_cone))
		return (false);
	if (!add_cone(scene, &new_cone, 1))
		return (false);
	return (true);
}

static bool	handle_light(char **tokens, t_scene *scene)
{
	t_light	new_light;
	int		count;

	count = count_tokens(tokens);
	if (!parse_light(tokens, count, &new_light))
		return (false);
	if (!add_light(scene, &new_light, 1))
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
		return (handle_light(tokens, scene));
	else if (ft_strcmp(tokens[0], "sp") == 0)
		return (handle_sphere(tokens, scene));
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (handle_plane(tokens, scene));
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (handle_cylinder(tokens, scene));
	else if (ft_strcmp(tokens[0], "cn") == 0)
		return (handle_cone(tokens, scene));
	else
	{
		printf("Unknown element '%s'\n", tokens[0]);
		return (false);
	}
	return (true);
}
