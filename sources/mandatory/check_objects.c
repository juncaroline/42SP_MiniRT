#include "../../includes/minirt.h"

bool	validate_sphere(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Erro: 'sp' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	if (validate_coordinates(tokens[1]) == false)
	{
		printf("Erro: 'sp' espera coordenadas válidas, recebeu '%s'\n",
			tokens[1]);
		return (false);
	}
	if (validate_measurements(tokens[2]) == false)
	{
		printf("Erro: 'sp' espera uma medida de diâmetro válida, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	if (validate_rgb(tokens[3]) == false)
	{
		printf("Erro: 'sp' espera um valor RGB válido, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	return (true);
}

bool	validate_plane(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Erro: 'pl' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	if (validate_coordinates(tokens[1]) == false)
	{
		printf("Erro: 'pl' espera coordenadas válidas, recebeu '%s'\n",
			tokens[1]);
		return (false);
	}
	if (validate_normalize_vector(tokens[2]) == false)
	{
		printf("Erro: 'pl' espera um vetor normalizado, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	if (validate_rgb(tokens[3]) == false)
	{
		printf("Erro: 'pl' espera um valor RGB válido, recebeu '%s'\n",
			tokens[3]);
		return (false);
	}
	return (true);
}

bool	validate_cylinder(char **tokens, int count)
{
	if (count != 6)
	{
		printf("Erro: 'cy' espera 5 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	if (validate_coordinates(tokens[1]) == false)
	{
		printf("Erro: 'cy' espera coordenadas válidas, recebeu '%s'\n",
			tokens[1]);
		return (false);
	}
	if (validate_normalize_vector(tokens[2]) == false)
	{
		printf("Erro: 'cy' espera um vetor normalizado, recebeu '%s'\n",
			tokens[2]);
		return (false);
	}
	if (validate_measurements(tokens[3]) == false
		|| validate_measurements(tokens[4]) == false)
	{
		printf("Erro: 'cy' espera uma medida de diâmetro e altura válidas, "
			"recebeu '%s' e '%s'\n", tokens[3], tokens[4]);
		return (false);
	}
	if (validate_rgb(tokens[5]) == false)
	{
		printf("Erro: 'cy' espera um valor RGB válido, recebeu '%s'\n",
			tokens[5]);
		return (false);
	}
	return (true);
}
