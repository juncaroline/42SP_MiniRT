#include "../../includes/minirt.h"

void	free_split(char **tokens)
{
	int	i = 0;
	if (!tokens)
		return;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
