/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:47 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 19:41:24 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

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
# define EPSILON_SHADOW 1e-3

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
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
	t_rgb_color	color;
}	t_light;

typedef struct s_surface
{
	bool			has_checker;
	mlx_texture_t	*bump_texture;
	char			*texture_path;
	bool			bump;
}	t_surface;

// quadratic equations in ray-geometry intersection calculations
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

typedef struct s_sphere
{
	t_vector3d		sphere_center;
	float			diameter;
	t_rgb_color		color;
	t_surface		surface;
}	t_sphere;

typedef struct s_plane
{
	t_vector3d		plane_point;
	t_vector3d		vector;
	t_rgb_color		color;
	t_surface		surface;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3d		cylinder_center;
	t_vector3d		vector;
	float			diameter;
	float			height;
	t_rgb_color		color;
	t_surface		surface;
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

typedef struct s_cone
{
	t_vector3d		cone_center;
	t_vector3d		vector;
	float			diameter;
	float			height;
	t_rgb_color		color;
	t_surface		surface;
}	t_cone;

typedef struct s_cone_projection
{
	t_vector3d	oc;
	float		k;
	float		v_dot_d;
	float		oc_dot_d;
}	t_cone_projection;

typedef struct s_cone_intersec
{
	t_vector3d	intersec_point;
	t_vector3d	vector_to_point;
	float		height_projection;
	t_vector3d	direction;
	t_vector3d	cone_vertex;
}	t_cone_intersec;

typedef struct s_object
{
	t_object_type	type;
	void			*data;
	t_rgb_color		white;
	t_rgb_color		black;
}	t_object;

typedef struct s_intersec_info
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
	t_light		*light;
	int			light_count;
	t_object	*objects;
	int			object_count;
	t_sphere	*sphere;
	int			sphere_count;
	t_plane		*plane;
	int			plane_count;
	t_cylinder	*cylinder;
	int			cylinder_count;
	t_cone		*cone;
	int			cone_count;
}	t_scene;

typedef struct s_surface_mapping
{
	float		u;
	float		v;
	int			texture_x;
	int			texture_y;
	int			i;
	uint8_t		height_value;
	float		bump_strength;
	t_vector3d	tangent;
	t_vector3d	bitangent;
	t_vector3d	local;
	t_vector3d	normal;
	float		du;
	float		dv;
	int			x1;
	int			y1;
	uint8_t		h1;
	uint8_t		h2;
	int			i1;
	int			i2;
	float		theta;
	float		height;
}	t_surface_mapping;

/* -------------------- bump --------------------- */

// bump_map_bonus.c
mlx_texture_t	**get_bump_texture(t_object *object);
char			**get_texture_path(t_object *object);
bool			load_object_texture(t_object *object);
bool			load_scene_textures(t_scene *scene);

// bump_map_generic_bonus.c
t_vector3d		apply_bump_map(t_intersec_info hit);

// bump_map_utils_bonus.c
bool			init_bump_mapping(t_object *object, t_vector3d point,
					mlx_texture_t *bump_texture, t_surface_mapping *bump);
bool			calculate_bump_gradients(mlx_texture_t *bump_texture,
					t_surface_mapping *bump);
bool			get_uv_coordinates(t_object *object, t_vector3d point, float *u,
					float *v);
void			free_object_texture(t_object *object);

// bump_map_uv_bonus.c
void			uv_map_sphere(t_vector3d point, t_sphere *sphere, float *u,
					float *v);
void			uv_map_plane(t_vector3d point, t_plane *plane, float *u,
					float *v);
void			uv_map_cylinder(t_vector3d point, t_cylinder *cylinder,
					float *u, float *v);
void			uv_map_cone(t_vector3d point, t_cone *cone, float *u, float *v);

// bump_map_uv_calc_bonus.c
void			calculate_plane_uv(t_vector3d point, t_plane *plane,
					t_surface_mapping *bump);
void			calculate_cylinder_uv(t_vector3d point, t_cylinder *cylinder,
					t_surface_mapping *bump);
