/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_quadratic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:38:16 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/21 11:41:36 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	solve_quadratic_equation(t_quadratic *quad)
{
	if (!quad || quad->a == 0.0f)
		return (false);
	quad->discriminant = quad->b * quad->b - 4.0f * quad->a * quad->c;
	if (quad->discriminant < 0.0f)
		return (false);
	quad->sqrt_discriminant = sqrtf(quad->discriminant);
	quad->nearest = (-quad->b - quad->sqrt_discriminant) / (2.0f * quad->a);
	quad->farther = (-quad->b + quad->sqrt_discriminant) / (2.0f * quad->a);
	if (quad->nearest < 0.0f && quad->farther < 0.0f)
		return (false);
	else if (quad->nearest < 0.0f)
		quad->t_hit = quad->farther;
	else if (quad->farther < 0.0f)
		quad->t_hit = quad->nearest;
	else
		quad->t_hit = (quad->nearest < quad->farther) ? quad->nearest : quad->farther;
	return (true);
}
