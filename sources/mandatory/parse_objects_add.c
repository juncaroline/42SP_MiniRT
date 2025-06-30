/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:20:29 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 16:21:47 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	add_sphere(t_scene *scene, t_sphere *new_sphere, int count)
{
	t_sphere	*new_array;
	int			i;

	new_array = malloc(sizeof(t_sphere) * (scene->sphere_count + count));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->sphere_count)
	{
		new_array[i] = scene->sphere[i];
		i++;
	}
	i = 0;
	while (i < count)
	{
		new_array[scene->sphere_count + i] = new_sphere[i];
		i++;
	}
	free(scene->sphere);
	scene->sphere = new_array;
	scene->sphere_count += count;
	return (true);
}

bool	add_plane(t_scene *scene, t_plane *new_plane, int count)
{
	t_plane	*new_array;
	int		i;

	new_array = malloc(sizeof(t_plane) * (scene->plane_count + count));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->plane_count)
	{
		new_array[i] = scene->plane[i];
		i++;
	}
	i = 0;
	while (i < count)
	{
		new_array[scene->plane_count + i] = new_plane[i];
		i++;
	}
	free(scene->plane);
	scene->plane = new_array;
	scene->plane_count += count;
	return (true);
}

bool	add_cylinder(t_scene *scene, t_cylinder *new_cylinder, int count)
{
	t_cylinder	*new_array;
	int			i;

	new_array = malloc(sizeof(t_cylinder) * (scene->cylinder_count + count));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->cylinder_count)
	{
		new_array[i] = scene->cylinder[i];
		i++;
	}
	i = 0;
	while (i < count)
	{
		new_array[scene->cylinder_count + i] = new_cylinder[i];
		i++;
	}
	free(scene->cylinder);
	scene->cylinder = new_array;
	scene->cylinder_count += count;
	return (true);
}
