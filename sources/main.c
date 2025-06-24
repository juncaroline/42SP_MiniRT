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

typedef struct s_plane
{
	t_vector3d plane_point;
	t_vector3d vector; // normal ao plano
} t_plane;

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

bool intersect_plane(t_ray *ray, t_plane *plane, float *t)
{
	float		denom;
	t_vector3d	diff;
	float		numer;

	denom = dot_product(ray->direction, plane->vector);
	if (fabs(denom) < 1e-6)
		return (false);
	diff = subtract_vectors(plane->plane_point, ray->origin);
	numer = dot_product(diff, plane->vector);
	*t = numer / denom;
	if (*t < 0.0f)
		return (false);
	return (true);
}

int main(void)
{
	// t_plane plane = {
	// 	.plane_point = {0.0f, 0.0f, -5.0f},     // plano em z = -5
	// 	.vector = {0.0f, 0.0f, 1.0f}            // normal apontando para +z
	// };

	// t_ray ray = {
	// 	.origin = {0.0f, 0.0f, 0.0f},           // origem da câmera
	// 	.direction = {0.0f, 0.0f, -1.0f}        // olhando para -z
	// };

	// t_plane plane = {
	// .plane_point = {0.0f, 0.0f, 5.0f},      // plano atrás da câmera
	// .vector = {0.0f, 0.0f, 1.0f}            // normal ainda aponta pra +z
	// };

	// t_ray ray = {
	// 	.origin = {0.0f, 0.0f, 0.0f},
	// 	.direction = {0.0f, 0.0f, -1.0f}
	// };

	// t_plane plane = {
	// .plane_point = {0.0f, 0.0f, -5.0f},
	// .vector = {0.0f, 0.0f, 1.0f}
	// };

	// t_ray ray = {
	// 	.origin = {0.0f, 0.0f, 0.0f},
	// 	.direction = {1.0f, 0.0f, 0.0f}     // raio andando no eixo X
	// };

	t_plane plane = {
	.plane_point = {0.0f, 0.0f, -5.0f},
	.vector = {0.0f, 0.707f, 0.707f}     // normal inclinada (normalizei para teste)
	};

	t_ray ray = {
		.origin = {0.0f, 0.0f, 0.0f},
		.direction = {0.0f, 0.0f, -1.0f}
	};

	float t;

	if (intersect_plane(&ray, &plane, &t))
		printf("Interseção com plano! t = %.2f\n", t);
	else
		printf("Nenhuma interseção com plano.\n");

	return 0;
}
