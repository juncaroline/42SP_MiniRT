#include "../../includes/minirt.h"

bool	intersect_plane(t_ray *ray, t_plane *plane, float *t)
{
	float	denominator;
	float	numerator;
	t_vector3d	diff;

	diff = subtract_vectors(plane->plane_point, ray->origin);
	denominator = dot_product(ray->direction, plane->vector);
	if (fabs(denominator) < 1e-6)
		return (false);
	numerator = dot_product(diff, plane->vector);
	*t = numerator / denominator;
	if (*t < 0.0f)
		return (false);
	return (true);
}
