/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/23 11:20:29 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

bool	in_shadow(t_scene *scene, t_intersec_info hit, t_light *light)
{
	t_ray			shadow_ray;
	t_intersec_info	shadow_hit;
	t_vector3d		light_dir;
	float			light_distance;

	light_dir = subtract_vectors(light->light_point, hit.over_point);
	light_distance = sqrtf(dot_product(light_dir, light_dir));
	light_dir = normalize(light_dir);
	shadow_ray.origin = hit.over_point;
	shadow_ray.direction = light_dir;
	shadow_hit = find_closest_interesection(&shadow_ray, scene);
	if (shadow_hit.intersection && shadow_hit.dist_to_intersec < light_distance)
		return (true);
	return (false);
}

void	prepare_point(t_intersec_info *hit, t_ray ray)
{
	t_vector3d	eyev;

	if (!hit || !hit->intersection)
		return ;
	eyev = scalar_multiplication(-1, ray.direction);
	if (dot_product(hit->normal, eyev) < 0)
		hit->normal = scalar_multiplication(-1, hit->normal);
	hit->over_point = add_vectors(hit->intersec_point, \
		scalar_multiplication(EPSILON, hit->normal));
}
