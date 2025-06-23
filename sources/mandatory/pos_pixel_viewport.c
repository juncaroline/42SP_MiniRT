#include "../../includes/minirt.h"

t_vector3d	calculate_pixel_position(t_camera *cam, t_cam_basis camera_basis,
	float viewport_width, float viewport_height)
{
	t_vector3d	horizontal;
	t_vector3d	vertical;
	t_vector3d	half_horizontal;
	t_vector3d	half_vertical;
	t_vector3d	moved_to_left;
	t_vector3d	moved_left_to_down;
	t_vector3d	bottom_left;
	
	viewport_width = WINDOW_WIDTH;
	viewport_height = WINDOW_HEIGHT;
	horizontal = scalar_multiplication(WINDOW_WIDTH, camera_basis.u);
	vertical = scalar_multiplication(WINDOW_HEIGHT, camera_basis.v);
	half_horizontal = scalar_multiplication(0.5f, horizontal);
	half_vertical = scalar_multiplication(0.5f, vertical);
	moved_to_left = subtract_vectors(cam->camera_position, half_horizontal);
	moved_left_to_down = subtract_vectors(moved_to_left, half_vertical);
	bottom_left = subtract_vectors(moved_left_to_down, camera_basis.w);
	return (bottom_left);
}

t_vector3d	generate_ray(t_ray ray)
{
	t_ray	ray;
	t_vector3d	direction;
	t_vector3d	pixel_position;

	pixel_position = calculate_pixel_position(&ray->origin, ray->direction,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	direction = normalize(subtract_vectors(pixel_position))
}
