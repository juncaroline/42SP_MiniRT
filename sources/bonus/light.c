/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/10 13:10:34 by cabo-ram         ###   ########.fr       */
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

t_rgb_color	add_color(t_rgb_color a, t_rgb_color b)
{
	t_rgb_color	color;

	color.red = a.red + b.red;
	color.green = a.green + b.green;
	color.blue = a.blue + b.blue;
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

t_rgb_color	get_color(t_intersec_info hit, t_scene *scene)
{
	t_rgb_color	final_color;
	t_rgb_color	ambient;
	t_rgb_color	diffuse;
	int			i;

	if (!hit.intersection)
	{
		final_color = (t_rgb_color){0, 0, 0};
		return (final_color);
	}
	
	// Luz ambiente
	ambient = scale_color(hit.color, scene->ambient.ratio);
	final_color = ambient;
	
	// Para cada luz na cena
	i = 0;
	while (i < scene->light_count)
	{
		diffuse = diff_color(hit, &scene->light[i]);
		final_color = add_color(final_color, diffuse);
		i++;
	}
	
	return (final_color);
}
