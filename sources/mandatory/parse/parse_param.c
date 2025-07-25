/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:39 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/25 16:21:04 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	is_rgb_color(t_rgb_color color_value)
{
	if (color_value.red < 0 || color_value.red > 255)
		return (parse_error("Invalid red color value."));
	if (color_value.green < 0 || color_value.green > 255)
		return (parse_error("Invalid green color value."));
	if (color_value.blue < 0 || color_value.blue > 255)
		return (parse_error("Invalid blue color value."));
	return (true);
}

static t_rgb_color	rgb_error(char **rgb, t_rgb_color color_value)
{
	parse_error("Invalid RGB color format.");
	free_split(rgb);
	return (color_value);
}

t_rgb_color	parse_rgb(char *str)
{
	char		**rgb;
	int			i;
	t_rgb_color	color_value;

	color_value.red = 0;
	color_value.green = 0;
	color_value.blue = 0;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (color_value);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (rgb_error(rgb, color_value));
	if (!ft_isnumber(rgb[0]) || !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2]))
		return (rgb_error(rgb, color_value));
	color_value.red = ft_atoi(rgb[0]);
	color_value.green = ft_atoi(rgb[1]);
	color_value.blue = ft_atoi(rgb[2]);
	free_split(rgb);
	return (color_value);
}

bool	is_normalized_vector(t_vector3d vector_value)
{
	if (vector_value.x < -1.0 || vector_value.x > 1.0)
		return (parse_error("Invalid x vector value."));
	if (vector_value.y < -1.0 || vector_value.y > 1.0)
		return (parse_error("Invalid y vector value."));
	if (vector_value.z < -1.0 || vector_value.z > 1.0)
		return (parse_error("Invalid z vector value."));
	return (true);
}
