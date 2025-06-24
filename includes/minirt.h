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

# define M_PI 3.14159265358979323846

typedef struct s_vector3d
{
	float	x;
	float	y;
	float	z;
}	t_vector3d;

typedef struct s_ray
{
	t_vector3d	origin;
	t_vector3d	direction;
}	t_ray;

typedef struct s_rgb_color
{
	int	red;
	int	green;
	int	blue;
}	t_rgb_color;

typedef struct s_ambient
{
	float		ratio;
	t_rgb_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vector3d	camera_position;
	t_vector3d	camera_direction;
	float		fov;
}	t_camera;

typedef struct s_cam_basis
{
	t_vector3d	u;
	t_vector3d	v;
	t_vector3d	w;
}	t_cam_basis;

typedef struct s_light
{
	t_vector3d	light_point;
	float		ratio;
	t_rgb_color	color;
}	t_light;

typedef struct s_sphere
{
	t_vector3d	sphere_center;
	float		diameter;
	t_rgb_color	color;
}	t_sphere;

typedef struct s_sphere_quad
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
}	t_sphere_quad;

typedef struct s_plane
{
	t_vector3d	plane_point;
	t_vector3d	vector;
	t_rgb_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3d	cylinder_center;
	t_vector3d	vector;
	float		diameter;
	float		height;
	t_rgb_color	color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	int			sphere_count;
	t_plane		*plane;
	int			plane_count;
	t_cylinder	*cylinder;
	int			cylinder_count;
}	t_scene;

// check_elements_convert.c
bool	parse_ambient(char **tokens, int count, t_ambient *ambient);
bool	parse_camera(char **tokens, int count, t_camera *camera);
bool	parse_light(char **tokens, int count, t_light *light);

// check_objects_convert.c
bool	parse_sphere(char **tokens, int count, t_sphere *sphere);
bool	add_sphere(t_scene *scene, t_sphere *new_sphere, int count);
bool	parse_plane(char **tokens, int count, t_plane *plane);
bool	add_plane(t_scene *scene, t_plane *new_plane, int count);
bool	parse_cylinder(char **tokens, int count, t_cylinder *cylinder);
bool	add_cylinder(t_scene *scene, t_cylinder *new_cylinder, int count);

// error.c
void	error_msg(int status);

// init.c
void	esc_command(void* param);
int32_t	init(void);

// intersect_cylinder.c
bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t);


// intersect_plane.c
bool	intersect_plane(t_ray *ray, t_plane *plane, float *t);

// intersect_sphere.c
bool	intersect_sphere(t_ray *ray, t_sphere *sphere, float *t);

// math.c
t_vector3d	add_vectors(t_vector3d a, t_vector3d b);
t_vector3d	cross_product(t_vector3d a, t_vector3d b);
t_vector3d	subtract_vectors(t_vector3d a, t_vector3d b);
t_vector3d	scalar_multiplication(float k, t_vector3d vector);
t_vector3d	negative_vector(t_vector3d vector);

// parse.c
void	check_file_extension(char *extension);
void	read_file(char *scene_file, t_scene *scene);

// ray_direction.c
t_vector3d	get_ray_direction(int x, int y, t_camera *cam, t_cam_basis basis);
t_ray	generate_ray(int x, int y, t_camera *cam);

// ray_generator.c
t_vector3d	normalize(t_vector3d vector);
t_cam_basis	camera_basis(t_camera *cam);

// free.c
void	free_split(char **tokens);
void	free_scene(t_scene *scene);

// utils.c
int		skip_spaces(char *line);
void	replace_with_spaces(char *line);
char	**split_line(char *line);

// utils2.c
bool	ft_isnumber(char *str);
bool	ft_isfloat(const char *str);
float	string_to_float(char *str);

// validate_elements.c
void	verify_elements(char *content, int i);
bool	validate_elements(char **tokens, t_scene *scene);

// validate_param_convert.c
bool	is_rgb_color(t_rgb_color color_value);
t_rgb_color	parse_rgb(char *str);
bool	is_normalized_vector(t_vector3d vector_value);
t_vector3d	parse_normalized_vector(char *str);
t_vector3d	parse_coordinates(char *str);

// validate_param2_convert.c
float	parse_fov(char *str);
float	parse_ratio(char *str);
float	parse_measurements(char *str);

#endif