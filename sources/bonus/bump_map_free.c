/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:44:17 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/16 16:44:37 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

static void	free_texture(mlx_texture_t **bump_texture,
	char **texture_path)
{
	if (bump_texture && *bump_texture)
	{
		mlx_delete_texture(*bump_texture);
		*bump_texture = NULL;
	}
	if (texture_path && *texture_path)
	{
		free(*texture_path);
		*texture_path = NULL;
	}
}

void	free_object_texture(t_object *object)
{
	mlx_texture_t	**bump_texture;
	char			**texture_path;

	if (!object)
		return ;
	bump_texture = get_bump_texture(object);
	texture_path = get_texture_path(object);
	free_texture(bump_texture, texture_path);
}
