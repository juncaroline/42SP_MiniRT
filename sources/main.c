// #include <math.h>
// #include <stdio.h>
// #include "../includes/minirt.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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
	float		oc_times_v;
	t_vector3d	oc_perpendicular;
	float		d_times_v;
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
	float	t0;
	float	t1;
	float	t_hit;
}	t_cylinder_quad;

typedef struct s_cylinder_intersection
{
	t_vector3d	intersection_point;
	t_vector3d	vector_to_point;
	float		height_projection;
}	t_cylinder_intersection;

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

void	init_cylinder_projection(t_ray *ray, t_cylinder *cylinder, t_cylinder_projection *proj)
{
	proj->oc = subtract_vectors(ray->origin, cylinder->cylinder_center);
	proj->oc_times_v = dot_product(proj->oc, cylinder->vector);
	proj->oc_perpendicular = subtract_vectors(proj->oc, scalar_multiplication(proj->oc_times_v, cylinder->vector));
	proj->d_times_v = dot_product(ray->direction, cylinder->vector);
	proj->projected_d = scalar_multiplication(proj->d_times_v, cylinder->vector);
	proj->d_perpendicular = subtract_vectors(ray->direction, proj->projected_d);
}

bool	solve_cylinder_quadratic(t_cylinder_projection *proj, t_cylinder *cylinder, t_cylinder_quad *quad)
{
	quad->radius = cylinder->diameter / 2.0f;
	quad->a = dot_product(proj->d_perpendicular, proj->d_perpendicular);
	quad->b = 2.0f * dot_product(proj->d_perpendicular, proj->oc_perpendicular);
	quad->c = dot_product(proj->oc_perpendicular, proj->oc_perpendicular) - quad->radius * quad->radius;
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

bool	validate_cylinder_intersection(t_ray *ray, t_cylinder *cylinder, t_cylinder_quad *quad)
{
	t_cylinder_intersection	intersection;
	
	intersection.intersection_point = add_vectors(ray->origin, scalar_multiplication(quad->t_hit, ray->direction));
	intersection.vector_to_point = subtract_vectors(intersection.intersection_point, cylinder->cylinder_center);
	intersection.height_projection = dot_product(intersection.vector_to_point, cylinder->vector);
	
	if (intersection.height_projection < 0.0f || intersection.height_projection > cylinder->height)
		return (false);
	
	return (true);
}

bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	t_cylinder_projection	proj;
	t_cylinder_quad			quad;
	
	init_cylinder_projection(ray, cylinder, &proj);
	
	if (!solve_cylinder_quadratic(&proj, cylinder, &quad))
		return (false);
	
	if (!validate_cylinder_intersection(ray, cylinder, &quad))
		return (false);
	
	*t = quad.t_hit;
	return (true);
}


int	main(void)
{
	t_ray ray;
	t_cylinder cyl;
	float t;

	// ray.origin = (t_vector3d){0.0f, 0.0f, 0.0f};
	// ray.direction = (t_vector3d){0.0f, 0.0f, -1.0f};

	// cyl.cylinder_center = (t_vector3d){0.0f, 0.0f, -5.0f};
	// cyl.vector = (t_vector3d){0.0f, 1.0f, 0.0f}; // eixo do cilindro
	// cyl.diameter = 2.0f;
	// cyl.height = 5.0f;

	// ray.origin = (t_vector3d){1.0f, 0.0f, 0.0f};  // deslocado 1 unidade no X (raio = 1)
	// ray.direction = (t_vector3d){0.0f, 0.0f, -1.0f};  // indo para o fundo (Z-)

	// cyl.cylinder_center = (t_vector3d){0.0f, 0.0f, -5.0f};  // mesmo cilindro de antes
	// cyl.vector = (t_vector3d){0.0f, 1.0f, 0.0f};
	// cyl.diameter = 2.0f;
	// cyl.height = 5.0f;

	// ray.origin = (t_vector3d){2.0f, 0.0f, 0.0f};  // 2 unidades no X
	// ray.direction = (t_vector3d){0.0f, 0.0f, -1.0f};  // mesma direção

	// cyl.cylinder_center = (t_vector3d){0.0f, 0.0f, -5.0f};
	// cyl.vector = (t_vector3d){0.0f, 1.0f, 0.0f};
	// cyl.diameter = 2.0f;
	// cyl.height = 5.0f;

	ray.origin = (t_vector3d){0.0f, -3.0f, 0.0f};  // Y abaixo do cilindro
	ray.direction = (t_vector3d){0.0f, 0.0f, -1.0f};  // indo para Z-

	cyl.cylinder_center = (t_vector3d){0.0f, 0.0f, -5.0f};
	cyl.vector = (t_vector3d){0.0f, 1.0f, 0.0f};
	cyl.diameter = 2.0f;
	cyl.height = 2.0f;  // altura curta: só vai até Y = 2.0

	if (intersect_cylinder(&ray, &cyl, &t))
	{
		printf("Interseção detectada! t = %.2f\n", t);
	}
	else
	{
		printf("Sem interseção com o cilindro.\n");
	}

	return (0);
}
