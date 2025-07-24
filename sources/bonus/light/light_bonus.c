/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/24 13:24:35 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

static t_rgb_color	loop_color(t_intersec_info hit, t_scene *scene, \
								t_rgb_color ambient)
{
	t_rgb_color	final_color;
	t_rgb_color	light_contribution;
	t_light		*light;
	int			i;

	final_color = ambient;
	i = 0;
	while (i < scene->light_count)
	{
		light = &scene->light[i];
		if (!in_shadow(scene, hit, light))
		{
			light_contribution = evaluate_lighting_effect(hit, scene, light);
			final_color = add_color(final_color, light_contribution);
		}
		i++;
	}
	return (final_color);
}

static void	prepare_point(t_intersec_info *hit, t_ray ray)
{
	t_vector3d	eyev;
	float		bias_factor;
	float		angle_factor;

	if (!hit || !hit->intersection)
		return ;
	eyev = scalar_multiplication(-1, ray.direction);
	if (dot_product(hit->normal, eyev) < 0)
		hit->normal = scalar_multiplication(-1, hit->normal);
	angle_factor = fabs(dot_product(hit->normal, eyev));
	bias_factor = SHADOW_EPSILON;
	if (angle_factor < 0.1f)
		bias_factor = SHADOW_EPSILON * 5.0f;
	else if (angle_factor < 0.3f)
		bias_factor = SHADOW_EPSILON * 2.0f;
	hit->over_point = add_vectors(hit->intersec_point, \
		scalar_multiplication(bias_factor, hit->normal));
}

t_rgb_color	apply_light(t_intersec_info hit, t_scene *scene, t_ray ray)
{
	t_rgb_color	final_color;
	t_rgb_color	ambient;

	prepare_point(&hit, ray);
	if (!hit.intersection)
		return ((t_rgb_color){0, 0, 0});
	ambient = scale_color(hit.color, scene->ambient.ratio);
	final_color = loop_color(hit, scene, ambient);
	return (final_color);
}
