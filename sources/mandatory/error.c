#include "../../includes/minirt.h"

// void	error_msg(int status)
// {
// 	if (status == 1)
// 		ft_putstr_fd("Please insert a valid file. i.e.: ./fdf 'file'\n", 1);
// 	else if (status == 2)
// 		ft_putstr_fd("Failed to allocate memory!\n", 1);
// 	else if (status == 3)
// 		ft_putstr_fd("Failed to create image!\n", 1);
// 	else if (status == 4)
// 		ft_putstr_fd("Invalid map file.\n", 1);
// 	else if (status == 5)
// 		ft_putstr_fd("Error opening file.\n", 1);
// 	else if (status == 6)
// 		ft_putstr_fd("No map to show.\n", 1);
// 	exit(status);
// }

void	error_msg(int status)
{
	if (status == 1)
		ft_putstr_fd("Invalid file extension.\n", 1);
	else if (status == 2)
		ft_putstr_fd("Error opening file.\n", 1);
	else if (status == 3)
		ft_putstr_fd("Empty file!\n", 1);
	exit(status);
}
