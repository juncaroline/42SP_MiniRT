#include "../../includes/minirt.h"

bool	parse_sphere(char **tokens, int count, t_sphere *sphere)
{
	t_coordinates	center;
	float			diameter;
	t_rgb_color		color;

	if (count != 4)
	{
		printf("Erro: 'sp' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	center = parse_coordinates(tokens[1]);
	diameter = parse_measurements(tokens[2]);
	color = parse_rgb(tokens[3]);
	if (diameter <= 0 || !is_rgb_color(color))
		return (false);
	sphere->sphere_center = center;
	sphere->diameter = diameter;
	sphere->color = color;
	return (true);
}

bool	add_sphere(t_scene *scene, t_sphere *new_sphere, int count)
{
	t_sphere	*new_array;
	int			i;

	new_array = malloc(sizeof(t_sphere) * (scene->sphere_count + count));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->sphere_count)
	{
		new_array[i] = scene->sphere[i];
		i++;
	}
	i = 0;
	while (i < count)
	{
		new_array[scene->sphere_count + i] = new_sphere[i];
		i++;
	}
	free(scene->sphere);
	scene->sphere = new_array;
	scene->sphere_count += count;
	return (true);
}

bool	parse_plane(char **tokens, int count, t_plane *plane)
{
	t_coordinates	plane_point;
	t_normalized_vector	plane_normal;
	t_rgb_color		color;

	if (count != 4)
	{
		printf("Erro: 'pl' espera 3 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	plane_point = parse_coordinates(tokens[1]);
	plane_normal = parse_normalized_vector(tokens[2]);
	color = parse_rgb(tokens[3]);
	if (!is_normalized_vector(plane_normal) || !is_rgb_color(color))
		return (false);
	plane->plane_point = plane_point;
	plane->vector = plane_normal;
	plane->color = color;
	return (true);
}

bool	add_plane(t_scene *scene, t_plane *new_plane, int count)
{
	t_plane	*new_array;
	int			i;

	new_array = malloc(sizeof(t_plane) * (scene->plane_count + count));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->plane_count)
	{
		new_array[i] = scene->plane[i];
		i++;
	}
	i = 0;
	while (i < count)
	{
		new_array[scene->plane_count + i] = new_plane[i];
		i++;
	}
	free(scene->plane);
	scene->plane = new_array;
	scene->plane_count += count;
	return (true);
}

bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder)
{
	t_coordinates		cylinder_center;
	t_normalized_vector	cylinder_normal;
	float				diameter;
	float				height;
	t_rgb_color			color;

	if (count != 6)
	{
		printf("Erro: 'cy' espera 5 parâmetros, recebeu %d\n", count - 1);
		return (false);
	}
	cylinder_center = parse_coordinates(tokens[1]);
	cylinder_normal = parse_normalized_vector(tokens[2]);
	diameter = parse_measurements(tokens[3]);
	height = parse_measurements(tokens[4]);
	color = parse_rgb(tokens[5]);
	if (!is_normalized_vector(cylinder_normal) || diameter <= 0.0
		|| height <= 0.0 || !is_rgb_color(color))
		return (false);
	cylinder->cylinder_center = cylinder_center;
	cylinder->vector = cylinder_normal;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;
	return (true);
}

bool	add_cylinder(t_scene *scene, t_cylinder *new_cylinder, int count)
{
	t_cylinder	*new_array;
	int			i;

	new_array = malloc(sizeof(t_cylinder) * (scene->cylinder_count + count));
	if (!new_array)
		return (false);
	i = 0;
	while (i < scene->cylinder_count)
	{
		new_array[i] = scene->cylinder[i];
		i++;
	}
	i = 0;
	while (i < count)
	{
		new_array[scene->cylinder_count + i] = new_cylinder[i];
		i++;
	}
	free(scene->cylinder);
	scene->cylinder = new_array;
	scene->cylinder_count += count;
	return (true);
}
