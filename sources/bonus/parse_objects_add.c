/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:20:29 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/14 15:49:03 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

bool	add_sphere(t_scene *scene, t_sphere *new_sphere, int count)
{
	t_sphere	*new_array;
	int			i;

	if (count != 1)
		return (false);
	new_array = malloc(sizeof(t_sphere) * (scene->sphere_count + 1));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->sphere_count)
	{
		new_array[i] = scene->sphere[i];
		i++;
	}
	new_array[scene->sphere_count] = *new_sphere;
	free(scene->sphere);
	scene->sphere = new_array;
	scene->sphere_count += 1;
	return (true);
}

bool	add_plane(t_scene *scene, t_plane *new_plane, int count)
{
	t_plane	*new_array;
	int		i;

	if (count != 1)
		return (false);
	new_array = malloc(sizeof(t_plane) * (scene->plane_count + 1));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->plane_count)
	{
		new_array[i] = scene->plane[i];
		i++;
	}
	new_array[scene->plane_count] = *new_plane;
	free(scene->plane);
	scene->plane = new_array;
	scene->plane_count += 1;
	return (true);
}

bool	add_cylinder(t_scene *scene, t_cylinder *new_cylinder, int count)
{
	t_cylinder	*new_array;
	int			i;

	if (count != 1)
		return (false);
	new_array = malloc(sizeof(t_cylinder) * (scene->cylinder_count + 1));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->cylinder_count)
	{
		new_array[i] = scene->cylinder[i];
		i++;
	}
	new_array[scene->cylinder_count] = *new_cylinder;
	free(scene->cylinder);
	scene->cylinder = new_array;
	scene->cylinder_count += 1;
	return (true);
}

bool	add_cone(t_scene *scene, t_cone *new_cone, int count)
{
	t_cone	*new_array;
	int		i;

	if (count != 1)
		return (false);
	new_array = malloc(sizeof(t_cone) * (scene->cone_count + 1));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->cone_count)
	{
		new_array[i] = scene->cone[i];
		i++;
	}
	new_array[scene->cone_count] = *new_cone;
	free(scene->cone);
	scene->cone = new_array;
	scene->cone_count += 1;
	return (true);
}

bool	add_light(t_scene *scene, t_light *new_light, int count)
{
	t_light	*new_array;
	int		i;

	if (count != 1)
		return (false);
	new_array = malloc(sizeof(t_light) * (scene->light_count + 1));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->light_count)
	{
		new_array[i] = scene->light[i];
		i++;
	}
	new_array[scene->light_count] = *new_light;
	free(scene->light);
	scene->light = new_array;
	scene->light_count += 1;
	return (true);
}
