#include "../../includes/minirt.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./minirt <scene_file.rt>\n", 2);
		return (EXIT_FAILURE);
	}
	read_file(av[1]);
	return (EXIT_SUCCESS);
	// validate_elements(tokens);
	// if (init() == EXIT_FAILURE)
	// {
	// 	ft_putstr_fd("Failed to initialize the window.\n", 2);
	// 	return (EXIT_FAILURE);
	// }
	// return (EXIT_SUCCESS);
}

// ./minirt ./sources/mandatory/scene.rt
// gcc check_elements.c check_objects.c error.c free.c main.c parse.c utils.c utils2.c validate_elements.c validate_param.c validate_param2.c ../../library/libft/libft.a -I../../includes -I../../library/libft -o scenetest