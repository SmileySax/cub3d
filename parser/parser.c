#include "../cub3d.h"

static void	check_env(char **map, int i, int j)
{
	int	flag;

	flag = 0;
	if (i != 0 && (map[i - 1][j] == '1' || map[i - 1][j] == '0'
		|| map[i - 1][j] == 'N' || map[i - 1][j] == 'S' || map[i - 1][j] == 'W'
		|| map[i - 1][j] == 'E'))
		flag++;
	if (map[i + 1] && (map[i + 1][j] == '1' || map[i + 1][j] == '0'
		|| map[i + 1][j] == 'N' || map[i + 1][j] == 'S' || map[i + 1][j] == 'W'
		|| map[i + 1][j] == 'E'))
		flag++;
	if (j != 0 && (map[i][j - 1] == '1' || map[i][j - 1] == '0'
		|| map[i][j - 1] == 'N' || map[i][j - 1] == 'S' || map[i][j - 1] == 'W'
		|| map[i][j - 1] == 'E'))
		flag++;
	if (map[i][j + 1] && (map[i][j + 1] == '1'
		|| map[i][j + 1] == '0'
		|| map[i][j + 1] == 'N' || map[i][j + 1] == 'S' || map[i][j + 1] == 'W'
		|| map[i][j + 1] == 'E'))
		flag++;
	if (flag != 4)
		print_error("The card is not closed.\n", NULL, NULL, NULL);
}

static void	map_valid(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
					|| map[i][j] == 'E')
					flag++;
				check_env(map, i, j);
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
		print_error("Incorrect symbols in the map!\n", NULL, NULL, NULL);
}

static void	recording_map(char **split_file)
{
	int		i;
	int		j;

	i = 0;
	while (split_file[i])
	{
		j = 0;
		while (split_file[i][j])
		{
			if (split_file[i][j] == ' ' || split_file[i][j] == '1'\
				|| split_file[i][j] == '0' || split_file[i][j] == 'N'\
				|| split_file[i][j] == 'S' || split_file[i][j] == 'W'\
				|| split_file[i][j] == 'E')
				j++;
			else
				print_error("Incorrect symbols in the map!\n", NULL, NULL, NULL);
		}
		i++;
	}
}

static void	overwriting_the_map(char ***map, char **map_file)
{
	int		len_map;
	int		i;

	while (map_file[len_map])
		len_map++;
	i = 0;
	*map = (char **)malloc(sizeof(char *) * (len_map + 1));
	while (map_file[i])
	{
		(*map)[i] = ft_strdup(map_file[i]);
		if ((*map)[i] == NULL)
			print_error("Memory allocation error in the function: ", \
		"overwriting_the_map ", "*map[i] == NULL\n", NULL);
		i++;
	}
	(*map)[i] = NULL;
}

void	parser(t_data *map, char *file)
{
	int		fd;
	int		i;
	char	**split_file;

	i = 0;
	split_file = NULL;
	checking_the_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error("The file does not open: ", file, "\n", NULL);
	reading_a_file(&split_file, fd, file);
	checking_card_information(split_file, fd);
	recording_file_information(split_file, data);
	recording_map(split_file + 6);
	overwriting_the_map(&map->map, split_file + 6);
	map_valid(map->map);
	ft_free_matrix(split_file);
	close(fd);
}
