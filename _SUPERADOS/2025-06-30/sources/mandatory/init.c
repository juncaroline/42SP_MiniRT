/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:09 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/06/30 09:27:10 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	esc_command(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int32_t	init(void)
{
	mlx_t		*mlx;
	uint32_t	color;
	uint32_t	x;
	uint32_t	y;
	size_t		index;
	mlx_image_t	*img;

	mlx = mlx_init(500, 500, "MiniRT", false);
	if (!mlx)
		return (EXIT_FAILURE);
	img = mlx_new_image(mlx, 50, 50);
	if (!img)
	{
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	color = 0xFF0000FF;
	x = 10;
	y = 10;
	index = (y * img->width + x) * 4;
	img->pixels[index + 0] = (color >> 24) & 0xFF;
	img->pixels[index + 1] = (color >> 16) & 0xFF;
	img->pixels[index + 2] = (color >> 8) & 0xFF;
	img->pixels[index + 3] = (color >> 0) & 0xFF;
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, esc_command, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
