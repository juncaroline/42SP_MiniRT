/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 12:45:43 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

void	check_file_extension(char *extension)
{
	int	len;

	len = ft_strlen(extension);
	if (len < 3 || extension[len - 3] != '.' || extension[len - 2] != 'r'
		|| extension[len - 1] != 't')
		printf("Invalid file extension.\n");
}

int	verif_content(char *content, t_scene *scene, char ***tokens, int i)
{
	if (content[i] == '\n')
		return (2);
	*tokens = split_line(content);
	if (!*tokens || !*tokens[0])
	{
		printf("Error splitting line into tokens\n");
		return (1);
	}
	if (ft_strcmp((*tokens)[0], "#") == 0)
	{
		free_split(*tokens);
		return (2);
	}
	if (!validate_line(*tokens, scene))
	{
		free_split(*tokens);
		return (1);
	}
	return (0);
}

bool	process_single_line(char *content, t_scene *scene, char **tokens)
{
	int	i;
	int	result;

	i = skip_spaces(content);
	result = verif_content(content, scene, &tokens, i);
	if (result)
	{
		if (result == 1)
			return (false);
		return (true);
	}
	free_split(tokens);
	return (true);
}

bool	process_file_content(int fd, t_scene *scene)
{
	char	*content;
	char	**tokens;

	tokens = NULL;
	content = get_next_line(fd);
	if (content == NULL)
		return (parse_error("Empty file!"));
	while (content)
	{
		if (!process_single_line(content, scene, tokens))
		{
			get_next_line(-1);
			return (false);
		}
		free(content);
		content = get_next_line(fd);
	}
	get_next_line(-1);
	return (true);
}

bool	read_file(char *scene_file, t_scene *scene)
{
	int		fd;
	bool	success;

	check_file_extension(scene_file);
	fd = open(scene_file, O_RDONLY);
	if (fd < 0)
		printf("Error opening file.\n");
	success = process_file_content(fd, scene);
	get_next_line(-1);
	close(fd);
	return (success);
}
