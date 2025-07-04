/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/01 18:29:17 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	in_shadow(t_scene *scene, t_intersection_info hit, t_light *light)
{
	t_ray				shadow_ray;
	t_intersection_info	shadow_hit;
	t_vector3d			light_dir;
	float				light_distance;

	light_dir = subtract_vectors(light->light_point, hit.intersec_point);
	light_distance = sqrtf(dot_product(light_dir, light_dir));
	light_dir = normalize(light_dir);
	shadow_ray.origin = add_vectors(hit.intersec_point,
		scalar_multiplication(EPSILON, hit.normal));
	shadow_ray.direction = light_dir;
	shadow_hit = find_closest_interesection(&shadow_ray, scene);
	if (shadow_hit.intersection && shadow_hit.dist_to_intersec < light_distance)
		return (true);
	return (false);
}
