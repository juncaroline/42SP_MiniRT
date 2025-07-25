/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:35 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/25 16:12:28 by cabo-ram         ###   ########.fr       */
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

static bool	process_digit(char c, bool *has_dot, bool *has_digit_before_dot,
	bool *has_digit_after_dot)
{
	if (c == '.')
	{
		if (*has_dot || !*has_digit_before_dot)
			return (false);
		*has_dot = true;
	}
	else if (!ft_isdigit(c))
		return (false);
	else if (!*has_dot)
		*has_digit_before_dot = true;
	else
		*has_digit_after_dot = true;
	return (true);
}

bool	ft_isfloat(const char *str)
{
	int		i;
	bool	has_dot;
	bool	has_digit_before_dot;
	bool	has_digit_after_dot;

	i = 0;
	has_dot = false;
	has_digit_before_dot = false;
	has_digit_after_dot = false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!process_digit(str[i], &has_dot, &has_digit_before_dot,
				&has_digit_after_dot))
			return (false);
		i++;
	}
	if (has_dot && !has_digit_after_dot)
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
