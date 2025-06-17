#include "../../includes/minirt.h"

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
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
