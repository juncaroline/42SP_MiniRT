/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:06:46 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/11 13:57:59 by cabo-ram         ###   ########.fr       */
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

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

# define M_PI 3.14159265358979323846

# define EPSILON 1e-6
# define CLOSE_TO_ZERO_EPSILON 1e-12

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

typedef struct s_sphere
{
	t_vector3d	sphere_center;
	float		diameter;
	t_rgb_color	color;
}	t_sphere;

// quadratic equations in ray-geometry intersection calculations
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

typedef struct s_cylinder_projection
{
	t_vector3d	oc;
	float		oc_proj_v;
	t_vector3d	oc_perpendicular;
	float		d_proj_v;
	t_vector3d	projected_d;
	t_vector3d	d_perpendicular;
}	t_cylinder_projection;

// quadratic equations in ray-geometry intersection calculations
typedef struct s_cylinder_quad
{
	float	radius;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	nearest;
	float	farther;
	float	t_hit;
}	t_cylinder_quad;

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

	t_rgb_color	color;

	t_object	*object;
}	t_intersec_info;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	int			object_count;
	t_sphere	*sphere;
	int			sphere_count;
	t_plane		*plane;
	int			plane_count;
	t_cylinder	*cylinder;
	int			cylinder_count;
}	t_scene;

// closest_hit.c
t_intersec_info	find_closest_sphere(t_ray *ray, t_sphere *spheres,
						int count);
t_intersec_info	find_closest_plane(t_ray *ray, t_plane*planes, int count);
t_intersec_info	find_closest_cylinder(t_ray *ray, t_cylinder *cylinders,
						int count);
t_intersec_info	find_closest_interesection(t_ray *ray, t_scene *scene);

// error.c
void				error_msg(int status);

// init.c
void				esc_command(void *param);
void				esc_command(void *param);
int32_t				init_scene(t_scene *scene);
// int32_t			init(void);

// intersect_cylinder_calc.c
void				init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
						t_cylinder_projection *proj);
bool				solve_cylinder_quadratic(t_cylinder_projection *proj,
						t_cylinder *cylinder, t_cylinder_quad *quad);
bool				validate_cylinder_intersec(t_ray *ray, t_cylinder *cylinder,
						t_cylinder_quad *quad);
t_vector3d			calculate_cylinder_normal(t_cylinder *cylinder,
						t_vector3d point);

// intersect_cylinder_aux.c
t_plane				create_cylinder_cap_plane(t_cylinder *cylinder,
						bool is_top_cap);
bool				is_intersection_within_cap_radius(
						t_vector3d intersection_point, t_vector3d cap_center,
						float cylinder_diameter);
bool				ray_intersects_cylinder_cap(t_ray *ray,
						t_cylinder *cylinder, bool is_top_cap,
						t_intersec_info *info);
t_intersec_info	ray_intersects_cylinder_surface(t_ray *ray,
						t_cylinder *cylinder);

// intersect_cylinder.c
void				compute_cylinder_cap_intersections(t_ray *ray,
						t_cylinder *cylinder, t_intersec_info *bottom_cap,
						t_intersec_info *top_cap);
t_intersec_info	select_closest_intersection(
						t_intersec_info surface,
						t_intersec_info bottom_cap,
						t_intersec_info top_cap, t_rgb_color color);
t_intersec_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder);

// intersect_plane.c
t_vector3d			calculate_plane_normal(t_plane *plane, t_vector3d point);
t_intersec_info	intersect_plane(t_ray *ray, t_plane *plane);

// intersect_sphere.c
t_vector3d			calculate_sphere_normal(t_sphere *sphere,
						t_vector3d intersec_point);
t_intersec_info	intersect_sphere(t_ray *ray, t_sphere *sphere);

// light.c
t_rgb_color			get_color(t_intersec_info hit, t_scene *scene);

// math.c
t_vector3d			add_vectors(t_vector3d a, t_vector3d b);
t_vector3d			cross_product(t_vector3d a, t_vector3d b);
t_vector3d			subtract_vectors(t_vector3d a, t_vector3d b);
t_vector3d			scalar_multiplication(float k, t_vector3d vector);
float				dot_product(t_vector3d a, t_vector3d b);

// parse_elements.c
bool				parse_ambient(char **tokens, int count, t_ambient *ambient);
bool				parse_camera(char **tokens, int count, t_camera *camera);
bool				parse_light(char **tokens, int count, t_light *light);

// parse_objects.c
bool				parse_sphere(char **tokens, int count, t_sphere *sphere);
bool				parse_plane(char **tokens, int count, t_plane *plane);
bool				parse_cylinder(char **tokens, int count,
						t_cylinder *cylinder);

// parse_objects_add.c
bool				add_sphere(t_scene *scene, t_sphere *new_sphere, int count);
bool				add_plane(t_scene *scene, t_plane *new_plane, int count);
bool				add_cylinder(t_scene *scene, t_cylinder *new_cylinder,
						int count);

// parse.c
void				check_file_extension(char *extension);
void				read_file(char *scene_file, t_scene *scene);
void				verify_elements(char *content, int i);

// ray_direction.c
t_vector3d			get_ray_direction(int x, int y, t_camera *cam,
						t_cam_basis basis);
t_ray				generate_ray(int x, int y, t_camera *cam);

// ray_generator.c
t_vector3d			negative_vector(t_vector3d vector);
t_vector3d			normalize(t_vector3d vector);
t_cam_basis			camera_basis(t_camera *cam);

// free.c
void				free_split(char **tokens);
void				free_scene(t_scene *scene);

// utils.c
int					skip_spaces(char *line);
void				replace_with_spaces(char *line);
char				**split_line(char *line);

// utils2.c
bool				ft_isnumber(char *str);
bool				ft_isfloat(const char *str);
float				string_to_float(char *str);

// validate_elements.c
bool				validate_elements(char **tokens, t_scene *scene);

// validate_param.c
bool				is_rgb_color(t_rgb_color color_value);
t_rgb_color			parse_rgb(char *str);
bool				is_normalized_vector(t_vector3d vector_value);
t_vector3d			parse_normalized_vector(char *str);

// validate_param2.c
t_vector3d			parse_coordinates(char *str);
float				parse_fov(char *str);
float				parse_ratio(char *str);
float				parse_measurements(char *str);

#endif