void			calculate_cone_uv(t_vector3d point, t_cone *cone,
					t_surface_mapping *bump);

// bump_map_vectors_bonus.c
t_vector3d		calc_vectors_sphere(t_vector3d normal, t_surface_mapping *bump);
t_vector3d		calc_vectors_plane(t_vector3d normal, t_surface_mapping *bump);
t_vector3d		calc_vectors_cylinder(t_vector3d normal,
					t_surface_mapping *bump, t_cylinder *cylinder);
t_vector3d		calc_vectors_cone(t_vector3d normal, t_surface_mapping *bump,
					t_cone *cone);

/* -------------------- checkerboard --------------------- */

// checkerboard_bonus.c
void			get_plane_coordinates(t_vector3d point, t_plane *plane,
					float *u, float *v);
t_rgb_color		object_pattern(t_vector3d point, t_object *object,
					float scale);

// checkerboard_calc_bonus.c
float			compute_cylinder_u_coord(t_surface_mapping mapping);
float			compute_cylinder_v_coord(t_surface_mapping mapping,
					t_cylinder *cylinder);
float			compute_cone_u_coord(t_surface_mapping mapping,
					t_vector3d axis);
float			compute_cone_v_coord(t_surface_mapping mapping, t_cone *cone);

// checkerboard_map_bonus.c
t_rgb_color		checkerboard_pattern(float u, float v, float scale,
					t_object *object);
void			get_sphere_coordinates(t_vector3d point, t_sphere *sphere,
					float *u, float *v);
void			get_cylinder_coordinates(t_vector3d point, t_cylinder *cylinder,
					float *u, float *v);
void			get_cone_coordinates(t_vector3d point, t_cone *cone, float *u,
					float *v);

/* -------------------- init --------------------- */

// handle_param_bonus.c
bool			handle_sphere(char **tokens, t_scene *scene);
bool			handle_plane(char **tokens, t_scene *scene);
bool			handle_cylinder(char **tokens, t_scene *scene);
bool			handle_cone(char **tokens, t_scene *scene);
bool			handle_light(char **tokens, t_scene *scene);

// init_bonus.c
void			esc_command(void *param);
void			set_pixel(mlx_image_t *img, int x, int y, t_rgb_color c);
void			set_color(t_scene *scene, mlx_image_t *img, int x, int y);
void			render(t_scene *scene, mlx_image_t *img);
int32_t			init_scene(t_scene *scene);

// validate_elements.c
void			verify_elements(char *content, int i);
int				count_tokens(char **tokens);
bool			validate_elements(char **tokens, t_scene *scene);

/* -------------------- intersection --------------------- */

// closest_hit_bonus.c
t_intersec_info	intersect_object(t_ray *ray, t_object *object, t_scene *scene);
t_intersec_info	find_closest_object(t_ray *ray, t_object *objects, int count,
					t_scene *scene);
t_intersec_info	find_closest_interesection(t_ray *ray, t_scene *scene);

// intersect_cone_aux_bonus.c
t_vector3d		insert_cone_bump_map(t_cone *cone, t_vector3d point,
					t_vector3d normal, mlx_texture_t *bump_texture);
t_intersec_info	ray_intersects_cone_surface(t_ray *ray,
					t_cone *cone, t_cone_intersec *base);

// intersect_cone_aux2_bonus.c
void			init_cone_struct(t_object *object, t_cone *cone);
t_plane			create_cone_plane(t_cone *cone, bool is_covered,
					t_cone_intersec *base);
bool			is_intersection_within_cone_cap_radius(
					t_vector3d intersection_point, t_vector3d cap_center,
					float cone_diameter);
bool			ray_intersects_cone_cap(t_ray *ray, t_cone *cone,
					bool is_covered, t_intersec_info *info);

// intersect_cone_bonus.c
t_vector3d		calculate_cone_normal(t_cone *cone, t_vector3d point,
					t_cone_intersec *base);
void			compute_cone_cap_intersections(t_ray *ray, t_cone *cone,
					t_intersec_info *bottom_cap, t_intersec_info *top_cap);
