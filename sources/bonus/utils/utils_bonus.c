/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:33 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 15:12:58 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	ignore_end_spaces(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
		len--;
	line[len] = '\0';
}

void	replace_with_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

char	**split_line(char *line)
{
	char	**tokens;
	int		start;
	int		i;
	char	*new_line;

	replace_with_spaces(line);
	ignore_end_spaces(line);
	start = skip_spaces(line);
	if (line[start] == '\n' || line[start] == '\0')
		return (NULL);
	tokens = ft_split(line + start, ' ');
	i = 0;
	while (tokens && tokens[i])
	{
		new_line = ft_strchr(tokens[i], '\n');
		if (new_line)
			*new_line = '\0';
		i++;
	}
	return (tokens);
}
