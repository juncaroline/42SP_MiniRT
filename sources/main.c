// #include <math.h>
// #include <stdio.h>
// #include "../includes/minirt.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct s_vector3d
{
	float x;
	float y;
	float z;
} t_vector3d;

typedef struct s_ray
{
	t_vector3d origin;
	t_vector3d direction;
} t_ray;

typedef struct s_rgb_color
{
	int	red;
	int	green;
	int	blue;
}	t_rgb_color;

typedef struct s_plane
{
	t_vector3d	plane_point;
	t_vector3d	vector;
	t_rgb_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3d	cylinder_center;
	t_vector3d	vector;
	float		diameter;
	float		height;
	t_rgb_color	color;
}	t_cylinder;

typedef struct s_cylinder_projection
{
	t_vector3d	oc;
	float		oc_proj_v;
	t_vector3d	oc_perpendicular;
	float		d_proj_v;
	t_vector3d	projected_d;
	t_vector3d	d_perpendicular;
}	t_cylinder_projection;

typedef struct s_cylinder_quad
{
	float	radius;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	nearest;
	float	farther;
	float	t_hit;
}	t_cylinder_quad;

typedef struct s_cylinder_intersec
{
	t_vector3d	intersec_point;
	t_vector3d	vector_to_point;
	float		height_projection;
}	t_cylinder_intersec;

typedef struct s_object
{
	t_object_type	type;
	void			*data;
}	t_object;

typedef struct s_intersec_info
{
	bool		intersection;
	float		dist_to_intersec;
	t_vector3d	intersec_point;
	t_vector3d	normal;
	t_object	*object;
} t_intersec_info;

