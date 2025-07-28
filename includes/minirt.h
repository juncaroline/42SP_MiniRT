/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:06:46 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/28 15:52:47 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// # define WINDOW_WIDTH 1600
// # define WINDOW_HEIGHT 900
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 450

# define M_PI 3.14159265358979323846

# define EPSILON 1e-3

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

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
}	t_light;

typedef struct s_quadratic
{
	float	radius;
	float	cos_squared;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	nearest;
	float	farther;
	float	t_hit;
}	t_quadratic;

typedef struct s_point_light
{
	t_vector3d	position;
	t_rgb_color	intensity;
}	t_point_light;

typedef struct s_sphere
{
	t_vector3d	sphere_center;
	float		diameter;
	t_rgb_color	color;
}	t_sphere;

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

typedef struct s_cylinder_projection
{
	t_vector3d	oc;
	float		oc_proj_v;
	t_vector3d	oc_perpendicular;
	float		d_proj_v;
	t_vector3d	projected_d;
	t_vector3d	d_perpendicular;
}	t_cylinder_projection;

typedef struct s_cylinder_intersec
{
	t_vector3d	intersec_point;
	t_vector3d	vector_to_point;
	float		height_projection;
}	t_cylinder_intersec;

typedef struct s_object
{
	t_object_type	type;
	void			*data;
}	t_object;

typedef struct s_intersection_info
{
	bool		intersection;
	float		dist_to_intersec;
	t_vector3d	intersec_point;
	t_vector3d	normal;
	t_vector3d	over_point;
	t_rgb_color	color;
	t_object	*object;
}	t_intersec_info;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	bool		has_ambient;
	bool		has_camera;
	bool		has_light;
	t_object	*objects;
	int			object_count;
	t_sphere	*sphere;
	int			sphere_count;
	t_plane		*plane;
	int			plane_count;
	t_cylinder	*cylinder;
	int			cylinder_count;
}	t_scene;

/* -------------------- init --------------------- */

// handle_param.c
bool				handle_sphere(char **tokens, t_scene *scene);
bool				handle_plane(char **tokens, t_scene *scene);
bool				handle_cylinder(char **tokens, t_scene *scene);

// init.c
void				esc_command(void *param);
void				set_pixel(mlx_image_t *img, int x, int y, t_rgb_color c);
void				set_color(t_scene *scene, mlx_image_t *img, int x, int y);
void				render(t_scene *scene, mlx_image_t *img);
int32_t				init_scene(t_scene *scene);

// validate_elements.c
int					count_tokens(char **tokens);
bool				validate_scene_objects(char **tokens, t_scene *scene);
bool				count_scene_elements(char **tokens, int count,
						t_scene *scene);
bool				validate_line(char **tokens, t_scene *scene);

/* -------------------- intersection --------------------- */

// closest_hit.c
t_intersec_info		intersect_object(t_ray *ray, t_object *object);
t_intersec_info		find_closest_object(t_ray *ray, t_object *objects,
						int count);
t_intersec_info		find_closest_interesection(t_ray *ray, t_scene *scene);

// intersect_cylinder_aux.c
t_plane				create_cylinder_cap_plane(t_cylinder *cylinder,
						bool is_top_cap);
bool				is_intersection_within_cap_radius(
						t_vector3d intersection_point, t_vector3d cap_center,
						float cylinder_diameter);
bool				ray_intersects_cylinder_cap(t_ray *ray,
						t_cylinder *cylinder, bool is_top_cap,
						t_intersec_info *info);
t_intersec_info		ray_intersects_cylinder_surface(t_ray *ray,
						t_cylinder *cylinder);

// intersect_cylinder_calc.c
void				init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
						t_cylinder_projection *proj);
bool				solve_cylinder_quadratic(t_cylinder_projection *proj,
						t_cylinder *cylinder, t_quadratic *quad);
bool				validate_cylinder_intersec(t_ray *ray, t_cylinder *cylinder,
						t_quadratic *quad);
t_vector3d			calculate_cylinder_normal(t_cylinder *cylinder,
						t_vector3d point);

// intersect_cylinder.c
void				compute_cylinder_cap_intersections(t_ray *ray,
						t_cylinder *cylinder, t_intersec_info *bottom_cap,
						t_intersec_info *top_cap);
