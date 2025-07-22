/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/22 16:45:23 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

t_rgb_color	scale_color(t_rgb_color c, float ratio)
{
	t_rgb_color	color;

	color.red = (int)(c.red * ratio);
	color.green = (int)(c.green * ratio);
	color.blue = (int)(c.blue * ratio);
	return (color);
}

t_rgb_color	max_color(t_rgb_color c)
{
	t_rgb_color	final;

	final.red = fmin(255, fmax(0, c.red));
	final.green = fmin(255, fmax(0, c.green));
	final.blue = fmin(255, fmax(0, c.blue));
	return (final);
}

t_rgb_color	add_color(t_rgb_color a, t_rgb_color b, t_rgb_color c)
{
	t_rgb_color	color;

	color.red = a.red + b.red + c.red;
	color.green = a.green + b.green + c.green;
	color.blue = a.blue + b.blue + c.blue;
	color = max_color(color);
	return (color);
}

t_rgb_color	diff_color(t_intersec_info hit, t_light *light)
{
	t_vector3d	light_dir;
	float		diff;

	light_dir = normalize(subtract_vectors(light->light_point, \
				hit.intersec_point));
	diff = fmax(0.0f, dot_product(hit.normal, light_dir));
	return (scale_color(light->color, (diff * light->ratio)));
}

t_vector3d	reflection(t_intersec_info hit, t_light *light)
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

t_rgb_color	spec_color(t_intersec_info hit, t_scene *scene, t_material mat, \
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
	spec_intensity = pow(max_value, mat.shininess);
	return (scale_color(light->color, spec_intensity * light->ratio));
}

t_rgb_color	evaluate_lighting_effect(t_intersec_info hit, t_scene *scene,
	t_light *light, t_material material)
{
	t_rgb_color	diffuse;
	t_rgb_color	specular;

	diffuse = diff_color(hit, light);
	specular = spec_color(hit, scene, material, light);
	return (add_color(diffuse, specular, (t_rgb_color){0, 0, 0}));
}

t_rgb_color	loop_color(t_intersec_info hit, t_scene *scene, \
						t_rgb_color ambient, t_material material)
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
			light_contribution = evaluate_lighting_effect(hit, scene,
					light, material);
			final_color = add_color(final_color, light_contribution,
					(t_rgb_color){0, 0, 0});
		}
		i++;
	}
	return (final_color);
}

t_rgb_color	color_without_shadow(t_intersec_info hit, t_scene *scene,
	t_material material, t_light *light)
{
	t_rgb_color	final_color;
	t_rgb_color	diffuse;
	t_rgb_color	specular;

	diffuse = diff_color(hit, light);
	material.shininess = 50;
	specular = spec_color(hit, scene, material, light);
	final_color = add_color(diffuse, specular, (t_rgb_color){0, 0, 0});
	return (final_color);
}

t_rgb_color	apply_light(t_intersec_info hit, t_scene *scene, t_ray ray)
{
	t_rgb_color	final_color;
	t_rgb_color	ambient;
	t_material	material;

	prepare_point(&hit, ray);
	if (!hit.intersection)
		return ((t_rgb_color){0, 0, 0});
	material.shininess = 50.0f;
	ambient = scale_color(hit.color, scene->ambient.ratio);
	final_color = loop_color(hit, scene, ambient, material);
	return (final_color);
}
