#ifndef MINIRT_H
# define MINIRT_H

# include "../library/libft/libft.h"
# include "../library/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
}	t_sphere;

// check_elements.c
bool	validate_ambient(char **tokens, int count);
bool	validate_camera(char **tokens, int count);
bool	validate_light(char **tokens, int count);

// check_objects.c
bool	validate_sphere(char **tokens, int count);
bool	validate_plane(char **tokens, int count);
bool	validate_cylinder(char **tokens, int count);

// error.c
void	error_msg(int status);

// init.c
void	esc_command(void* param);
int32_t	init(void);

// parse.c
void	check_file_extension(char *extension);
void	read_file(char *scene);

// free.c
void	free_split(char **tokens);

// utils.c
int		skip_spaces(char *line);
void	replace_with_spaces(char *line);
char	**split_line(char *line);

// utils2.c
bool	ft_isnumber(char *str);
bool	ft_isfloat(const char *str);
float	string_to_float(char *str);

// validate_param.c
bool	validate_rgb(char *str);
bool	validate_normalize_vector(char *str);
bool	validate_coordinates(char *str);

// validate_param2.c
bool	validate_fov(char *str);
bool	validate_ratio(char *str);
bool	validate_measurements(char *str);

// validate_elements.c
void	verify_elements(char *content, int i);
bool	validate_elements(char **tokens);

#endif