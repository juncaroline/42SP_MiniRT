#include "../../includes/minirt.h"

bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	t_vector3d	oc;
	float	oc_times_v;
	t_vector3d	oc_perpendicular;
	float	d_times_v;
	t_vector3d	projected_d;
	t_vector3d	d_perpendicular;
	
	oc = subtract_vectors(ray->origin, cylinder->cylinder_center);
	oc_times_v = dot_product(oc, cylinder->vector);
	oc_perpendicular = subtract_vectors(oc, scalar_multiplication(oc_times_v, cylinder->vector));
	d_times_v = dot_product(ray->direction, cylinder->vector);
	projected_d = scalar_multiplication(d_times_v, cylinder->vector);
	d_perpendicular = subtract_vectors(ray->direction, projected_d);

	float	radius;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	t0;
	float	t1;
	float	t_hit;

	radius = cylinder->diameter / 2.0f;
	a = dot_product(d_perpendicular, d_perpendicular);
	b = 2.0f * dot_product(d_perpendicular, oc_perpendicular);
	c = dot_product(oc_perpendicular, oc_perpendicular) - radius * radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (false);
	sqrt_discriminant = sqrtf(discriminant);
	t0 = (-b - sqrt_discriminant) / (2.0f * a);
	t1 = (-b + sqrt_discriminant) / (2.0f * a);
	t_hit = -1.0f;
	if (t0 > 0.0f && t1 > 0.0f)
		t_hit = fminf(t0, t1);
	else if (t0 > 0.0f)
		t_hit = t0;
	else if (t1 > 0.0f)
		t_hit = t1;
	else
		return (false);

	t_vector3d	intersection_point;
	intersection_point = add_vectors(ray->origin, scalar_multiplication(t_hit, ray->direction));
	t_vector3d	vector_to_point;
	vector_to_point = subtract_vectors(intersection_point, cylinder->cylinder_center);
	float	height_projection = dot_product(vector_to_point, cylinder->vector);
	if (height_projection < 0.0f || height_projection > cylinder->height)
		return (false);
	*t = t_hit;
	return (true);
}
