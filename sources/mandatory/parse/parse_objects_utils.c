/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:15:03 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 18:18:00 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void	assign_object_data(t_object *object, t_scene *scene, int *index)
{
	if (object->type == SPHERE)
	{
		object->data = &scene->sphere[index[0]];
		index[0]++;
	}
	else if (object->type == PLANE)
	{
		object->data = &scene->plane[index[1]];
		index[1]++;
	}
	else if (object->type == CYLINDER)
	{
		object->data = &scene->cylinder[index[2]];
		index[2]++;
	}
}

void	rebuild_object_pointers(t_scene *scene)
{
	int	i;
	int	index[4];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	i = 0;
	while (i < scene->object_count)
	{
		assign_object_data(&scene->objects[i], scene, index);
		i++;
	}
}
