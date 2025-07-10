/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/10 11:56:53 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_intersection_info(t_intersection_info *info)
{
	info->intersection = false;
	info->dist_to_intersec = 0.0f;
	info->intersec_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info->normal = (t_vector3d){0.0f, 0.0f, 0.0f};
	info->over_point = (t_vector3d){0.0f, 0.0f, 0.0f};
	info->color = (t_rgb_color){0, 0, 0};
	info->object = NULL;
}
