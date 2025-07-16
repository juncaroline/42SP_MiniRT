/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:07 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/16 15:58:01 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->sphere)
		free(scene->sphere);
	if (scene->plane)
		free(scene->plane);
	if (scene->cylinder)
		free(scene->cylinder);
	if (scene->cone)
		free(scene->cone);
	if (scene->light)
		free(scene->light);
	if (scene->objects)
		free(scene->objects);
}

void	free_scene_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		free_object_texture(&scene->objects[i]);
		i++;
	}
}
