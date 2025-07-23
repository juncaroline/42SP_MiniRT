/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:07 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 15:07:56 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

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
	if (scene->objects)
		free(scene->objects);
}
