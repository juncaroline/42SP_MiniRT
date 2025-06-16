#include "../../includes/minirt.h"

int	skip_spaces(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void    replace_with_spaces(char *line)
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

char    **split_line(char *line)
{
    char    **tokens;
    int     start;

    replace_with_spaces(line);
    start = skip_spaces(line);
    if (line[start] == '\n' || line[start] == '\0')
        return (NULL);
    tokens = ft_split(line + start, ' ');
    return (tokens);
}

void    verify_elements(char *content, int i)
{
    if (ft_strncmp(content + i, "A", 1) == 0)
        printf("Detected ambient light\n");
    else if (ft_strncmp(content + i, "C", 1) == 0)
        printf("Detected camera\n");
    else if (ft_strncmp(content + i, "L", 1) == 0)
        printf("Detected light source\n");
    else if (ft_strncmp(content + i, "sp", 2) == 0)
        printf("Detected sphere\n");
    else if (ft_strncmp(content + i, "pl", 2) == 0)
        printf("Detected plane\n");
    else if (ft_strncmp(content + i, "cy", 2) == 0)
        printf("Detected cylinder\n");
    else
        printf("Unknown element: %s\n", content);
}

bool	validate_elements(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	if (ft_strcmp(tokens[0], "A") == 0 && count != 3)
	{
		printf("Erro: A espera 2 parâmetros, recebeu %d\n", count - 1);
		return false;
	}
	else if (ft_strcmp(tokens[0], "C") == 0 && count != 4)
	{
		printf("Erro: C espera 3 parâmetros, recebeu %d\n", count - 1);
		return false;
	}
	else if (ft_strcmp(tokens[0], "L") == 0 && (count != 4 && count != 5))
	{
		printf("Erro: L espera 3 ou 4 parâmetros, recebeu %d\n", count - 1);
		return false;
	}
	else if (ft_strcmp(tokens[0], "sp") == 0 && count != 4)
	{
		printf("Erro: sp espera 3 parâmetros, recebeu %d\n", count - 1);
		return false;
	}
	else if (ft_strcmp(tokens[0], "pl") == 0 && count != 4)
	{
		printf("Erro: pl espera 3 parâmetros, recebeu %d\n", count - 1);
		return false;
	}
	else if (ft_strcmp(tokens[0], "cy") == 0 && count != 6)
	{
		printf("Erro: cy espera 5 parâmetros, recebeu %d\n", count - 1);
		return false;
	}
	else if (!(ft_strcmp(tokens[0], "A") == 0 || ft_strcmp(tokens[0], "C") == 0 ||
			ft_strcmp(tokens[0], "L") == 0 || ft_strcmp(tokens[0], "sp") == 0 ||
			ft_strcmp(tokens[0], "pl") == 0 || ft_strcmp(tokens[0], "cy") == 0))
	{
		printf("Erro: Elemento desconhecido '%s'\n", tokens[0]);
		return false;
	}
	return true;
}
