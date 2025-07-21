/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:25 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/21 11:38:09 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

t_vector3d	add_vectors(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3d	cross_product(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector3d	subtract_vectors(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3d	scalar_multiplication(float k, t_vector3d vector)
{
	t_vector3d	result;

	result.x = k * vector.x;
	result.y = k * vector.y;
	result.z = k * vector.z;
	return (result);
}

float	dot_product(t_vector3d a, t_vector3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
