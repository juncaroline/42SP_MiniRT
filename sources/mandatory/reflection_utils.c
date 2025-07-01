/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/01 11:18:30 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color scale_color(t_color c, float factor)
{
	return (t_color){
		.r = (int)(c.r * factor),
		.g = (int)(c.g * factor),
		.b = (int)(c.b * factor)
	};
}

t_color add_color(t_color a, t_color b)
{
	return (t_color){
		.r = a.r + b.r,
		.g = a.g + b.g,
		.b = a.b + b.b
	};
}

t_color clamp_color(t_color c)
{
	t_color clamped;
	clamped.r = fmin(255, fmax(0, c.r));
	clamped.g = fmin(255, fmax(0, c.g));
	clamped.b = fmin(255, fmax(0, c.b));
	return clamped;
}

t_color trace_ray(t_ray ray, t_scene *scene)
{
	t_intersection_info hit = find_closest_interesection(&ray, scene);

	if (!hit.intersection)
		return (t_color){0, 0, 0};  // fundo preto

	// Calcula luz ambiente
	t_color ambient = scale_color(hit.color, scene->ambient_ratio);

	// Calcula luz difusa (Lambert)
	t_vector3d light_dir = normalize(subtract_vectors(scene->light.pos, hit.intersec_point));
	float diff = fmax(0.0f, dot_product(hit.normal, light_dir));
	t_color diffuse = scale_color(scene->light.color, diff * scene->light.ratio);

	// Combina (clamp para 255)
	t_color final_color = add_color(ambient, diffuse);
	final_color = clamp_color(final_color);
	return final_color;

	// Luz especular:
	// Calcula o vetor de reflexão
	// Calcula o dot product com o vetor da câmera
	// Eleva à potência (ex: 32) para fazer o brilho concentrado
	// Multiplica pela intensidade e pela cor da luz
}

