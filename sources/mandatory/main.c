/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/06 19:18:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free(scene);
		return (EXIT_FAILURE);
	}
	read_file(av[1], scene);
	init_scene(scene);
	free_scene(scene);
	free(scene);
	return (EXIT_SUCCESS);
}

// int	main(int ac, char **av)
// {
// 	t_scene	*scene;

// 	scene = malloc(sizeof(t_scene));
// 	if (!scene)
// 		return (EXIT_FAILURE);
// 	scene->sphere = NULL;
// 	scene->sphere_count = 0;
// 	scene->plane = NULL;
// 	scene->plane_count = 0;
// 	scene->cylinder = NULL;
// 	scene->cylinder_count = 0;
// 	if (ac != 2)
// 	{
// 		ft_putstr_fd("Usage: ./minirt <scene_file.rt>\n", 2);
// 		free(scene);
// 		return (EXIT_FAILURE);
// 	}
// 	read_file(av[1], scene);
// 	init_scene(scene);
// 	// init();
// 	// validate_elements(tokens, scene);
// 	free_scene(scene);
// 	free(scene);
// 	return (EXIT_SUCCESS);
// 	// if (init() == EXIT_FAILURE)
// 	// {
// 	// 	ft_putstr_fd("Failed to initialize the window.\n", 2);
// 	// 	return (EXIT_FAILURE);
// 	// }
// 	// return (EXIT_SUCCESS);
// }

// ./minirt ./sources/mandatory/scene.rt

// valgrind --leak-check=full --suppressions=suppress_mlx_error.sup