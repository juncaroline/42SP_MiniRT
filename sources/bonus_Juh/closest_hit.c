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

#include "../../includes/minirt_bonus.h"

t_intersec_info	find_closest_sphere(t_ray *ray, t_sphere *spheres,
	int count)
{
	t_intersec_info	closest;
	t_intersec_info	current;
	int					i;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	i = 0;
	if (count <= 0 || !spheres || !ray)
		return (closest);
	while (i < count)
	{
		current = intersect_sphere(ray, &spheres[i]);
		if (current.intersection
			&& current.dist_to_intersec < closest.dist_to_intersec)
			{
				closest = current;

				closest.uv = uv_sphere(current.intersec_point, sphere_center);

			}
		i++;
	}
	return (closest);
}

t_intersec_info	find_closest_plane(t_ray *ray, t_plane*planes, int count)
{
	t_intersec_info	closest;
	t_intersec_info	current;
	int					i;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	i = 0;
	if (count <= 0 || !planes || !ray)
		return (closest);
	while (i < count)
	{
		current = intersect_plane(ray, &planes[i]);
		if (current.intersection
			&& current.dist_to_intersec < closest.dist_to_intersec)
			{
				closest = current;

				closest.uv = uv_plane(current.intersec_point, plane.plane_point, scale);

			}
			i++;
	}
	return (closest);
}

t_intersec_info	find_closest_cylinder(t_ray *ray, t_cylinder *cylinders,
	int count)
{
	t_intersec_info	closest;
	t_intersec_info	current;
	int					i;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	i = 0;
	if (count <= 0 || !cylinders || !ray)
		return (closest);
	while (i < count)
	{
		current = intersect_cylinder(ray, &cylinders[i]);
		if (current.intersection
			&& current.dist_to_intersec < closest.dist_to_intersec)
			{
				closest = current;

				closest.uv = uv_cylinder(current.intersec_point, cylinders.cylinder_center, cylinder.vector, cylinder.height);

			}
			i++;
	}
	return (closest);
}

t_intersec_info	find_closest_cone(t_ray *ray, t_cone *cones,
	int count)
{
	t_intersec_info	closest;
	t_intersec_info	current;
	int					i;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	i = 0;
	if (count <= 0 || !cones || !ray)
		return (closest);
	while (i < count)
	{
		current = intersect_cone(ray, &cones[i]);
		if (current.intersection
			&& current.dist_to_intersec < closest.dist_to_intersec)
			{
				closest = current;

				closest.uv = uv_cone(current.intersec_point, cones.cone_center, cones.vector, cones.height);

			}
			i++;
	}
	return (closest);
}

t_intersec_info	find_closest_interesection(t_ray *ray, t_scene *scene)
{
	t_intersec_info	sphere_hit;
	t_intersec_info	plane_hit;
	t_intersec_info	cylinder_hit;
	t_intersec_info	cone_hit;
	t_intersec_info	closest;

	closest.object = NULL;
	closest.intersection = false;
	closest.dist_to_intersec = INFINITY;
	if (!ray || !scene)
		return (closest);
	sphere_hit = find_closest_sphere(ray, scene->sphere, scene->sphere_count);
	plane_hit = find_closest_plane(ray, scene->plane, scene->plane_count);
	cylinder_hit = find_closest_cylinder(ray, scene->cylinder,
			scene->cylinder_count);
	cone_hit = find_closest_cone(ray, scene->cone, scene->cone_count);
	closest = sphere_hit;
	if (plane_hit.intersection && plane_hit.dist_to_intersec
		< closest.dist_to_intersec)
		closest = plane_hit;
	if (cylinder_hit.intersection && cylinder_hit.dist_to_intersec
		< closest.dist_to_intersec)
		closest = cylinder_hit;
	if (cone_hit.intersection && cone_hit.dist_to_intersec
		< closest.dist_to_intersec)
		closest = cone_hit;
	return (closest);
}
