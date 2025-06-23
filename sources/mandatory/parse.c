#include "../../includes/minirt.h"

void	check_file_extension(char *extension)
{
	int	len;

	len = ft_strlen(extension);
	if (len < 3 || extension[len - 3] != '.' || extension[len - 2] != 'r'
		|| extension[len - 1] != 't')
		error_msg(1);
}

void	read_file(char *scene_file, t_scene *scene)
{
	int		fd;
	char	*content;
	int		i;
	char	**tokens;

	check_file_extension(scene_file);
	fd = open(scene_file, O_RDONLY);
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
			continue ;
		}
		tokens = split_line(content);
		if (!tokens || !tokens[0])
		{
			printf("Erro ao dividir linha em tokens\n");
			free(content);
			content = get_next_line(fd);
			continue ;
		}
		if (!validate_elements(tokens, scene))
		{
			free_split(tokens);
			free(content);
			content = get_next_line(fd);
			continue ;
		}
		verify_elements(content, i);
		free_split(tokens);
		free(content);
		content = get_next_line(fd);
	}
	close(fd);
}
