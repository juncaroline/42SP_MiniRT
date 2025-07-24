/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:35 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/24 18:03:25 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_isfloat(const char *str)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (false);
			has_dot = true;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

float	string_to_float(char *str)
{
	float	result;
	float	div;
	char	*dec_pos;
	int		sign;

	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	result = (float)ft_atoi(str);
	dec_pos = str;
	while (*dec_pos && *dec_pos != '.')
		dec_pos++;
	if (*dec_pos == '.')
	{
		dec_pos++;
		div = 1.0;
		while (*dec_pos >= '0' && *dec_pos <= '9')
		{
			div *= 10.0;
			result += (*dec_pos - '0') / div;
			dec_pos++;
		}
	}
	return (result * sign);
}
