#include "../cub3d.h"

void	check_file(char *file)
{
	int	i;

	i = (ft_strlen(file)) - 4;
	if (ft_strncmp(".cub\0", file + i, 4))
	{
		print_error("Incorrect file extension: ", file, "\n", NULL);
		exit (EXIT_FAILURE);
	}
}
