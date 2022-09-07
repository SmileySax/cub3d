#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	t %= 256;
	r %= 256;
	g %= 256;
	b %= 256;
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	ft_keydealer(int key, t_data *map)
{
	(void)map;
	printf("%d \n",key);
	if (key == 53)
		exit(0);
	else if (key == 126)
	{
		printf("up arrow\n");
	}
	else if (key == 125)
	{
		printf("down arrow\n");
	}
	else if (key == 123)
	{
		// printf("left arrow\n");
		map->fPlayerA -= 0.1f;
		if (map->fPlayerA < 0)
			map->fPlayerA += 2 * (float)PI;
		printf ("angle %f\n", map->fPlayerA);
	}
	else if (key == 124)
	{
		// printf("right arrow\n");
		map->fPlayerA += 0.1f;
		if (map->fPlayerA > 2.0f * (float)PI)
			map->fPlayerA -= 2.0f * (float)PI;
		printf ("angle %f\n", map->fPlayerA);

	}
	else if (key == 13)
	{
		// printf("front (w)\n");
		map->fPlayerX += cos(map->fPlayerA) * 0.05;
		map->fPlayerY += sin(map->fPlayerA) * 0.05;
		printf ("pos %f %f\n", map->fPlayerX, map->fPlayerY);
	}
	else if (key == 1)
	{
		// printf("rev (s)\n");
		map->fPlayerX -= cos(map->fPlayerA) * 0.05;
		map->fPlayerY -= sin(map->fPlayerA) * 0.05;
	}
	else if (key == 0)
	{
		// printf("left (a)\n");
		map->fPlayerX += sin(map->fPlayerA) * 0.05;
		map->fPlayerY -= cos(map->fPlayerA) * 0.05;
	}
	if (key == 2)
	{
		// printf("right (d)\n");
		map->fPlayerX -= sin(map->fPlayerA) * 0.05;
		map->fPlayerY += cos(map->fPlayerA) * 0.05;
	}
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	ft_draw(map);
	return (0);
}

// int	ft_exit_x_button(t_map *map)
// {
// 	mlx_destroy_image(map->mlx_ptr, map->img);
// 	exit(1);
// }

t_point	ft_init_point(int x, int y, int c)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.c = c;
	return (p);
}

t_fpoint	ft_init_fpoint(float x, float y, int c)
{
	t_fpoint	p;

	p.x = x;
	p.y = y;
	p.c = c;
	return (p);
}

t_point	ft_nullify_point(t_point p)
{
	p = ft_init_point(0, 0, create_trgb(0, 0, 0, 0));
	return p;
}

t_fpoint	ft_nullify_fpoint(t_fpoint p)
{
	p = ft_init_fpoint(0, 0, create_trgb(0, 0, 0, 0));
	return p;
}

// t_point	ft_pshift(t_point p, int x, int y)
// {
// 	p.x += x;
// 	p.y += y;
// 	return (p);
// }

t_fpoint	ft_fpincr(t_fpoint p, t_fpoint dp)
{
	int			c[4];

	if (dp.c)
	{
		c[0] = get_t(p.c);
		c[1] = get_r(p.c);
		c[2] = get_g(p.c);
		c[3] = get_b(p.c);
		c[0] += get_t(dp.c);
		c[1] += get_r(dp.c);
		c[2] += get_g(dp.c);
		c[3] += get_b(dp.c);
		p.c = create_trgb(c[0], c[1], c[2], c[3]);
	}
	p.x = p.x + dp.x;
	p.y = p.y + dp.y;
	return (p);
}

t_fpoint	ft_pdelta(t_point p1, t_point p2)
{
	t_fpoint	dp;
	int			max;
	int			c[4];

	dp.x = (float)(p2.x - p1.x);
	dp.y = (float)(p2.y - p1.y);
	c[0] = get_t(p2.c) - get_t(p1.c);
	c[1] = get_r(p2.c) - get_r(p1.c);
	c[2] = get_g(p2.c) - get_g(p1.c);
	c[3] = get_b(p2.c) - get_b(p1.c);
	max = (int)fmaxf(fabsf(dp.x), fabsf(dp.y));
	if (max)
	{
		dp.x /= max;
		dp.y /= max;
		c[0] /= max;
		c[1] /= max;
		c[2] /= max;
		c[3] /= max;
		dp.c = create_trgb(c[0], c[1], c[2], c[3]);
	}
	else
		return (ft_nullify_fpoint(dp));
	return (dp);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *map, t_point p1, t_point p2)
{
	t_fpoint	dp;
	t_fpoint	p;

	p = ft_init_fpoint((float)p1.x, (float)p1.y, p1.c);
	dp = ft_pdelta(p1, p2);
	while (((int)p.x - p2.x) || ((int)p.y - p2.y))
	{
		if (p.x >= 0 && p.y >= 0 && p.x < WIN_W && p.y < WIN_H)
			my_mlx_pixel_put(map, (int)p.x, (int)p.y, p.c);
		p = ft_fpincr(p, dp);
	}
}

