#include "../../includes/minirt.h"

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->sphere)
		free(scene->sphere);
	if (scene->plane)
		free(scene->plane);
	if (scene->cylinder)
		free(scene->cylinder);
}
