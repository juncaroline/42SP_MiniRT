#include "../../includes/minirt.h"

float	parse_fov(char *str)
{
	int	fov_value;

	if (!ft_isnumber(str))
		return (0.0);
	fov_value = ft_atoi(str);
	if (fov_value < 0 || fov_value > 180)
		return (0.0);
	return ((float)fov_value);
}

float	parse_ratio(char *str)
{
	float	ratio;

	if (!ft_isfloat(str))
		return (0.0);
	ratio = string_to_float(str);
	if (ratio < 0.0 || ratio > 1.0)
		return (0.0);
	return (ratio);
}

float	parse_measurements(char *str)
{
	float	value;

	if (!ft_isfloat(str))
		return (0.0);
	value = string_to_float(str);
	if (value <= 0)
		return (0.0);
	return (value);
}