void	my_map_put(t_data *map)
{
	int	y;
	int	x;
	int	c;
	t_point	p[4];

	y = 0;
	x = 0;
	while (y < map->h)
	{
		while (x < map->w)
		{
			if (map->map[y * map->w + x] == '1')
				c = WALL_COLOR;
			else
				c = BG_COLOR;
			p[0] = ft_init_point(x * MAP_SIZE, y * MAP_SIZE, c);
			p[1] = ft_init_point(x * MAP_SIZE, (y + 1) * MAP_SIZE - 1, c);
//			p[3] = ft_init_point((x + 1) * MAP_SIZE - 1, (y + 1) * MAP_SIZE - 1, c);
			p[2] = ft_init_point((x + 1) * MAP_SIZE - 1, y * MAP_SIZE, c);
			while (p[0].x != p[2].x)
			{
				my_mlx_line_put(map, p[0], p[1]);
				p[0].x++;
				p[1].x++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	ft_find_player(t_data *map)
{
	int i = 0;
	int j = 0;

	while (i < 6)
	{
		while (j < 6)
		{
			if (map->map[i * 6 + j] == 'X')
			{
				map->fPlayerX = (float)j + 0.5f;
				map->fPlayerY = (float)i + 0.5f;
				map->fPlayerA = 0.0f;
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	my_player_put(t_data *map)
{
	int	i;
	int	j;
	int	pos[3];

	if (!map->fPlayerX)
		printf("no player on map!");
	else
	{
		pos[0] = (int)fmaxf(MAP_SIZE/10.0f, 1.0f);
		i = pos[0];
		j = i;
		pos[1] = (int)(map->fPlayerX * (float)MAP_SIZE);
		pos[2] = (int)(map->fPlayerY * (float)MAP_SIZE);
		while (i >= 0)
		{
			while (j >= -pos[0])
			{
				if(i * i + j * j < pos[0] * pos[0])
				{
					my_mlx_pixel_put(map, pos[1] + i, pos[2] + j, PLAYER_COLOR);
					my_mlx_pixel_put(map, pos[1] - i, pos[2] + j, PLAYER_COLOR);
				}
				j--;
			}
			j = pos[0];
			i--;
		}
		i = 9;
		while (i++ < 20)
			my_mlx_pixel_put(map, pos[1] + (i/10.0f) * pos[0] * cos(map->fPlayerA), pos[2] + (i/10.0f) * pos[0] * sin(map->fPlayerA), PLAYER_COLOR);
	}
}


void	ft_map(char *map)
{
	int i = 0;
	int j = 0;

	while (i < 6)
	{
		while (j < 6)
		{
			if (map[i * 6 + j] == '1')
				printf("[]");
			else if (map[i * 6 + j] == 'X')
				printf("><");
			else
				printf("  ");
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
}

void	ft_draw(t_data *img)
{
	my_map_put(img);
	my_player_put(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img, 0, 0);
}

int	main(int ac, char **av)
{
	char	*m=  "111111101001101011100001100X01111111";
	// 			(1, 1, 1, 1, 1, 1,
	// 			1, 0, 1, 0, 0, 1,
	// 			1, 0, 1, 0, 1, 1,
	// 			1, 0, 0, 0, 0, 1,
	// 			1, 0, 0, 0, 0, 1,
	// 			1, 1, 1, 1, 1, 1);
	t_data	map;

	map.map = m;
	map.h = 6;
	map.w = 6;
	if (ac > 3)
		printf("%s", av[2]);
	ft_map(m);
	map.mlx_ptr = mlx_init();
	map.win_ptr = mlx_new_window(map.mlx_ptr, 1000, 1000, "cub3d");
	map.img = mlx_new_image(map.mlx_ptr, 1000, 1000);
	map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length,
								&map.endian);
	if(!ft_find_player(&map))
		printf("no player on map!");
	ft_draw(&map);
	mlx_hook(map.win_ptr, 2, 0, ft_keydealer, (void *)&map);
	// mlx_hook(mlx_win, 17, 0, ft_exit_x_button, map);
	mlx_loop(map.mlx_ptr);
	return 0;
}