/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:41 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 11:04:29 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void	validate_coordinates(char *str, char **coords)
{
	int	i;

	if (!str || *str == '\0')
	{
		parse_error("No coordinates provided.");
		exit(1);
	}
	if (!coords)
	{
		parse_error("Failed to split coordinates.");
		exit(1);
	}
	i = 0;
	while (coords[i])
		i++;
	if (i != 3 || !ft_isfloat(coords[0]) || !ft_isfloat(coords[1])
		|| !ft_isfloat(coords[2]))
	{
		parse_error("Invalid coordinates format.");
		free_split(coords);
		exit(1);
	}
}

t_vector3d	parse_coordinates(char *str)
{
	char		**coords;
	t_vector3d	coords_value;

	coords_value.x = 0.0;
	coords_value.y = 0.0;
	coords_value.z = 0.0;
	coords = ft_split(str, ',');
	validate_coordinates(str, coords);
	coords_value.x = string_to_float(coords[0]);
	coords_value.y = string_to_float(coords[1]);
	coords_value.z = string_to_float(coords[2]);
	free_split(coords);
	return (coords_value);
}

float	parse_fov(char *str)
{
	int	fov_value;

	if (!ft_isnumber(str))
		return (parse_error("Invalid FOV format."));
	fov_value = ft_atoi(str);
	if (fov_value < 0 || fov_value > 180)
		return (parse_error("Invalid FOV value."));
	return ((float)fov_value);
}

bool	parse_ratio(char *str, float *ratio)
{
	if (!ft_isfloat(str))
		return (parse_error("Invalid ratio format."));
	*ratio = string_to_float(str);
	if (*ratio < 0.0 || *ratio > 1.0)
		return (parse_error("Invalid ratio value."));
	return (true);
}

float	parse_measurements(char *str)
{
	float	value;

	if (!ft_isfloat(str))
		return (parse_error("Invalid measurement format."));
	value = string_to_float(str);
	if (value <= 0)
		return (parse_error("Invalid measurement value."));
	return (value);
}
