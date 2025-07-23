/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:29 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 14:46:05 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt_bonus.h"

static void	get_pixel(int x, int y, float *px, float *py)
{
	*px = (2.0f * ((float)x + 0.5f) / (float)WINDOW_WIDTH - 1.0f);
	*py = (1.0f - 2.0f * ((float)y + 0.5f) / (float)WINDOW_HEIGHT);
}

static t_vector3d	get_direction_from_pixel(float px, float py, t_camera *cam,
	t_cam_basis basis)
{
	float		ratio;
	float		scale;
	t_vector3d	pixel_direction;
	t_vector3d	temp1;
	t_vector3d	temp2;

	ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	scale = tanf(cam->fov * 0.5f * (M_PI / 180.0f));
	px *= ratio * scale;
	py *= scale;
	temp1 = scalar_multiplication(px, basis.u);
	temp2 = scalar_multiplication(py, basis.v);
	pixel_direction = subtract_vectors(add_vectors(temp1, temp2), basis.w);
	return (normalize(pixel_direction));
}

t_vector3d	get_ray_direction(int x, int y, t_camera *cam, t_cam_basis basis)
{
	float	px;
	float	py;

	get_pixel(x, y, &px, &py);
	return (get_direction_from_pixel(px, py, cam, basis));
}

t_ray	generate_ray(int x, int y, t_camera *cam)
{
	t_ray		ray;
	t_cam_basis	basis;

	basis = camera_basis(cam);
	ray.origin = cam->camera_position;
	ray.direction = get_ray_direction(x, y, cam, basis);
	return (ray);
}
