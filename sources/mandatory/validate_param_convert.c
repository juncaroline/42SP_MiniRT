#include "../../includes/minirt.h"

bool	is_rgb_color(t_rgb_color color_value)
{
	if (color_value.red < 0 || color_value.red > 255)
		return (false);
	if (color_value.green < 0 || color_value.green > 255)
		return (false);
	if (color_value.blue < 0 || color_value.blue > 255)
		return (false);
	return (true);
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
	{
		free_split(rgb);
		return (color_value);
	}
	if (!ft_isnumber(rgb[0]) || !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2]))
	{
		free_split(rgb);
		return (color_value);
	}
	color_value.red = ft_atoi(rgb[0]);
	color_value.green = ft_atoi(rgb[1]);
	color_value.blue = ft_atoi(rgb[2]);
	free_split(rgb);
	return (color_value);
}

// example of usage
// t_rgb_color	color_value = parse_rgb("255,100,50");
// if (!is_rgb_color(color_value))
// 	printf("Cor inválida\n");

bool	normalized_vector(t_normalized_vector vector_value)
{
	if (vector_value.x < -1.0 || vector_value.x > 1.0)
		return (false);
	if (vector_value.y < -1.0 || vector_value.y > 1.0)
		return (false);
	if (vector_value.z < -1.0 || vector_value.z > 1.0)
		return (false);
	return (true);
}

t_normalized_vector	parse_normalize_vector(char *str)
{
	char				**vector;
	int					i;
	t_normalized_vector	vector_value;

	vector_value.x = 0.0;
	vector_value.y = 0.0;
	vector_value.z = 0.0;
	vector = ft_split(str, ',');
	if (!vector)
		return (vector_value);
	i = 0;
	while (vector[i])
		i++;
	if (i != 3 || !ft_isfloat(vector[0]) || !ft_isfloat(vector[1])
		|| !ft_isfloat(vector[2]))
	{
		free_split(vector);
		return (vector_value);
	}
	vector_value.x = string_to_float(vector[0]);
	vector_value.y = string_to_float(vector[1]);
	vector_value.z = string_to_float(vector[2]);
	free_split(vector);
	return (vector_value);
}

//example of usage
// t_normalized_vector	dir = parse_vector("0.0,1.0,0.5");
// if (!is_normalized_vector(dir))
// {
// 	printf("Direção inválida\n");
// }

t_coordinates	parse_coordinates(char *str)
{
	char			**coords;
	int				i;
	t_coordinates	coords_value;

	coords_value.x = 0.0;
	coords_value.y = 0.0;
	coords_value.z = 0.0;
	coords = ft_split(str, ',');
	if (!coords)
		return (coords_value);
	i = 0;
	while (coords[i])
		i++;
	if (i != 3 || !ft_isfloat(coords[0]) || !ft_isfloat(coords[1])
		|| !ft_isfloat(coords[2]))
	{
		free_split(coords);
		return (coords_value);
	}
	coords_value.x = string_to_float(coords[0]);
	coords_value.y = string_to_float(coords[1]);
	coords_value.z = string_to_float(coords[2]);
	free_split(coords);
	return (coords_value);
}
