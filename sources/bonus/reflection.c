/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:40:08 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/01 14:45:45 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"
#include <math.h>

typedef struct s_material
{
	t_rgb_color	color;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
} t_material;

typedef struct s_sphere
{
	t_vector3d	sphere_center;
	float		diameter;
	t_rgb_color	color;

	t_material	material;

}	t_sphere;

typedef struct s_point_light
{
	t_vector3d	position;
	t_rgb_color	intensity;
}	t_point_light;

t_rgb_color;

t_vector3d	reflection(t_vector3d ray_in, t_vector3d normal)
{
	float	nbr;
	t_vector3d	tmp;

	nbr = 2 * dot_product(ray_in, normal);
	tmp = scalar_multiplication(nbr, normal);
	return (subtract_vectors(ray_in, tmp));
}

bool	valid_material(t_material	*m)
{
	if (m && (m->ambient >= 0 && m->ambient <= 1) && \
		(m->diffuse >= 0 && m->diffuse <= 1) && \
		(m->specular >= 0 && m->specular <= 1) && \
		(m->shininess >= 10 && m->shininess <= 200))
		return (true);
	return (false);
}



int	main(void)
{
	// REFLEXAO
	// raio incidindo em 45 graus
	// t_vector3d	in = {1, -1, 0};
	// t_vector3d	normal = {0, 1, 0};

	// ponto de luz escondido
	// t_vector3d	in = {0, -1, 0};
	// t_vector3d	normal = {(sqrt(2) / 2.0), (sqrt(2) / 2.0), 0};
	// t_vector3d	result;
	
	// result = reflection(in, normal);
	// printf("Vetor (%.0f, %.0f, %.0f)\n", result.x, result.y, result.z);
	
	// PONTO DE LUZ
	t_point_light	light = {{0, 0, 0}, {1, 1, 1}};
	t_material	m;

	m.color = (t_rgb_color){1, 1, 1};
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	
	// printf("Light position (%.0f, %.0f, %.0f)\n", light.position.x, light.position.y, light.position.z);
	// printf("Light i\n");
	return (0);
}