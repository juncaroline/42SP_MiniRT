// #include <math.h>
// #include <stdio.h>
#include "../includes/minirt.h"

t_normalized_vector normalize(t_coordinates vector)
{
	float				magnitude;
	t_normalized_vector	result;

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

void	test_normalize(void)
{
	t_coordinates input;
	t_normalized_vector result;

	input.x = 3.0f;
	input.y = 0.0f;
	input.z = 4.0f;

	result = normalize(input);

	printf("Vetor original: (%.2f, %.2f, %.2f)\n", input.x, input.y, input.z);
	printf("Vetor normalizado: (%.4f, %.4f, %.4f)\n", result.x, result.y, result.z);
}

int main(void)
{
	test_normalize();
	return (0);
}
