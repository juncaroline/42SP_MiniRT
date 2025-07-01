/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/01 12:32:37 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

t_rgb_color	diff_color(t_intersection_info hit, t_scene *scene)
{
	t_vector3d	light_dir;
	float		diff;

	light_dir = normalize(subtract_vectors(scene->light.light_point , \
				hit.intersec_point));
	diff = fmax(0.0f, dot_product(hit.normal, light_dir));
	return (scale_color(scene->light.color, (diff * scene->light.ratio)));
}

t_rgb_color	get_color(t_intersection_info hit, t_scene *scene)
{
	t_rgb_color	final_color;
	t_rgb_color	ambient;
	t_rgb_color	diffuse;
	// t_rgb_color	specular;

	if (!hit.intersection)
	{
		final_color = (t_rgb_color){0, 0, 0};
		return (final_color);
	}

	ambient = scale_color(hit.color, scene->ambient.ratio);
	diffuse = diff_color(hit, scene);

	final_color = add_color(ambient, diffuse);
	return (final_color);

	// Luz especular:
	// Calcular o vetor de reflexão
	// Calcular o dot product com o vetor da câmera
	// Eleva à potência (ex: 32) para fazer o brilho concentrado
	// Multiplica pela intensidade e pela cor da luz
}