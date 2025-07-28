/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:09 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 15:42:10 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

void	esc_command(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	set_pixel(mlx_image_t *img, int x, int y, t_rgb_color c)
{
	size_t	i;

	i = (y * img->width + x) * 4;
	img->pixels[i + 0] = c.red;
	img->pixels[i + 1] = c.green;
	img->pixels[i + 2] = c.blue;
	img->pixels[i + 3] = 255;
}

void	set_color(t_scene *scene, mlx_image_t *img, int x, int y)
{
	t_ray			ray;
	t_intersec_info	hit;
	t_rgb_color		final_color;

	ray = generate_ray(x, y, &scene->camera);
	hit = find_closest_interesection(&ray, scene);
	final_color = apply_light(hit, scene, ray);
	set_pixel(img, x, y, final_color);
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
			set_color(scene, img, x, y);
			x++;
		}
		y++;
	}
}

mlx_t	*open_window(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT_bonus", false);
	if (!mlx)
		return (NULL);
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		return (NULL);
	}
	render(scene, img);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		mlx_terminate(mlx);
		return (NULL);
	}
	return (mlx);
}
