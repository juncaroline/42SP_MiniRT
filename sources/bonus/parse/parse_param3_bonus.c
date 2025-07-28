/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:36:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 14:36:40 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

static bool	validate_and_parse_vector(char **vector, t_vector3d *vector_value)
{
	int	i;

	i = 0;
	while (vector[i])
		i++;
	if (i != 3 || !ft_isfloat(vector[0]) || !ft_isfloat(vector[1])
		|| !ft_isfloat(vector[2]))
	{
		parse_error("Invalid vector format.");
		return (false);
	}
	vector_value->x = string_to_float(vector[0]);
	vector_value->y = string_to_float(vector[1]);
	vector_value->z = string_to_float(vector[2]);
	if (vector_value->x == 0.0 && vector_value->y == 0.0
		&& vector_value->z == 0.0)
		return (false);
	return (true);
}

t_vector3d	parse_normalized_vector(char *str)
{
	char		**vector;
	t_vector3d	vector_value;

	vector_value.x = 0.0;
	vector_value.y = 0.0;
	vector_value.z = 0.0;
	vector = ft_split(str, ',');
	if (!vector)
		return (vector_value);
	if (!validate_and_parse_vector(vector, &vector_value))
	{
		free_split(vector);
		vector_value.x = 0.0;
		vector_value.y = 0.0;
		vector_value.z = 0.0;
		return (vector_value);
	}
	free_split(vector);
	return (vector_value);
}
