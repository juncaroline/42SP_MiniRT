/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/06 19:16:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_file_extension(char *extension)
{
	int	len;

	len = ft_strlen(extension);
	if (len < 3 || extension[len - 3] != '.' || extension[len - 2] != 'r'
		|| extension[len - 1] != 't')
		error_msg(1);
}

void	verify_elements(char *content, int i)
{
	if (ft_strncmp(content + i, "A", 1) == 0)
		printf("Detected ambient light\n");
	else if (ft_strncmp(content + i, "C", 1) == 0)
		printf("Detected camera\n");
	else if (ft_strncmp(content + i, "L", 1) == 0)
		printf("Detected light source\n");
	else if (ft_strncmp(content + i, "sp", 2) == 0)
		printf("Detected sphere\n");
	else if (ft_strncmp(content + i, "pl", 2) == 0)
		printf("Detected plane\n");
	else if (ft_strncmp(content + i, "cy", 2) == 0)
		printf("Detected cylinder\n");
	else
		printf("Unknown element: %s\n", content);
}

void	get_content(char	**content, int fd)
{
	free(*content);
	*content = get_next_line(fd);
}

int	verif_content(char *content, t_scene *scene, char ***tokens, int i)
{
	if (content[i] == '\n')
		return (1);
	*tokens = split_line(content);
	if (!*tokens || !*tokens[0])
	{
		printf("Error splitting line into tokens\n");
		return (1);
	}
	if (!validate_elements(*tokens, scene))
	{
		free_split(*tokens);
		return (1);
	}
	return (0);
}

void	read_file(char *scene_file, t_scene *scene)
{
	int		fd;
	char	*content;
	int		i;
	char	**tokens;

	check_file_extension(scene_file);
	fd = open(scene_file, O_RDONLY);
	if (fd < 0)
		error_msg(2);
	content = get_next_line(fd);
	if (content == NULL)
		error_msg(3);
	while (content)
	{
		i = skip_spaces(content);
		if (verif_content(content, scene, &tokens, i))
		{
			get_content(&content, fd);
			continue ;
		}
		verify_elements(content, i);
		free_split(tokens);
		get_content(&content, fd);
	}
	close(fd);
}

// void	read_file(char *scene_file, t_scene *scene)
// {
// 	int		fd;
// 	char	*content;
// 	int		i;
// 	char	**tokens;

// 	check_file_extension(scene_file);
// 	fd = open(scene_file, O_RDONLY);
// 	if (fd < 0)
// 		error_msg(2);
// 	content = get_next_line(fd);
// 	if (content == NULL)
// 		error_msg(3);
// 	while (content)
// 	{
// 		i = skip_spaces(content);
// 		if (content[i] == '\n')
// 		{
// 			free(content);
// 			content = get_next_line(fd);
// 			continue ;
// 		}
// 		tokens = split_line(content);
// 		if (!tokens || !tokens[0])
// 		{
// 			printf("Erro ao dividir linha em tokens\n");
// 			free(content);
// 			content = get_next_line(fd);
// 			continue ;
// 		}
// 		if (!validate_elements(tokens, scene))
// 		{
// 			free_split(tokens);
// 			free(content);
// 			content = get_next_line(fd);
// 			continue ;
// 		}
// 		verify_elements(content, i);
// 		free_split(tokens);
// 		free(content);
// 		content = get_next_line(fd);
// 	}
// 	close(fd);
// }
