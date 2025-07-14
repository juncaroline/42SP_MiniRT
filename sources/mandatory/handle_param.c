/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:31:52 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/14 11:12:49 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	handle_sphere(char **tokens, t_scene *scene)
{
	t_sphere	new_sphere;
	int			count;

	count = count_tokens(tokens);
	if (!parse_sphere(tokens, count, &new_sphere))
		return (false);
	if (!add_sphere(scene, &new_sphere, 1))
		return (false);
	add_object(scene, SPHERE, NULL);
	rebuild_object_pointers(scene);
	return (true);
}

bool	handle_plane(char **tokens, t_scene *scene)
{
	t_plane	new_plane;
	int		count;

	count = count_tokens(tokens);
	if (!parse_plane(tokens, count, &new_plane))
		return (false);
	if (!add_plane(scene, &new_plane, 1))
		return (false);
	add_object(scene, PLANE, NULL);
	rebuild_object_pointers(scene);
	return (true);
}

bool	handle_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	new_cylinder;
	int			count;

	count = count_tokens(tokens);
	if (!parse_cylinder(tokens, count, &new_cylinder))
		return (false);
	if (!add_cylinder(scene, &new_cylinder, 1))
		return (false);
	add_object(scene, CYLINDER, NULL);
	rebuild_object_pointers(scene);
	return (true);
}
