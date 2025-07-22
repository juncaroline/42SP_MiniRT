/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_generic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/22 17:48:50 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

t_vector3d	apply_bump_map(t_intersec_info hit)
{
	t_vector3d	perturbation;
	t_vector3d	new_vector;
	float		scale;

	scale = 0.3f;
	perturbation.x = sinf(hit.intersec_point.y * 10.0f) * scale;
	perturbation.y = cosf(hit.intersec_point.x * 10.0f) * scale;
	perturbation.z = sinf(hit.intersec_point.z * 10.0f) * scale;
	new_vector = add_vectors(hit.normal, perturbation);
	return (normalize(new_vector));
}
