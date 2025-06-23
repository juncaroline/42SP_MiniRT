#include "../../includes/minirt.h"

int	main(int ac, char **av)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (EXIT_FAILURE);
	scene->sphere = NULL;
	scene->sphere_count = 0;
	scene->plane = NULL;
	scene->plane_count = 0;
	scene->cylinder = NULL;
	scene->cylinder_count = 0;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./minirt <scene_file.rt>\n", 2);
		return (EXIT_FAILURE);
	}
	read_file(av[1], scene);
	init();
	// validate_elements(tokens, scene);
	return (EXIT_SUCCESS);
	// if (init() == EXIT_FAILURE)
	// {
	// 	ft_putstr_fd("Failed to initialize the window.\n", 2);
	// 	return (EXIT_FAILURE);
	// }
	// return (EXIT_SUCCESS);
}

// ./minirt ./sources/mandatory/scene.rt

// gcc check_elements.c check_objects.c error.c free.c main.c parse.c utils.c
// utils2.c validate_elements.c validate_param.c validate_param2.c
// ../../library/libft/libft.a -I../../includes -I../../library/libft -o scenetest