t_intersec_info		select_closest_intersection(t_intersec_info surface,
						t_intersec_info bottom_cap, t_intersec_info top_cap,
						t_rgb_color color);
t_intersec_info		intersect_cylinder(t_ray *ray, t_cylinder *cylinder);

// intersect_plane.c
t_vector3d			calculate_plane_normal(t_plane *plane, t_vector3d point);
t_intersec_info		intersect_plane(t_ray *ray, t_plane *plane);

// intersect_quadratic.c
bool				solve_quadratic_equation(t_quadratic *quad);

// intersect_sphere.c
t_vector3d			calculate_sphere_normal(t_sphere *sphere,
						t_vector3d intersec_point);
t_intersec_info		intersect_sphere(t_ray *ray, t_sphere *sphere);

/* -------------------- light --------------------- */

// light.c
t_rgb_color			apply_light(t_intersec_info hit, t_scene *scene, t_ray ray);

// light_color.c
t_rgb_color			scale_color(t_rgb_color c, float ratio);
t_rgb_color			add_color(t_rgb_color a, t_rgb_color b);

/* -------------------- parse --------------------- */

// parse_elements.c
bool				parse_ambient(char **tokens, int count, t_ambient *ambient);
bool				parse_camera(char **tokens, int count, t_camera *camera);
bool				parse_light(char **tokens, int count, t_light *light);

// parse_objects_add.c
bool				add_sphere(t_scene *scene, t_sphere *new_sphere, int count);
bool				add_plane(t_scene *scene, t_plane *new_plane, int count);
bool				add_cylinder(t_scene *scene, t_cylinder *new_cylinder,
						int count);

// parse_objects_utils.c
void				rebuild_object_pointers(t_scene *scene);

// parse_objects.c
bool				parse_sphere(char **tokens, int count, t_sphere *sphere);
bool				parse_plane(char **tokens, int count, t_plane *plane);
bool				parse_cylinder(char **tokens, int count,
						t_cylinder *cylinder);
void				add_object(t_scene *scene, t_object_type type, void *data);

// parse_param.c
bool				parse_rgb(char *str, t_rgb_color *color_value);
bool				is_normalized_vector(t_vector3d vector_value);

// parse_param2.c
t_vector3d			parse_coordinates(char *str);
float				parse_fov(char *str);
bool				parse_ratio(char *str, float *ratio);
float				parse_measurements(char *str);

// parse_param3.c
t_vector3d			parse_normalized_vector(char *str);

// parse.c
bool				check_file_extension(char *extension);
int					verif_content(char *content, t_scene *scene, char ***tokens,
						int i);
bool				process_single_line(char *content, t_scene *scene,
						char **tokens);
bool				process_file_content(int fd, t_scene *scene);
bool				read_file(char *scene_file, t_scene *scene);

/* -------------------- ray --------------------- */

// ray_direction.c
t_vector3d			get_ray_direction(int x, int y, t_camera *cam,
						t_cam_basis basis);
t_ray				generate_ray(int x, int y, t_camera *cam);

// ray_generator.c
t_vector3d			negative_vector(t_vector3d vector);
t_vector3d			normalize(t_vector3d vector);
t_cam_basis			camera_basis(t_camera *cam);

/* -------------------- utils --------------------- */

// error.c
void				error_msg(int status);
void				cleanup_and_exit(int status);
bool				parse_error(const char *str);

// free.c
void				free_split(char **tokens);
void				free_scene(t_scene *scene);

// math.c
t_vector3d			add_vectors(t_vector3d a, t_vector3d b);
t_vector3d			cross_product(t_vector3d a, t_vector3d b);
t_vector3d			subtract_vectors(t_vector3d a, t_vector3d b);
t_vector3d			scalar_multiplication(float k, t_vector3d vector);
float				dot_product(t_vector3d a, t_vector3d b);

// utils.c
int					skip_spaces(char *line);
void				ignore_end_spaces(char *line);
void				replace_with_spaces(char *line);
char				**split_line(char *line);

// utils2.c
bool				ft_isnumber(char *str);
bool				ft_isfloat(const char *str);
float				string_to_float(char *str);

#endif