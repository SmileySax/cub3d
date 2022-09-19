#include "../cub3d.h"

void	error_read(int rd)
{
	if (rd == 0)
		print_error("The file is empty.\n", NULL, NULL, NULL);
	else if (rd == -1)
		print_error("The file is not readable.\n", NULL, NULL, NULL);
}

static int	number_of_characters_in_the_file(char *file)
{
	int		fd;
	ssize_t	rd;
	char	buf[2];
	int		len_file;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error("The file does not open: ", file, "\n", NULL);
	buf[1] = '\0';
	len_file = 0;
	rd = read(fd, &buf[0], 1);
	if (rd)
		len_file++;
	while (rd > 0)
	{
		rd = read(fd, &buf[0], 1);
		len_file++;
	}
	if (rd == -1)
		error_read(rd);
	if (len_file == 0)
		error_read(len_file);
	close(fd);
	return (len_file);
}

static void	wrapper_reading_a_file(int fd, char **str, char *file)
{
	int			rd;
	int			len_file;

	len_file = number_of_characters_in_the_file(file);
	*str = (char *)malloc(sizeof(char) * (len_file + 1));
	if (*str == NULL)
		print_error("Memory allocation error in the function: ", \
		"wrapper_reading_a_file ", "*str == NULL\n", NULL);
	rd = read(fd, *str, len_file);
	if (rd == -1)
		error_read(rd);
	(*str)[++len_file] = '\0';
	close(fd);
}

void	reading_a_file(char ***split_file, int fd, char *file)
{
	char	*str;

	wrapper_reading_a_file(fd, &str, file);
	*split_file = ft_split(str, '\n');
	if (*split_file == NULL)
		print_error("The function ft_split() returned NULL: ", \
		"\nreading_a_file()", "\n*split_file == NULL\n", NULL);
	free(str);
}