t_intersec_info	select_closest_intersection_cone(
					t_intersec_info surface_info, t_intersec_info base_info,
					t_intersec_info top_info);
t_intersec_info	intersect_cone(t_ray *ray, t_cone *cone);

// intersect_cone_calc_bonus.c
void			init_cone_base(t_cone *cone, t_cone_intersec *base);
void			init_cone_projection(t_ray *ray, t_cone *cone,
					t_cone_projection *proj, t_cone_intersec *base);
void			calculate_equation(t_cone_projection *proj, t_cone *cone,
					t_quadratic *quad, t_ray *ray);
bool			solve_cone_quadratic(t_cone_projection *proj,
					t_cone *cone, t_quadratic *quad, t_ray *ray);
bool			validate_cone_intersec(t_ray *ray, t_cone *cone,
					t_quadratic *quad, t_cone_intersec *base);

// intersect_cylinder_aux_bonus.c
bool			ray_intersects_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
					bool is_top_cap, t_intersec_info *info);
t_vector3d		insert_cylinder_bump_map(t_cylinder *cylinder, t_vector3d point,
					t_vector3d normal, mlx_texture_t *bump_texture);
t_intersec_info	ray_intersects_cylinder_surface(t_ray *ray,
					t_cylinder *cylinder);

// intersect_cylinder_aux2_bonus.c
void			init_cylinder_struct(t_object *object, t_cylinder *cylinder);
void			get_top_cap_coord(t_vector3d point, t_cylinder *cylinder,
					float *coord1, float *coord2);
void			get_bottom_cap_coord(t_vector3d point, t_cylinder *cylinder,
					float *coord1, float *coord2);

// intersect_cylinder_bonus.c
t_plane			create_cylinder_cap_plane(t_cylinder *cylinder,
					bool is_top_cap);
bool			is_intersection_within_cap_radius(t_vector3d intersection_point,
					t_vector3d cap_center, float cylinder_diameter);
void			compute_cylinder_cap_intersections(t_ray *ray,
					t_cylinder *cylinder, t_intersec_info *bottom_cap,
					t_intersec_info *top_cap);
t_intersec_info	select_closest_intersection(
					t_intersec_info surface, t_intersec_info bottom_cap,
					t_intersec_info top_cap, t_rgb_color color);
t_intersec_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder);

// intersect_cylinder_calc_bonus.c
void			init_cylinder_projection(t_ray *ray, t_cylinder *cylinder,
					t_cylinder_projection *proj);
bool			solve_cylinder_quadratic(t_cylinder_projection *proj,
					t_cylinder *cylinder, t_quadratic *quad);
bool			validate_cylinder_intersec(t_ray *ray, t_cylinder *cylinder,
					t_quadratic *quad);
t_vector3d		calculate_cylinder_normal(t_cylinder *cylinder,
					t_vector3d point);

// intersect_plane_bonus.c
t_vector3d		calculate_plane_normal(t_plane *plane, t_vector3d point);
t_vector3d		insert_plane_bump_map(t_plane *plane, t_vector3d point,
					t_vector3d normal, mlx_texture_t *bump_texture);
t_intersec_info	intersect_plane(t_ray *ray, t_plane *plane);

// intersect_quadratic_bonus.c
bool			solve_quadratic_equation(t_quadratic *quad);

// intersect_sphere_bonus.c
t_vector3d		insert_sphere_bump_map(t_sphere *sphere, t_vector3d point,
					t_vector3d normal, mlx_texture_t *bump_texture);
t_intersec_info	intersect_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene);

// intersect_sphere_calc_bonus.c
void			init_sphere_struct(t_object *object, t_sphere *sphere);
t_quadratic		intersect_sphere_quad(t_ray *ray, t_sphere *sphere);
bool			intersect_sphere_solution(t_quadratic quad, float *t);
t_vector3d		calculate_sphere_normal(t_sphere *sphere,
					t_vector3d point);

/* -------------------- ray --------------------- */

