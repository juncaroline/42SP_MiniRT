#include "../../includes/minirt.h"

bool	validate_ambient(char **tokens, int count)
{
	if (count != 3)
	{
		printf("Erro: 'A' espera 2 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	if (validate_ratio(tokens[1]))
	{
		printf("Erro: 'A' espera um valor entre 0.0 e 1.0, recebeu '%s'\n",
			tokens[1]);
		return (false);
	}
	if (validate_rgb(tokens[2]) == false)
	{
		printf("Erro: 'A' espera um valor RGB válido, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	return (true);
}

bool	validate_camera(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Erro: 'C' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	if (validate_coordinates(tokens[1]) == false)
	{
		printf("Erro: 'C' espera coordenadas válidas, recebeu '%s'\n",
			tokens[1]);
		return (false);
	}
	if (validate_normalize_vector(tokens[2]) == false)
	{
		printf("Erro: 'C' espera um vetor normalizado, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	if (validate_fov(tokens[3]) == false)
	{
		printf("Erro: 'C' espera um FOV válido, recebeu '%s'\n",
			tokens[3]);
		return (false);
	}
	return (true);
}

bool	validate_light(char **tokens, int count)
{
	if (count != 4 && count != 5)
	{
		printf("Erro: 'L' espera 3 ou 4 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	if (validate_coordinates(tokens[1]) == false)
	{
		printf("Erro: 'L' espera coordenadas válidas, recebeu '%s'\n",
			tokens[1]);
		return (false);
	}
	if (validate_ratio(tokens[2]) == false)
	{
		printf("Erro: 'L' espera um valor entre 0.0 e 1.0, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	if (count == 5 && validate_rgb(tokens[3]))
	{
		printf("Erro: 'L' espera um valor RGB válido, recebeu '%s'\n",
			tokens[3]);
		return (false);
	}
	return (true);
}
