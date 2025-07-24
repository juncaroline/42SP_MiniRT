/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_in_shadow_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/24 13:24:50 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

static t_vector3d	reflection(t_intersec_info hit, t_light *light)
{
	float		scalar_nbr;
	t_vector3d	result;
	t_vector3d	light_dir;

	light_dir = normalize(subtract_vectors(light->light_point, \
				hit.intersec_point));
	scalar_nbr = 2 * dot_product(hit.normal, light_dir);
	result = scalar_multiplication(scalar_nbr, hit.normal);
	return (subtract_vectors(result, light_dir));
}

static t_rgb_color	spec_color(t_intersec_info hit, t_scene *scene, \
								t_light *light)
{
	t_vector3d	v_refle;
	t_vector3d	v_cam;
	float		max_value;
	float		spec_intensity;

	v_refle = reflection(hit, light);
	v_cam = normalize(subtract_vectors(scene->camera.camera_position, \
				hit.intersec_point));
	max_value = fmax(0.0f, dot_product(v_refle, v_cam));
	spec_intensity = pow(max_value, 150.0f);
	return (scale_color(light->color, spec_intensity * light->ratio));
}

static t_rgb_color	diff_color(t_intersec_info hit, t_light *light)
{
	t_vector3d	light_dir;
	float		diff;

	light_dir = normalize(subtract_vectors(light->light_point, \
				hit.intersec_point));
	diff = fmax(0.0f, dot_product(hit.normal, light_dir));
	return (scale_color(light->color, (diff * light->ratio)));
}

t_rgb_color	evaluate_lighting_effect(t_intersec_info hit, t_scene *scene,
	t_light *light)
{
	t_rgb_color	diffuse;
	t_rgb_color	specular;

	diffuse = diff_color(hit, light);
	specular = spec_color(hit, scene, light);
	return (add_color(diffuse, specular));
}

bool	in_shadow(t_scene *scene, t_intersec_info hit, t_light *light)
{
	t_ray			shadow_ray;
	t_intersec_info	shadow_hit;
	t_vector3d		light_dir;
	float			light_distance;
	float			shadow_tolerance;

	light_dir = subtract_vectors(light->light_point, hit.over_point);
	light_distance = sqrtf(dot_product(light_dir, light_dir));
	light_dir = normalize(light_dir);
	shadow_ray.origin = hit.over_point;
	shadow_ray.direction = light_dir;
	shadow_hit = find_closest_interesection(&shadow_ray, scene);
	shadow_tolerance = light_distance * 0.001f;
	if (shadow_tolerance < SHADOW_EPSILON)
		shadow_tolerance = SHADOW_EPSILON;
	if (shadow_hit.intersection && \
		shadow_hit.dist_to_intersec < (light_distance - shadow_tolerance))
		return (true);
	return (false);
}
