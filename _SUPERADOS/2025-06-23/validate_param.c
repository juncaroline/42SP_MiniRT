#include "../../includes/minirt.h"

bool	validate_rgb(char *str)
{
	char	**rgb;
	int		i;
	int		value;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (false);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		free_split(rgb);
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_isnumber(rgb[i]))
		{
			free_split(rgb);
			return (false);
		}
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
		{
			free_split(rgb);
			return (false);
		}
		i++;
	}
	free_split(rgb);
	return (true);
}

bool	validate_normalize_vector(char *str)
{
	char	**vector;
	int		i;
	float	vector_value;

	vector = ft_split(str, ',');
	if (!vector)
		return (false);
	i = 0;
	while (vector[i])
		i++;
	if (i != 3)
	{
		free_split(vector);
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_isfloat(vector[i]))
		{
			free_split(vector);
			return (false);
		}
		vector_value = string_to_float(vector[i]);
		if (vector_value < -1.0 || vector_value > 1.0)
		{
			free_split(vector);
			return (false);
		}
		i++;
	}
	free_split(vector);
	return (true);
}

bool	validate_coordinates(char *str)
{
	char	**coords;
	int		i;

	coords = ft_split(str, ',');
	if (!coords)
		return (false);
	i = 0;
	while (coords[i])
		i++;
	if (i != 3)
	{
		free_split(coords);
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_isfloat(coords[i]))
		{
			free_split(coords);
			return (false);
		}
		i++;
	}
	free_split(coords);
	return (true);
}
