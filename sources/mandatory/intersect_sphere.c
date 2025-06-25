#include "../../includes/minirt.h"

static t_sphere_quad	intersect_sphere_quad(t_ray *ray, t_sphere *sphere)
{
	t_vector3d		L;
	t_sphere_quad	quad;

	L = subtract_vectors(ray->origin, sphere->sphere_center);
	quad.a = dot_product(ray->direction, ray->direction);
	quad.b = 2.0f * dot_product(ray->direction, L);
	quad.c = dot_product(L, L)
		- (sphere->diameter * sphere->diameter) / 4.0f;
	quad.discriminant = quad.b * quad.b - 4.0f * quad.a * quad.c;
	return (quad);
}

static bool	intersect_sphere_solution(t_sphere_quad quad, float *t)
{
	float	t0;
	float	t1;

	if (quad.discriminant < 0.0f)
		return (false);
	t0 = (-quad.b - sqrtf(quad.discriminant)) / (2.0f * quad.a);
	t1 = (-quad.b + sqrtf(quad.discriminant)) / (2.0f * quad.a);
	if (t0 < 0.0f && t1 < 0.0f)
		return (false);
	else if (t0 < 0.0f)
		*t = t1;
	else if (t1 < 0.0f)
		*t = t0;
	else
	{
		if (t0 < t1)
			*t = t0;
		else
			*t = t1;
	}
	return (true);
}

t_intersection_info	intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_sphere_quad	quad;
	t_intersection_info	info;

	info.intersection = false;
	info.dist_to_intesec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};

	quad = intersect_sphere_quad(ray, sphere);
	if (!intersect_sphere_solution(quad, &info.dist_to_intesec))
		return (info);

	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
		scalar_multiplication(info.dist_to_intesec, ray->direction));
	info.normal = calculate_sphere_normal(sphere, info.intersec_point);
	return (info);
}

t_vector3d	calculate_sphere_normal(t_sphere *sphere,
	t_vector3d point)
{
	t_vector3d	normal;
	float		radius;

	radius = sphere->diameter / 2.0f;
	normal = subtract_vectors(point, sphere->sphere_center);
	normal = scalar_multiplication(1.0f / radius, normal);
	return (normal);
}

// bool	intersect_sphere(t_ray *ray, t_sphere *sphere, float *t)
// {
// 	t_sphere_quad	quad;

// 	quad = intersect_sphere_quad(ray, sphere);
// 	return (intersect_sphere_solution(quad, t));
// }
