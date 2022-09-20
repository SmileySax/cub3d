#include "../cub3d.h"

static void	check_nswe(char **split_file, char *nswe)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	count = 0;
	k = 0;
	while (i < 6)
	{
		j = 0;
		while (ft_isspace(split_file[i][j]))
			j++;
		if (!(ft_strncmp(&split_file[i][j], nswe, 2)))
		{
			count++;
			k = i;
		}
		if (count > 1)
			print_error("Incorrectly submitted information: \"", \
				split_file[k], "\".\n", NULL);
		i++;
	}
}

static void	check_color(char **split_file, char *color)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	count = 0;
	k = 0;
	while (i < 6)
	{
		j = 0;
		while (ft_isspace(split_file[i][j]))
			j++;
		if (!(ft_strncmp(&split_file[i][j], color, 1)))
		{
			count++;
			k = i;
		}
		if (count > 1)
			print_error("Incorrectly submitted information: \"", \
				split_file[k], "\".\n", NULL);
		i++;
	}
}

static void	check_col_arg(char *line)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	if (!(ft_isspace(line[i])))
		count_word++;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			while (ft_isspace(line[i]) && line[i])
				i++;
			count_word++;
		}
		else
			i++;
	}
	if (count_word != 2)
		print_error("Invalid number of arguments: \"", line, "\".\n", NULL);
}

static void	check_start_param(char *line)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(line + i, "NO", 2) || ft_strncmp((line + i + 2), " ", 1))
		flag++;
	if (ft_strncmp(line + i, "SO", 2) || ft_strncmp((line + i + 2), " ", 1))
		flag++;
	if (ft_strncmp(line + i, "WE", 2) || ft_strncmp((line + i + 2), " ", 1))
		flag++;
	if (ft_strncmp(line + i, "EA", 2) || ft_strncmp((line + i + 2), " ", 1))
		flag++;
	if (ft_strncmp(line + i, "F", 1) || ft_strncmp((line + i + 1), " ", 1))
		flag++;
	if (ft_strncmp(line + i, "C", 1) || ft_strncmp((line + i + 1), " ", 1))
		flag++;
	if (flag != 5)
		print_error("Incorrectly submitted information: \"", line, "\".\n", NULL);
}

void	check_map_info(char **split_file)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		check_col_arg(split_file[i]);
		check_start_param(split_file[i]);
		i++;
	}
	check_nswe(split_file, "NO");
	check_nswe(split_file, "SO");
	check_nswe(split_file, "WE");
	check_nswe(split_file, "EA");
	check_color(split_file, "F");
	check_color(split_file, "C");
}
