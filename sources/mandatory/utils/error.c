/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:27:03 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/07/23 15:07:52 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

void	error_msg(int status)
{
	if (status == 1)
		printf("Invalid file extension.\n");
	else if (status == 2)
		printf("Error opening file.\n");
	else if (status == 3)
		printf("Empty file!\n");
	exit(status);
}