t_vector3d subtract_vectors(t_vector3d a, t_vector3d b)
{
	t_vector3d result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

float dot_product(t_vector3d a, t_vector3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3d	scalar_multiplication(float k, t_vector3d vector)
{
	t_vector3d	result;

	result.x = k * vector.x;
	result.y = k * vector.y;
	result.z = k * vector.z;
	return (result);
}

t_vector3d	add_vectors(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

void	print_vector(char *label, t_vector3d v)
{
	printf("%s: (%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
}

t_vector3d	normalize(t_vector3d vector)
{
	float		magnitude;
	t_vector3d	result;

	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z);
	if (magnitude == 0.0f)
	{
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
		return (result);
	}
	else
	{
		result.x = vector.x / magnitude;
		result.y = vector.y / magnitude;
		result.z = vector.z / magnitude;
	}
	return (result);
}

t_vector3d	calculate_plane_normal(t_plane *plane, t_vector3d point)
{
	(void)point;
	return (normalize(plane->vector));
}

t_intersec_info	intersect_plane(t_ray *ray, t_plane *plane)
{
	t_intersec_info	info;
	float				denominator;
	float				numerator;
	t_vector3d			diff;

	info.intersection = false;
	info.dist_to_intersec = 0.0f;
	info.intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info.normal = (t_vector3d){0.0f, 0.0f, 0.0f};

	diff = subtract_vectors(plane->plane_point, ray->origin);
	denominator = dot_product(ray->direction, plane->vector);
	if (fabs(denominator) < 1e-6)
		return (info);
	numerator = dot_product(diff, plane->vector);
	info.dist_to_intersec = numerator / denominator;
	if (info.dist_to_intersec < 0.0f)
		return (info);

	info.intersection = true;
	info.intersec_point = add_vectors(ray->origin,
			scalar_multiplication(info.dist_to_intersec, ray->direction));
	info.normal = calculate_plane_normal(plane, info.intersec_point);
	return (info);
}

static void	init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
	t_cylinder_projection *proj)
{
	proj->oc = subtract_vectors(ray->origin, cylinder->cylinder_center);
	proj->oc_proj_v = dot_product(proj->oc, cylinder->vector);
	proj->oc_perpendicular = subtract_vectors(proj->oc,
			scalar_multiplication(proj->oc_proj_v, cylinder->vector));
	proj->d_proj_v = dot_product(ray->direction, cylinder->vector);
	proj->projected_d = scalar_multiplication(proj->d_proj_v,
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

	if (quad->discriminant < 1e-6f)
		return (false);
	if (fabs(quad->a) < 1e-6)
		return (false);
	quad->sqrt_discriminant = sqrtf(quad->discriminant);
	quad->nearest = (-quad->b - quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->farther = (-quad->b + quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->t_hit = -1.0f;
	if (quad->nearest > 1e-6)
		quad->t_hit = quad->nearest;
	else if (quad->farther > 1e-6)
		quad->t_hit = quad->farther;
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

static bool	intersect_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
	bool top_cap, t_intersec_info *info)
{
	t_vector3d			center;
	t_vector3d			normal;
	t_plane				plane;
	t_intersec_info	cap_info;
	float				radius;
	t_vector3d			delta;
	float				distance_squared;

	normal = cylinder->vector;
	if (top_cap == false)
	{
		center = cylinder->cylinder_center;
		normal = scalar_multiplication(-1.0f, normal);
	}
	else
		center = add_vectors(cylinder->cylinder_center,
				scalar_multiplication(cylinder->height, cylinder->vector));
	plane.plane_point = center;
	plane.vector = normal;
	cap_info = intersect_plane(ray, &plane);
	if (cap_info.intersection == false || cap_info.dist_to_intersec <= 1e-6)
		return (false);
	delta = subtract_vectors(cap_info.intersec_point, center);
	radius = cylinder->diameter / 2.0f;
	distance_squared = dot_product(delta, delta);
	if (distance_squared > radius * radius + 1e-6)
		return (false);
	*info = cap_info;
	return (true);
}

t_vector3d	calculate_cylinder_normal(t_cylinder *cylinder, t_vector3d point)
{
	t_vector3d	point_to_axis;
	t_vector3d	axis_point;
	t_vector3d	normal;
	t_vector3d	projection;

	point_to_axis = subtract_vectors(point, cylinder->cylinder_center);
	axis_point = scalar_multiplication(dot_product(point_to_axis,
			cylinder->vector), cylinder->vector);
	normal = subtract_vectors(point_to_axis, axis_point);
	float length_squared = dot_product(normal, normal);
	printf("normal antes do fallback: ");
	print_vector("", normal);
	printf("length_squared: %f\n", length_squared);
	if (length_squared < 1e-12)
	{
		if (fabs(cylinder->vector.x) < 0.9)
			normal = (t_vector3d){1.0f, 0.0f, 0.0f};
		else
			normal = (t_vector3d){0.0f, 1.0f, 0.0f};
		projection = scalar_multiplication(dot_product(normal,
			cylinder->vector), cylinder->vector);
		normal = subtract_vectors(normal, projection);
	}
	normal = normalize(normal);
	return (normal);
}

t_intersec_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	t_intersec_info		info;
	t_intersec_info		cap_inf;
	t_intersec_info		cap_sup;
	bool					hit_lateral;
	bool					hit_cap_inf;
	bool					hit_cap_sup;
	float					best_dist;
	t_intersec_info		best_info;

	info.intersection = false;
	best_info.intersection = false;
	init_cylinder_projection(ray, cylinder, &proj);
	hit_lateral = solve_cylinder_quadratic(&proj, cylinder, &quad);

	if (hit_lateral && validate_cylinder_intersec(ray, cylinder, &quad))
	{
		info.intersection = true;
		info.dist_to_intersec = quad.t_hit;
		info.intersec_point = add_vectors(ray->origin,
				scalar_multiplication(quad.t_hit, ray->direction));
		info.normal = calculate_cylinder_normal(cylinder, info.intersec_point);
	}
	hit_cap_inf = intersect_cylinder_cap(ray, cylinder, false, &cap_inf);
	hit_cap_sup = intersect_cylinder_cap(ray, cylinder, true, &cap_sup);
	best_dist = INFINITY;
	if (info.intersection && info.dist_to_intersec < best_dist)
	{
		best_dist = info.dist_to_intersec;
		best_info = info;
	}
	if (hit_cap_inf && cap_inf.dist_to_intersec < best_dist)
	{
		best_dist = cap_inf.dist_to_intersec;
		best_info = cap_inf;
	}
	if (hit_cap_sup && cap_sup.dist_to_intersec < best_dist)
	{
		best_dist = cap_sup.dist_to_intersec;
		best_info = cap_sup;
	}
	return (best_info);
}

void	test_intersect_cylinder()
{
	t_ray ray;
	t_cylinder cylinder;
	t_intersec_info result;

	// Raio vindo da frente, apontando para o centro do cilindro
	ray.origin = (t_vector3d){0, 1, -5};
	ray.direction = (t_vector3d){0, 0, 1}; // Normalizado

	// Cilindro no centro do mundo, eixo apontando para cima
	cylinder.cylinder_center = (t_vector3d){0, 0, 0};
	cylinder.vector = (t_vector3d){0, 1, 0};
	cylinder.diameter = 2.0f;
	cylinder.height = 4.0f;

	// Interseção
	result = intersect_cylinder(&ray, &cylinder);

	printf("\n--- Teste: Raio Atravessa o Cilindro ---\n");
	printf("Intersecao: %s\n", result.intersection ? "SIM" : "NAO");
	if (result.intersection)
	{
		printf("Distancia: %.2f\n", result.dist_to_intersec);
		print_vector("Ponto de intersecao", result.intersec_point);
		print_vector("Normal", result.normal);
	}
}

int	main(void)
{
	test_intersect_cylinder();
	return (0);
}
