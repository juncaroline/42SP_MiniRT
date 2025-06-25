#include "../../includes/minirt.h"

static void	init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
	t_cylinder_projection *proj)
{
	proj->oc = subtract_vectors(ray->origin, cylinder->cylinder_center);
	proj->oc_times_v = dot_product(proj->oc, cylinder->vector);
	proj->oc_perpendicular = subtract_vectors(proj->oc,
		scalar_multiplication(proj->oc_times_v, cylinder->vector));
	proj->d_times_v = dot_product(ray->direction, cylinder->vector);
	proj->projected_d = scalar_multiplication(proj->d_times_v,
		cylinder->vector);
	proj->d_perpendicular = subtract_vectors(ray->direction, proj->projected_d);
}

static bool	solve_cylinder_quadratic(t_cylinder_projection *proj,
	t_cylinder *cylinder, t_cylinder_quad *quad)
{
	quad->radius = cylinder->diameter / 2.0f;
	quad->a = dot_product(proj->d_perpendicular, proj->d_perpendicular);
	quad->b = 2.0f * dot_product(proj->d_perpendicular, proj->oc_perpendicular);
	quad->c = dot_product(proj->oc_perpendicular, proj->oc_perpendicular)
		- quad->radius * quad->radius;
	quad->discriminant = quad->b * quad->b - 4.0f * quad->a * quad->c;
	
	if (quad->discriminant < 0.0f)
		return (false);
	quad->sqrt_discriminant = sqrtf(quad->discriminant);
	quad->t0 = (-quad->b - quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->t1 = (-quad->b + quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->t_hit = -1.0f;
	if (quad->t0 > 0.0f && quad->t1 > 0.0f)
		quad->t_hit = fminf(quad->t0, quad->t1);
	else if (quad->t0 > 0.0f)
		quad->t_hit = quad->t0;
	else if (quad->t1 > 0.0f)
		quad->t_hit = quad->t1;
	else
		return (false);
	return (true);
}

static bool	validate_cylinder_intersec(t_ray *ray, t_cylinder *cylinder,
	t_cylinder_quad *quad)
{
	t_cylinder_intersec	intersec;
	
	intersec.intersec_point = add_vectors(ray->origin,
		scalar_multiplication(quad->t_hit, ray->direction));
	intersec.vector_to_point = subtract_vectors(intersec.intersec_point,
		cylinder->cylinder_center);
	intersec.height_projection = dot_product(intersec.vector_to_point,
		cylinder->vector);
	
	if (intersec.height_projection < 0.0f || intersec.height_projection
		> cylinder->height)
		return (false);
	return (true);
}

t_intersection_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	t_intersection_info		info;
	
	info.intersection = false;
	info.dist_to_intesec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	
	init_cylinder_projection(ray, cylinder, &proj);
	if (!solve_cylinder_quadratic(&proj, cylinder, &quad))
		return (info);
	if (!validate_cylinder_intersec(ray, cylinder, &quad))
		return (info);
	
	info.intersection = true;
	info.dist_to_intesec = quad.t_hit;
	info.intersec_point = add_vectors(ray->origin,
		scalar_multiplication(quad.t_hit, ray->direction));
	info.normal = calculate_cylinder_normal(cylinder, info.intersec_point);
	return (info);
}

t_vector3d	calculate_cylinder_normal(t_cylinder *cylinder, t_vector3d point)
{
	t_vector3d	point_to_axis;
	t_vector3d	axis_point;
	t_vector3d	normal;
	
	point_to_axis = subtract_vectors(point, cylinder->cylinder_center);
	axis_point = scalar_multiplication(dot_product(point_to_axis, cylinder->vector), 
		cylinder->vector);
	info.normal = subtract_vectors(point_to_axis, axis_point);
	info.normal = normalize_vector(info.normal);
	return (normal);
}

// bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
// {
// 	t_cylinder_projection	proj;
// 	t_cylinder_quad			quad;
	
// 	init_cylinder_projection(ray, cylinder, &proj);
	
// 	if (!solve_cylinder_quadratic(&proj, cylinder, &quad))
// 		return (false);
	
// 	if (!validate_cylinder_intersec(ray, cylinder, &quad))
// 		return (false);
	
// 	*t = quad.t_hit;
// 	return (true);
// }