// ray_direction_bonus.c
t_vector3d		get_ray_direction(int x, int y, t_camera *cam,
					t_cam_basis basis);
t_ray			generate_ray(int x, int y, t_camera *cam);

// ray_generator_bonus.c
t_vector3d		negative_vector(t_vector3d vector);
t_vector3d		normalize(t_vector3d vector);
t_cam_basis		camera_basis(t_camera *cam);

/* -------------------- utils --------------------- */

// error_bonus.c
void			error_msg(int status);

// free_bonus.c
void			free_split(char **tokens);
void			free_scene(t_scene *scene);
void			free_scene_textures(t_scene *scene);

// math_bonus.c
t_vector3d		add_vectors(t_vector3d a, t_vector3d b);
t_vector3d		cross_product(t_vector3d a, t_vector3d b);
t_vector3d		subtract_vectors(t_vector3d a, t_vector3d b);
t_vector3d		scalar_multiplication(float k, t_vector3d vector);
float			dot_product(t_vector3d a, t_vector3d b);

// utils_bonus.c
int				skip_spaces(char *line);
void			replace_with_spaces(char *line);
char			**split_line(char *line);

// utils2_bonus.c
bool			ft_isnumber(char *str);
bool			ft_isfloat(const char *str);
float			string_to_float(char *str);

// light_bonus.c
t_rgb_color		scale_color(t_rgb_color c, float ratio);
t_rgb_color		max_color(t_rgb_color c);
t_rgb_color		add_color(t_rgb_color a, t_rgb_color b);
t_rgb_color		diff_color(t_intersec_info hit, t_light *light);
t_vector3d		reflection(t_intersec_info hit, t_light *light);
t_rgb_color		spec_color(t_intersec_info hit, t_scene *scene, t_light *light);
t_rgb_color		evaluate_lighting_effect(t_intersec_info hit, t_scene *scene, \
					t_light *light);
t_rgb_color		loop_color(t_intersec_info hit, t_scene *scene, \
					t_rgb_color ambient);
t_rgb_color		apply_light(t_intersec_info hit, t_scene *scene, t_ray ray);

// light_shadow.c
bool			in_shadow(t_scene *scene, t_intersec_info hit, t_light *light);
void			prepare_point(t_intersec_info *hit, t_ray ray);

// parse_elements.c
bool			parse_ambient(char **tokens, int count, t_ambient *ambient);
bool			parse_camera(char **tokens, int count, t_camera *camera);
bool			parse_light(char **tokens, int count, t_light *light);

// parse_objects_add.c
bool			add_sphere(t_scene *scene, t_sphere *new_sphere, int count);
bool			add_plane(t_scene *scene, t_plane *new_plane, int count);
bool			add_cylinder(t_scene *scene, t_cylinder *new_cylinder,
					int count);
bool			add_cone(t_scene *scene, t_cone *new_cone, int count);
bool			add_light(t_scene *scene, t_light *new_light, int count);

// parse_objects_utils.c
void			rebuild_object_pointers(t_scene *scene);

// parse_objects.c
bool			parse_sphere(char **tokens, int count, t_sphere *sphere);
bool			parse_plane(char **tokens, int count, t_plane *plane);
bool			parse_cylinder(char **tokens, int count,
					t_cylinder *cylinder);
bool			parse_cone(char **tokens, int count, t_cone *cone);
void			add_object(t_scene *scene, t_object_type type, void *data);

// parse.c
void			check_file_extension(char *extension);
void			get_content(char	**content, int fd);
int				verif_content(char *content, t_scene *scene, char ***tokens,
					int i);
void			read_file(char *scene_file, t_scene *scene);

// parse_param.c
bool			is_rgb_color(t_rgb_color color_value);
t_rgb_color		parse_rgb(char *str);
bool			is_normalized_vector(t_vector3d vector_value);
t_vector3d		parse_normalized_vector(char *str);

// parse_param2.c
t_vector3d		parse_coordinates(char *str);
float			parse_fov(char *str);
float			parse_ratio(char *str);
float			parse_measurements(char *str);

#endif