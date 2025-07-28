/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:35 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 10:44:39 by cabo-ram         ###   ########.fr       */
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

static bool	process_digit(char c, bool *has_dot, bool *is_int,
	bool *is_decimal)
{
	if (c == '.')
	{
		if (*has_dot)
			return (false);
		if (!*is_int)
			return (false);
		*has_dot = true;
	}
	else if (!ft_isdigit(c))
		return (false);
	else if (!*has_dot)
		*is_int = true;
	else
		*is_decimal = true;
	return (true);
}

bool	ft_isfloat(const char *str)
{
	int		i;
	bool	has_dot;
	bool	is_int;
	bool	is_decimal;

	i = 0;
	has_dot = false;
	is_int = false;
	is_decimal = false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!process_digit(str[i], &has_dot, &is_int,
				&is_decimal))
			return (false);
		i++;
	}
	if (has_dot && !is_decimal)
		return (false);
	return (true);
}

static float	verify_decimal(char *str)
{
	float	div;
	char	*dec_pos;
	float	result;

	dec_pos = str;
	div = 1.0;
	result = 0.0;
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
	return (result);
}

float	string_to_float(char *str)
{
	float	result;
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
	result += verify_decimal(str);
	return (result * sign);
}
