/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:31 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/07/01 18:30:26 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Generic texture
t_vector3d	apply_bump_map(t_intersection_info hit)
{
	t_vector3d	perturbation;
	t_vector3d	new_vector;
	float		scale;

	scale = 0.3f;
	perturbation.x = sinf(hit.intersec_point.y * 5.0f) * scale;
	perturbation.y = cosf(hit.intersec_point.x * 5.0f) * scale;
	perturbation.z = sinf(hit.intersec_point.z * 5.0f) * scale;
	new_vector = add_vectors(hit.normal, perturbation);
	return (normalize(new_vector));
}


// Texture from img -> imagem apenas como "pintura" esta implementando a cor
#define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"

typedef struct s_texture
{
	int		width;
	int		height;
	int		channels;
	unsigned char *data;
}	t_texture;

// add nas estruturas dos objs
// bool		has_texture;

// add no t_intersec_info
// t_uv	uv;

t_texture	load_texture(const char *filename)
{
	t_texture	texture;

	texture.data = stbi_load(filename,
		&texture.width, &texture.height, &texture.channels, 3);
	if (!texture.data)
	{
		printf("Erro ao carregar textura: %s\n", filename);
		exit(1);
	}
	return (texture);
}

t_rgb_color	sample_texture(t_texture *tex, float u, float v)
{
	int	x = (int)(u * tex->width) % tex->width;
	int	y = (int)((1.0f - v) * tex->height) % tex->height;

	int	index = (y * tex->width + x) * 3;

	t_rgb_color color;
	color.red = tex->data[index];
	color.green = tex->data[index + 1];
	color.blue = tex->data[index + 2];
	return (color);
}

// Add ao hit de interseccao
// if (hit.has_texture)
// {
// 	t_rgb_color tex_color = sample_texture(hit.texture, hit.u, hit.v);
// 	hit.color = tex_color;
// }

// Calucular o u e o v para cada tipo de obj
// float theta = acos(hit.normal.y);
// float phi = atan2(hit.normal.z, hit.normal.x) + M_PI;
// hit.u = phi / (2.0f * M_PI);
// hit.v = theta / M_PI;

// aplicar a cor da textura
// int tex_x = (int)(uv.u * (texture_width - 1));
// int tex_y = (int)(uv.v * (texture_height - 1));


typedef struct s_uv {
	float u;
	float v;
}	t_uv;

t_uv	uv_sphere(t_vector3d point, t_vector3d center)
{
	t_uv	uv;
	t_vector3d	p;
	float	theta, phi;

	p = subtract_vectors(point, center);
	p = normalize(p);
	theta = atan2f(p.z, p.x);  // Longitude [-PI, PI]
	phi = acosf(p.y);          // Latitude [0, PI]
	uv.u = (theta + M_PI) / (2.0f * M_PI);  // Normaliza para [0,1]
	uv.v = phi / M_PI;
	return (uv);
}

t_uv	uv_plane(t_vector3d point, t_vector3d origin, float scale)
{
	t_uv	uv;
	t_vector3d	p;

	p = subtract_vectors(point, origin);
	uv.u = fmodf(fabsf(p.x) * scale, 1.0f);
	uv.v = fmodf(fabsf(p.z) * scale, 1.0f);
	return (uv);
}

t_uv	uv_cylinder(t_vector3d point, t_vector3d base, t_vector3d axis, float height)
{
	t_uv	uv;
	t_vector3d	p;
	float	theta;
	float	y;

	p = subtract_vectors(point, base);

	y = dot_product(p, axis);
	t_vector3d	p_perp = subtract_vectors(p, scalar_multiplication(y, axis));
	p_perp = normalize(p_perp);
	theta = atan2f(p_perp.z, p_perp.x);
	uv.u = (theta + M_PI) / (2.0f * M_PI);
	uv.v = y / height;  // Normalizado pela altura
	return (uv);
}

t_uv	uv_cone(t_vector3d point, t_vector3d apex, t_vector3d axis, float height)
{
	t_uv	uv;
	t_vector3d	p;
	float	y;
	float	theta;

	p = subtract_vectors(point, apex);
	y = dot_product(p, axis);
	t_vector3d	p_perp = subtract_vectors(p, scalar_multiplication(y, axis));
	p_perp = normalize(p_perp);
	theta = atan2f(p_perp.z, p_perp.x);
	uv.u = (theta + M_PI) / (2.0f * M_PI);
	uv.v = y / height;  // Normalizado pela altura
	return (uv);
}

// IMPORTANTEEEEEEEEEEEEEEEE
// Dar free em tds as imagem de textura guardadas
// stbi_image_free(texture.data)


// Normal mapping -> texturizando com img
typedef struct s_texture
{
	int		width;
	int		height;
	int		channels;
	unsigned char *data;
}	t_texture;

typedef struct s_material
{
	float shininess;
	bool has_texture;
	t_texture *diffuse_texture;

	t_texture *normal_map;

}	t_material;

// Transformando a base tangente para espaço mundo

void compute_tg_sphere_and_plane(t_vector3d normal, t_vector3d *T, t_vector3d *B)
{
    t_vector3d up = {0.0f, 1.0f, 0.0f};
    if (fabsf(dot_product(normal, up)) > 0.99f)
        up = (t_vector3d){1.0f, 0.0f, 0.0f};
    *T = normalize(cross_product(up, normal));
    *B = cross_product(normal, *T);
}

void compute_tg_cylinder_and_cone(t_vector3d normal, t_vector3d axis, t_vector3d *T, t_vector3d *B)
{
    *T = normalize(cross_product(axis, normal));
    *B = cross_product(normal, *T);
}


// no get_color
if (hit.material->normal_map)
{
	t_rgb_color normal_color = sample_texture(hit.material->normal_map, hit.uv.u, hit.uv.v);

	t_vector3d normal_map_vec;
	normal_map_vec.x = (normal_color.red / 255.0f) * 2.0f - 1.0f;
	normal_map_vec.y = (normal_color.green / 255.0f) * 2.0f - 1.0f;
	normal_map_vec.z = (normal_color.blue / 255.0f); // geralmente Z é [0,1]

	normal_map_vec.z = normal_map_vec.z * 2.0f - 1.0f;

	normal_map_vec = normalize(normal_map_vec);


	t_vector3d T, B, N = hit.normal;
	t_vector3d tangent_normal;
	t_vector3d world_normal;

	// calcular base tangente
	if (hit.object->type == "sp" || hit.object->type == "pl")
		compute_tg_sphere_and_plane(N, &T, &B);
	else if (hit.object->type == "cy" || hit.object->type == "cn")
		compute_tg_cylinder_and_cone(N, hit.axis, &T, &B);

	// converter normal para espaço mundo
	world_normal.x = T.x * tangent_normal.x + B.x * tangent_normal.y + N.x * tangent_normal.z;
	world_normal.y = T.y * tangent_normal.x + B.y * tangent_normal.y + N.y * tangent_normal.z;
	world_normal.z = T.z * tangent_normal.x + B.z * tangent_normal.y + N.z * tangent_normal.z;

	hit.normal = normalize(world_normal);

}
