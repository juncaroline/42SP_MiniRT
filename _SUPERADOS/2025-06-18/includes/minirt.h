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

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	z;
}	t_coordinates;

typedef struct s_normalized_vector
{
	float	x;
	float	y;
	float	z;
}	t_normalized_vector;

typedef struct s_ray
{
	t_coordinates	origin;
	t_coordinates	direction;
}	t_ray;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_coordinates		camera_position;
	t_normalized_vector	camera_direction;
	float				fov;
}	t_camera;

typedef struct s_light
{
	t_coordinates	light_point;
	float			ratio;
	t_color			color;
}	t_light;

typedef struct s_sphere
{
	t_coordinates	sphere_center;
	float			diameter;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	t_coordinates		plane_point;
	t_normalized_vector	vector;
	t_color				color;
}	t_plane;

typedef struct s_cylinder
{
	t_coordinates		cylinder_center;
	t_normalized_vector	vector;
	float				diameter;
	float				height;
	t_color				color;
}	t_cylinder;

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