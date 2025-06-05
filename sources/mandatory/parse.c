#include "../../includes/minirt.h"

void	read_file(char *map)
{
	int		fd;
	char	*content;

	if (ft_strnstr(map, ".rt", ft_strlen(map)) == NULL)
		error_msg(1);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_msg(2);
	content = get_next_line(fd);
	if (content == NULL)
		error_msg(3);
	free(content);
	get_next_line(-1);
	close(fd);
}
