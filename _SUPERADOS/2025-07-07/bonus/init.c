/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:09 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/01 14:45:45 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt_bonus.h"

void	esc_command(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	set_pixel(mlx_image_t *img, int x, int y, t_rgb_color c)
{
	size_t i = (y * img->width + x) * 4;
	img->pixels[i + 0] = c.red;
	img->pixels[i + 1] = c.green;
	img->pixels[i + 2] = c.blue;
	img->pixels[i + 3] = 255;
}

void	render(t_scene *scene, mlx_image_t *img)
{
	int	width;
	int	height;
	int	x;
	int	y;

	width = img->width;
	height = img->height;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			t_ray ray = generate_ray(x, y, &scene->camera);
			t_intersection_info hit = find_closest_interesection(&ray, scene);
			t_rgb_color final_color = {0, 0, 0};

			// POR ENQUANTO APENAS A COR DO OBJ
			if (hit.intersection)
				final_color = hit.color;
			set_pixel(img, x, y, final_color);
			x++;
		}
		y++;
	}
}

int32_t	init_scene(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT", false);
	if (!mlx)
		return (EXIT_FAILURE);
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	render(scene, img);
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

// int32_t	init(void)
// {
// 	mlx_t		*mlx;
// 	uint32_t	color;
// 	uint32_t	x;
// 	uint32_t	y;
// 	size_t		index;
// 	mlx_image_t	*img;

// 	mlx = mlx_init(500, 500, "MiniRT", false);
// 	if (!mlx)
// 		return (EXIT_FAILURE);
// 	img = mlx_new_image(mlx, 50, 50);
// 	if (!img)
// 	{
// 		mlx_terminate(mlx);
// 		return (EXIT_FAILURE);
// 	}
// 	color = 0xFF0000FF;
// 	x = 10;
// 	y = 10;
// 	index = (y * img->width + x) * 4;
// 	img->pixels[index + 0] = (color >> 24) & 0xFF;
// 	img->pixels[index + 1] = (color >> 16) & 0xFF;
// 	img->pixels[index + 2] = (color >> 8) & 0xFF;
// 	img->pixels[index + 3] = (color >> 0) & 0xFF;
// 	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
// 	{
// 		mlx_terminate(mlx);
// 		return (EXIT_FAILURE);
// 	}
// 	mlx_loop_hook(mlx, esc_command, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
