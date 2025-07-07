/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:00 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 09:27:00 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// t_intersec_info	find_closest_sphere(t_ray *ray, t_sphere *spheres,
// 	int count)
// {
// 	t_intersec_info	closest;
// 	t_intersec_info	current;
// 	int					i;

// 	closest.object = NULL;
// 	closest.intersection = false;
// 	closest.dist_to_intersec = INFINITY;
// 	i = 0;
// 	if (count <= 0 || !spheres || !ray)
// 		return (closest);
// 	while (i < count)
// 	{
// 		current = intersect_sphere(ray, &spheres[i]);
// 		if (current.intersection
// 			&& current.dist_to_intersec < closest.dist_to_intersec)
// 			closest = current;
// 		i++;
// 	}
// 	return (closest);
// }

// t_intersec_info	find_closest_plane(t_ray *ray, t_plane*planes, int count)
// {
// 	t_intersec_info	closest;
// 	t_intersec_info	current;
// 	int					i;

// 	closest.object = NULL;
// 	closest.intersection = false;
// 	closest.dist_to_intersec = INFINITY;
// 	i = 0;
// 	if (count <= 0 || !planes || !ray)
// 		return (closest);
// 	while (i < count)
// 	{
// 		current = intersect_plane(ray, &planes[i]);
// 		if (current.intersection
// 			&& current.dist_to_intersec < closest.dist_to_intersec)
// 			closest = current;
// 		i++;
// 	}
// 	return (closest);
// }

// t_intersec_info	find_closest_cylinder(t_ray *ray, t_cylinder *cylinders,
// 	int count)
// {
// 	t_intersec_info	closest;
// 	t_intersec_info	current;
// 	int					i;

// 	closest.object = NULL;
// 	closest.intersection = false;
// 	closest.dist_to_intersec = INFINITY;
// 	i = 0;
// 	if (count <= 0 || !cylinders || !ray)
// 		return (closest);
// 	while (i < count)
// 	{
// 		current = intersect_cylinder(ray, &cylinders[i]);
// 		if (current.intersection
// 			&& current.dist_to_intersec < closest.dist_to_intersec)
// 			closest = current;
// 		i++;
// 	}
// 	return (closest);
// }

t_intersec_info	intersect_object(t_ray *ray, t_object *object)
{
	t_intersec_info	result;
	t_object_type		type;

	result.object = NULL;
	result.intersection = false;
	result.dist_to_intersec = INFINITY;
	if (!ray || !object)
		return (result);
	type = object->type;
	if (type == SPHERE)
		result = intersect_sphere(ray, (t_sphere *)object->data);
	else if (type == PLANE)
		result = intersect_plane(ray, (t_plane *)object->data);
	else if (type == CYLINDER)
		result = intersect_cylinder(ray, (t_cylinder *)object->data);
	else if (type == CONE)
		result = intersect_cone(ray, (t_cone *)object->data);
	if (result.intersection)
		result.object = object;
	return (result);
}

t_intersec_info	find_closest_object(t_ray *ray, t_object *objects, int count)
{
	t_intersec_info	closest;
	t_intersec_info	current;
	int					i;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	if (!ray || !objects || count <= 0)
		return (closest);
	i = 0;
	while (i < count)
	{
		current = intersect_single_object(ray, &objects[i]);
		if (current.intersection && current.dist_to_intersec < closest.dist_to_intersec)
			closest = current;
		i++;
	}
	return (closest);
}

t_intersec_info	find_closest_interesection(t_ray *ray, t_scene *scene)
{
	t_intersec_info	closest;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	if (!ray || !scene)
		return (closest);
	closest = find_closest_object(ray, scene->objects, scene->object_count);
	return (closest);
}
