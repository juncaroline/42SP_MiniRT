/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/01 18:30:26 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// shininess [10, 200];
typedef struct s_material
{
	char		*type;
	t_rgb_color	color;
	float		reflective;
	float		transparency;
	float		refractive_index;
	float		shininess;
}	t_material;

// typedef struct s_scene
// {
// 	t_ambient	ambient;
// 	t_camera	camera;

// 	t_light		*light;
// 	int			light_count;

// 	t_sphere	*sphere;
// 	int			sphere_count;
// 	t_plane		*plane;
// 	int			plane_count;
// 	t_cylinder	*cylinder;
// 	int			cylinder_count;
// }	t_scene;

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

t_rgb_color	diff_color(t_intersection_info hit, t_light *light)
{
	t_vector3d	light_dir;
	float		diff;

	light_dir = normalize(subtract_vectors(light->light_point, \
				hit.intersec_point));
	diff = fmax(0.0f, dot_product(hit.normal, light_dir));
	return (scale_color(light->color, (diff * light->ratio)));
}

t_vector3d	reflection(t_intersection_info hit, t_light *light)
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

t_rgb_color	spec_color(t_intersection_info hit, t_scene *scene, t_material mat \
						t_light *light)
{
	t_vector3d	v_refle;
	t_vector3d	v_cam;
	double		max_value;
	float		prod;

	v_refle = reflection(hit, light);
	v_cam = normalize(subtract_vectors(scene->camera.camera_position, \
				hit.intersec_point));
	max_value = fmax(0.0f, dot_product(v_refle, v_cam));
	prod = pow(max_value, mat.shininess);
	return (scale_color(scene->light.color, pow(max_value, mat.shininess)));
}


t_rgb_color	loop_color(t_intersection_info hit, t_scene *scene, \
						t_rgb_color ambient, t_material material)
{
	t_rgb_color	final_color;
	t_rgb_color	diffuse;
	t_rgb_color	specular;

	t_light		*light;
	int			i;

	i = 0;
	final_color = ambient;
	while (i < scene->light_count)
	{
		light = &scene->light[i];
		if (in_shadow(scene, hit, light))
			continue ;

		diffuse = diff_color(hit, light);

		material.shininess = 50;

		specular = spec_color(hit, scene, material, light);
		final_color = add_color(final_color, diffuse, specular);
		i++;
	}
	return (final_color);
}

t_rgb_color	get_color(t_intersection_info hit, t_scene *scene)
{
	t_rgb_color	final_color;
	t_rgb_color	ambient;
	t_rgb_color	diffuse;
	t_rgb_color	specular;

	t_material	material;

	if (!hit.intersection)
	{
		final_color = (t_rgb_color){0, 0, 0};
		return (final_color);
	}
	ambient = scale_color(hit.color, scene->ambient.ratio);

	final_color = loop_color(hit, scene, ambient, material);
	return (final_color);
}

// VERSAO COM SOMBRA E MULTI-LIGHTS

// t_rgb_color	get_color(t_intersection_info hit, t_scene *scene)
// {
// 	t_rgb_color	final_color;
// 	t_rgb_color	ambient;
// 	t_rgb_color	diffuse;
// 	t_rgb_color	specular;

// 	if (!hit.intersection)
// 	{
// 		final_color = (t_rgb_color){0, 0, 0};
// 		return (final_color);
// 	}
// 	ambient = scale_color(hit.color, scene->ambient.ratio);
// 	final_color = ambient;

// 	int	i = 0;
// 	while (i < scene->light_count)
// 	{
// 		t_light	*light = &scene->light[i];
// 		if (in_shadow(scene, hit, light))
// 			continue ;

// 		diffuse = diff_color(hit, light);

// 		t_material	material;
// 		material.shininess = 50;

// 		specular = spec_color(hit, scene, material, light);
// 		final_color = add_color(final_color, diffuse, specular);
// 		i++;
// 	}
// 	return (final_color);
// }


// PRIMEIRA VERSAO

// t_rgb_color	get_color(t_intersection_info hit, t_scene *scene)
// {
// 	t_rgb_color	final_color;
// 	t_rgb_color	ambient;
// 	t_rgb_color	diffuse;
// 	t_rgb_color	specular;

// 	if (!hit.intersection)
// 	{
// 		final_color = (t_rgb_color){0, 0, 0};
// 		return (final_color);
// 	}
// 	ambient = scale_color(hit.color, scene->ambient.ratio);
// 	diffuse = diff_color(hit, scene);

// 	t_material	material;

// 	material.shininess = 50;
// 	specular = spec_color(hit, scene, material);
// 	final_color = add_color(ambient, diffuse, specular);
// 	return (final_color);
// }
