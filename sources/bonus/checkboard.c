#include "../../includes/minirt_bonus.h"

t_rgb_color	checkerboard_plane_pattern(t_vector3d point, float scale, t_object *color)
{
	int	x;
	int	y;

	x = (floor)(point.x * scale);
	y = (floor)(point.z * scale);

	if ((x + y) % 2 == 0)
		return (color->white);
	else
		return (color->black);
}

t_rgb_color	checkerboard_sphere_pattern(t_vector3d point, t_sphere *sphere,
	float scale, t_object *color)
{
	t_vector3d	local;
	float		longitude;
	float		latitude;
	int			i_longitude;
	int			i_latitude;

	local = normalize(subtract_vectors(point, sphere->center));
	longitude = 0.5f + atan2(local.z, local.x) / (2 * M_PI);
	latitude = 0.5f - asin(local.y) / M_PI;
	i_longitude = floor(u * scale);
	i_latitude = floor(v * scale);;

	if ((i_longitude + i_latitude) % 2 == 0)
		return (color->white);
	else
		return (color->black);
}

t_rgb_color	checkerboard_cylinder_pattern(t_vector3d point, t_cylinder *cylinder,
	float scale, t_object *color)
{
	t_vector3d	center_to_intersection;
	float		height;
	t_vector3d	radial;
	float		longitude;
	float		latitude;
	int			i_longitude;
	int			i_latitude;

	center_to_intersection = subtract_vectors(point, cylinder->cylinder_center);
	height = dot_product(center_to_intersection, cylinder->vector);
	radial = subtract_vectors(center_to_intersection,
		scalar_multiplication(height, cylinder->vector));
	radial = normalize(radial);
	longitude = 0.5f + atan2(radial.z, radial.x) / (2 * M_PI);
	latitude = height / cylinder->height;
	i_longitude = floor(u * scale);
	i_latitude = floor(v * scale);;

	if ((i_longitude + i_latitude) % 2 == 0)
		return (color->white);
	else
		return (color->black);
}

t_rgb_color	checkerboard_cone_pattern(t_vector3d point, t_cone *cone,
	float scale, t_object *color)
{
	t_vector3d	center_to_intersection;
	float		height;
	t_vector3d	radial;
	float		longitude;
	float		latitude;
	int			i_longitude;
	int			i_latitude;

	center_to_intersection = subtract_vectors(point, cone->cone_center);
	height = dot_product(center_to_intersection, cone->vector);
	radial = subtract_vectors(center_to_intersection,
		scalar_multiplication(height, cone->vector));
	radial = normalize(radial);
	longitude = 0.5f + atan2(radial.z, radial.x) / (2 * M_PI);
	latitude = height / cone->height;
	i_longitude = floor(u * scale);
	i_latitude = floor(v * scale);;

	if ((i_longitude + i_latitude) % 2 == 0)
		return (color->white);
	else
		return (color->black);
}
