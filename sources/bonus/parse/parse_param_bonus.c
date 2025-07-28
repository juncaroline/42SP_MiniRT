/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:39 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 14:35:36 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

static bool	is_rgb_color(t_rgb_color color_value)
{
	if (color_value.red < 0 || color_value.red > 255)
		return (parse_error("Invalid red color value."));
	if (color_value.green < 0 || color_value.green > 255)
		return (parse_error("Invalid green color value."));
	if (color_value.blue < 0 || color_value.blue > 255)
		return (parse_error("Invalid blue color value."));
	return (true);
}

static bool	rgb_error(char **rgb)
{
	parse_error("Invalid RGB color format.");
	free_split(rgb);
	return (false);
}

bool	parse_rgb(char *str, t_rgb_color *color_value)
{
	char		**rgb;
	int			i;

	color_value->red = 0;
	color_value->green = 0;
	color_value->blue = 0;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (parse_error("Failed to split RGB values."));
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (rgb_error(rgb));
	if (!ft_isnumber(rgb[0]) || !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2]))
		return (rgb_error(rgb));
	color_value->red = ft_atoi(rgb[0]);
	color_value->green = ft_atoi(rgb[1]);
	color_value->blue = ft_atoi(rgb[2]);
	free_split(rgb);
	return (is_rgb_color(*color_value));
}

bool	is_normalized_vector(t_vector3d vector_value)
{
	if (vector_value.x == 0.0 && vector_value.y == 0.0 && vector_value.z == 0.0)
		return (parse_error("Vector cannot be zero (0,0,0)."));
	if (vector_value.x < -1.0 || vector_value.x > 1.0)
		return (parse_error("Invalid x vector value."));
	if (vector_value.y < -1.0 || vector_value.y > 1.0)
		return (parse_error("Invalid y vector value."));
	if (vector_value.z < -1.0 || vector_value.z > 1.0)
		return (parse_error("Invalid z vector value."));
	return (true);
}
