#include "../../includes/minirt.h"

bool	validate_fov(char *str)
{
	int	fov_value;

	if (!ft_isnumber(str))
		return (false);
	fov_value = ft_atoi(str);
	if (fov_value < 0 || fov_value > 180)
		return (false);
	return (true);
}

bool	validate_ratio(char *str)
{
	float	ratio;

	if (!ft_isfloat(str))
		return (false);
	ratio = string_to_float(str);
	if (ratio < 0.0 || ratio > 1.0)
		return (false);
	return (true);
}

bool	validate_measurements(char *str)
{
	float	value;

	if (!ft_isfloat(str))
		return (false);
	value = string_to_float(str);
	if (value <= 0)
		return (false);
	return (true);
}
