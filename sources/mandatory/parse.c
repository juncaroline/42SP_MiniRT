#include "../../includes/minirt.h"
// #include "../../library/libft/libft.h"
// #include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>

// void	read_file(char *scene) //original
// {
// 	int		fd;
// 	char	*content;
// 	int		len;

// 	len = ft_strlen(scene);
// 	if (len < 3 || scene[len - 3] != '.' || scene[len - 2] != 'r'
// 		|| scene[len - 1] != 't')
// 		error_msg(1);
// 	fd = open(scene, O_RDONLY);
// 	if (fd < 0)
// 		error_msg(2);
// 	content = get_next_line(fd);
// 	if (content == NULL)
// 		error_msg(3);
// 	free(content);
// 	get_next_line(-1);
// 	close(fd);
// }


int	skip_spaces(char *line)
{
	int	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	read_file(char *scene)
{
	int		fd;
	char	*content;
	int		len;
	int		i;
	char	**tokens;

	len = ft_strlen(scene);
	if (len < 3 || scene[len - 3] != '.' || scene[len - 2] != 'r'
		|| scene[len - 1] != 't')
		error_msg(1);
	fd = open(scene, O_RDONLY);
	if (fd < 0)
		error_msg(2);
	content = get_next_line(fd);
	if (content == NULL)
		error_msg(3);
	while (content)
	{
		i = skip_spaces(content);
		if (content[i] == '\n')
		{
			free(content);
			content = get_next_line(fd);
			continue;
		}
		tokens = ft_split(content + i, ' ');
		if (!tokens || !tokens[0])
		{
			printf("Erro ao dividir linha em tokens\n");
			free(content);
			content = get_next_line(fd);
			continue;
		}
		if (!validate_elements(tokens))
		{
			free_split(tokens);
			free(content);
			content = get_next_line(fd);
			continue;
		}
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
		free_split(tokens);
		free(content);
		content = get_next_line(fd);
	}
	close(fd);
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
	else if (ft_strcmp(tokens[0], "L") == 0 && count != 4)
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
	return true;
}

void	free_split(char **tokens)
{
	int	i = 0;
	if (!tokens)
		return;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
