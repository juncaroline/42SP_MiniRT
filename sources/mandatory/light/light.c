/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/24 13:29:47 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static t_rgb_color	diff_color(t_intersec_info hit, t_scene *scene)
{
	t_vector3d	light_dir;
	float		diff;

	light_dir = normalize(subtract_vectors(scene->light.light_point, \
				hit.intersec_point));
	diff = fmax(0.0f, dot_product(hit.normal, light_dir));
	return (scale_color(scene->ambient.color, (diff * scene->light.ratio)));
}

static bool	in_shadow(t_scene *scene, t_intersec_info hit, t_light *light)
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

static void	prepare_point(t_intersec_info *hit, t_ray ray)
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

t_rgb_color	apply_light(t_intersec_info hit, t_scene *scene, t_ray ray)
{
	t_rgb_color	final_color;
	t_rgb_color	ambient;
	t_rgb_color	diffuse;

	prepare_point(&hit, ray);
	if (!hit.intersection)
		return ((t_rgb_color){0, 0, 0});
	ambient = scale_color(hit.color, scene->ambient.ratio);
	final_color = ambient;
	if (!in_shadow(scene, hit, &scene->light))
	{
		diffuse = diff_color(hit, scene);
		final_color = add_color(ambient, diffuse);
	}
	return (final_color);
}
