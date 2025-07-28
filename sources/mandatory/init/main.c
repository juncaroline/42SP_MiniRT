/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 14:23:48 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

int	main(int ac, char **av)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (EXIT_FAILURE);
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./minirt <scene_file.rt>\n", 2);
		free(scene);
		return (EXIT_FAILURE);
	}
	if (!read_file(av[1], scene))
	{
		free_scene(scene);
		free(scene);
		return (EXIT_FAILURE);
	}
	init_scene(scene);
	free_scene(scene);
	free(scene);
	return (EXIT_SUCCESS);
}
