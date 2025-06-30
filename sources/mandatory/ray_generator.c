/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:31 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 09:27:32 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector3d	normalize(t_vector3d vector)
{
	float		magnitude;
	t_vector3d	result;

	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z);
	if (magnitude == 0.0f)
	{
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
		return (result);
	}
	else
	{
		result.x = vector.x / magnitude;
		result.y = vector.y / magnitude;
		result.z = vector.z / magnitude;
	}
	return (result);
}

t_cam_basis	camera_basis(t_camera *cam)
{
	t_cam_basis	basis;
	t_vector3d	w_temp;
	t_vector3d	u_temp;
	t_vector3d	v_temp;
	t_vector3d	world_up;

	w_temp = negative_vector(cam->camera_direction);
	basis.w = normalize(w_temp);
	world_up.x = 0.0f;
	world_up.y = 1.0f;
	world_up.z = 0.0f;
	u_temp = cross_product(world_up, basis.w);
	basis.u = normalize(u_temp);
	v_temp = cross_product(basis.w, basis.u);
	basis.v = normalize(v_temp);
	return (basis);
}
