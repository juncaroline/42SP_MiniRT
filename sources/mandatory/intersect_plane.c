#include "../../includes/minirt.h"

t_intersection_info	intersect_plane(t_ray *ray, t_plane *plane)
{
	t_intersection_info	info;
	float	denominator;
	float	numerator;
	t_vector3d	diff;

	info.intersection = false;
	info.dist_to_intesec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};

	diff = subtract_vectors(plane->plane_point, ray->origin);
	denominator = dot_product(ray->direction, plane->vector);
	if (fabs(denominator) < 1e-6)
		return (info);
	numerator = dot_product(diff, plane->vector);
	info.dist_to_intesec = numerator / denominator;
	if (info.dist_to_intesec < 0.0f)
		return (info);

	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
		scalar_multiplication(info.dist_to_intesec, ray->direction));
	info.normal = calculate_plane_normal(plane, info.intersec_point);
	return (info);
}

t_vector3d	calculate_plane_normal(t_plane *plane, t_vector3d point)
{
	(void)point;
	return (normalize_vector(plane->vector));
}

// bool	intersect_plane(t_ray *ray, t_plane *plane, float *t)
// {
// 	float	denominator;
// 	float	numerator;
// 	t_vector3d	diff;

// 	diff = subtract_vectors(plane->plane_point, ray->origin);
// 	denominator = dot_product(ray->direction, plane->vector);
// 	if (fabs(denominator) < 1e-6)
// 		return (false);
// 	numerator = dot_product(diff, plane->vector);
// 	*t = numerator / denominator;
// 	if (*t < 0.0f)
// 		return (false);
// 	return (true);
// }
