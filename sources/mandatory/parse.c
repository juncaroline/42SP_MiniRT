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
		free(content);
		content = get_next_line(fd);
	}
	close(fd);
}
