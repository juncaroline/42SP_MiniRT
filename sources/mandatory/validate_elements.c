#include "../../includes/minirt.h"

void	verify_elements(char *content, int i)
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
	if (ft_strcmp(tokens[0], "A") == 0)
		return (validate_ambient(tokens, count));
	else if (ft_strcmp(tokens[0], "C") == 0)
		return (validate_camera(tokens, count));
	else if (ft_strcmp(tokens[0], "L") == 0)
		return (validate_light(tokens, count));
	else if (ft_strcmp(tokens[0], "sp") == 0)
		return (validate_sphere(tokens, count));
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (validate_plane(tokens, count));
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (validate_cylinder(tokens, count));
	else if (!(ft_strcmp(tokens[0], "A") == 0 || ft_strcmp(tokens[0], "C") == 0 ||
			ft_strcmp(tokens[0], "L") == 0 || ft_strcmp(tokens[0], "sp") == 0 ||
			ft_strcmp(tokens[0], "pl") == 0 || ft_strcmp(tokens[0], "cy") == 0))
	{
		printf("Erro: Elemento desconhecido '%s'\n", tokens[0]);
		return (false);
	}
	return (true);
}
