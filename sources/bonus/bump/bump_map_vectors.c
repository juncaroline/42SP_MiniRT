/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_vectors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:43:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/18 18:19:23 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

t_vector3d	calc_vectors_sphere(t_vector3d normal, t_surface_mapping *bump)
{
	bump->tangent = (t_vector3d){-sinf(bump->u * 2 * M_PI), 0,
		cosf(bump->u * 2 * M_PI)};
	bump->bitangent = cross_product(normal, bump->tangent);
	bump->normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->normal = add_vectors(bump->normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->normal));
}

t_vector3d	calc_vectors_plane(t_vector3d normal, t_surface_mapping *bump)
{
	t_vector3d	temp;

	if (fabsf(normal.x) > 0.9f)
		temp = (t_vector3d){0, 1, 0};
	else
		temp = (t_vector3d){1, 0, 0};
	bump->tangent = normalize(cross_product(temp, normal));
	bump->bitangent = cross_product(normal, bump->tangent);
	bump->normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->normal = add_vectors(bump->normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->normal));
}

t_vector3d	calc_vectors_cylinder(t_vector3d normal, t_surface_mapping *bump,
	t_cylinder *cylinder)
{
	bump->tangent = normalize(cross_product(bump->bitangent, normal));
	bump->bitangent = normalize(cylinder->vector);
	bump->normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->normal = add_vectors(bump->normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->normal));
}

t_vector3d	calc_vectors_cone(t_vector3d normal, t_surface_mapping *bump,
	t_cone *cone)
{
	bump->tangent = normalize(cross_product(bump->bitangent, normal));
	bump->bitangent = normalize(cone->vector);
	bump->normal = add_vectors(normal,
			scalar_multiplication(bump->du, bump->tangent));
	bump->normal = add_vectors(bump->normal,
			scalar_multiplication(bump->dv, bump->bitangent));
	return (normalize(bump->normal));
}
