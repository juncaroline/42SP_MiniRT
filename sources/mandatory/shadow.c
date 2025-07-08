/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/08 14:47:50 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	in_shadow(t_scene *scene, t_intersection_info hit, t_light *light)
{
	t_ray				shadow_ray;
	t_intersection_info	shadow_hit;
	t_vector3d			light_dir;
	float				light_distance;

	// light_dir = subtract_vectors(light->light_point, hit.intersec_point);
	light_dir = subtract_vectors(light->light_point, hit.over_point);
	light_distance = sqrtf(dot_product(light_dir, light_dir));
	light_dir = normalize(light_dir);
	// shadow_ray.origin = add_vectors(hit.intersec_point,
	// 	scalar_multiplication(EPSILON, hit.normal));
	
	shadow_ray.origin = hit.over_point;
	shadow_ray.direction = light_dir;
	
	shadow_hit = find_closest_interesection(&shadow_ray, scene);
	if (shadow_hit.intersection && shadow_hit.dist_to_intersec < light_distance)
		return (true);
	return (false);
}

// bool	in_shadow(t_scene *scene, t_intersection_info hit, t_light *light)
// {
// 	t_ray				shadow_ray;
// 	t_intersection_info	shadow_hit;
// 	t_vector3d			light_dir;
// 	float				light_distance;

// 	light_dir = subtract_vectors(light->light_point, hit.intersec_point);
// 	light_distance = sqrtf(dot_product(light_dir, light_dir));
// 	light_dir = normalize(light_dir);
// 	shadow_ray.origin = add_vectors(hit.intersec_point,
// 		scalar_multiplication(EPSILON, hit.normal));
// 	shadow_ray.direction = light_dir;
// 	shadow_hit = find_closest_interesection(&shadow_ray, scene);
// 	if (shadow_hit.intersection && shadow_hit.dist_to_intersec < light_distance)
// 		return (true);
// 	return (false);
// }


// --------------------------------

// t_intersection_info	prepare_computations(t_object *object, t_ray ray, float t)
// {
// 	t_intersection_info	comps;

// 	comps.intersection = true;
// 	comps.dist_to_intersec = t;
// 	comps.object = object;

// 	// Calcula o ponto de intersecção
// 	comps.intersec_point = vector_add(ray.origin, vector_scalar(ray.direction, t));

// 	// Vetor do olho (câmera)
// 	t_vector3d eyev = vector_negate(ray.direction);

// 	// Normal no ponto (essa função depende do tipo do objeto)
// 	comps.normal = get_normal_at(object, comps.intersec_point);

// 	// Se o raio vem de dentro do objeto, inverter normal
// 	if (vector_dot(comps.normal, eyev) < 0)
// 	{
// 		comps.normal = vector_negate(comps.normal);
// 		comps.inside = true;
// 	}
// 	else
// 		comps.inside = false;

// 	// Corrige a posição para evitar acne
// 	t_vector3d offset = vector_scalar(comps.normal, EPSILON);
// 	comps.over_point = vector_add(comps.intersec_point, offset);

// 	return comps;
// }

