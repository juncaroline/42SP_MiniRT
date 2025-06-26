#include "../../includes/minirt.h"


t_vector3d	add_vectors(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
t_vector3d	cross_product(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector3d	subtract_vectors(t_vector3d a, t_vector3d b)
{
	t_vector3d	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3d	scalar_multiplication(float k, t_vector3d vector)
{
	t_vector3d	result;

	result.x = k * vector.x;
	result.y = k * vector.y;
	result.z = k * vector.z;
	return (result);
}

float	dot_product(t_vector3d a, t_vector3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3d	negative_vector(t_vector3d vector)
{
	t_vector3d	result;

	result.x = -vector.x;
	result.y = -vector.y;
	result.z = -vector.z;
	return (result);
}
