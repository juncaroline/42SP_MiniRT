#include "../../includes/minirt.h"

// #include "../../library/libft/libft.h"
// #include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>

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
