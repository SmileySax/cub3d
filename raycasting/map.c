#include "../cub3d.h"

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

int	keydown(int key, t_data *map)
{
	if (key == 123)
		map->key.la = 1;
	else if (key == 124)
		map->key.ra = 1;
	else if (key == 13)
		map->key.w = 1;
	else if (key == 1)
		map->key.s = 1;
	else if (key == 0)
		map->key.a = 1;
	else if (key == 2)
		map->key.d = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

int	keyup(int key, t_data *map)
{
	if (key == 123)
		map->key.la = 0;
	else if (key == 124)
		map->key.ra = 0;
	else if (key == 13)
		map->key.w = 0;
	else if (key == 1)
		map->key.s = 0;
	else if (key == 0)
		map->key.a = 0;
	else if (key == 2)
		map->key.d = 0;
	return (0);
}

int	keydealer(t_data *map)
{
	//printf("%d \n",key);
	if (map->key.la == 1)
	{
		// printf("left arrow\n");
		map->fpa -= 0.05f;
		if (map->fpa <= 0.0f)
			map->fpa += 2 * PI;
		//printf ("angle %f\n", map->fPlayerA);
	}
	if (map->key.ra == 1)
	{
		// printf("right arrow\n");
		map->fpa += 0.05f;
		if (map->fpa > 2 * PI)
			map->fpa -= 2 * PI;
		//printf ("angle %f\n", map->fPlayerA);
	}

	float	xo, yo;
	int		ipx, ipx_add_xo, ipx_sub_xo, ipy, ipy_add_yo, ipy_sub_yo;

	if (cos(map->fpa) < 0)
		xo = -0.2f;
	else
		xo = 0.2f;
	if (sin(map->fpa) < 0)
		yo = -0.2f;
	else
		yo = 0.2f;
	ipx = (int)map->fpx;
	ipx_add_xo = (int)(map->fpx + xo);
	ipx_sub_xo = (int)(map->fpx - xo);
	ipy = (int)map->fpy;
	ipy_add_yo = (int)(map->fpy + yo);
	ipy_sub_yo = (int)(map->fpy - yo);
	// printf("x %d+%d-%d | y %d+%d-%d | p %d-%c\n", ipx, ipx_add_xo, ipx_sub_xo, ipy, ipy_add_yo, ipy_sub_yo, ipy * map->w + ipx_add_xo, map->map[ipy * map->w + ipx_add_xo]);

	if (map->key.w == 1)
	{
		// printf("front (w)\n");
		if(map->map[ipy * map->img.w + ipx_add_xo] != '1')
			map->fpx += cos(map->fpa) * 0.05;
		if(map->map[ipy_add_yo * map->img.w + ipx] != '1')
			map->fpy += sin(map->fpa) * 0.05;
		// printf ("pos %f %f\n", map->fPlayerX, map->fPlayerY);
	}
	if (map->key.s == 1)
	{
		// printf("rev (s)\n");
		if(map->map[ipy * map->img.w + ipx_sub_xo] != '1')
			map->fpx -= cos(map->fpa) * 0.05;
		if(map->map[ipy_sub_yo * map->img.w + ipx] != '1')
			map->fpy -= sin(map->fpa) * 0.05;
	}

	if (cos(map->fpa) < 0)
		yo = -0.2f;
	else
		yo = 0.2f;
	if (sin(map->fpa) < 0)
		xo = -0.2f;
	else
		xo = 0.2f;
	ipx = (int)map->fpx;
	ipx_add_xo = (int)(map->fpx + xo);
	ipx_sub_xo = (int)(map->fpx - xo);
	ipy = (int)map->fpy;
	ipy_add_yo = (int)(map->fpy + yo);
	ipy_sub_yo = (int)(map->fpy - yo);
	// printf("x %d+%d-%d | y %d+%d-%d | p %d-%c\n", ipx, ipx_add_xo, ipx_sub_xo, ipy, ipy_add_yo, ipy_sub_yo, ipy * map->w + ipx_add_xo, map->map[ipy * map->w + ipx_add_xo]);

	if (map->key.a == 1)
	{
		// printf("left (a)\n");
		if(map->map[ipy * map->img.w + ipx_add_xo] != '1')
			map->fpx += sin(map->fpa) * 0.05;
		if(map->map[ipy_sub_yo * map->img.w + ipx] != '1')
			map->fpy -= cos(map->fpa) * 0.05;
	}
	if (map->key.d == 1)
	{
		// printf("right (d)\n");
		if(map->map[ipy * map->img.w + ipx_sub_xo] != '1')
			map->fpx -= sin(map->fpa) * 0.05;
		if(map->map[ipy_add_yo * map->img.w + ipx] != '1')
			map->fpy += cos(map->fpa) * 0.05;
	}
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	draw(map);
	return (0);
}

// int	ft_keydealer(int key, t_data *map)
// {
// 	(void)map;
// 	//printf("%d \n",key);
// 	if (key == 53)
// 		exit(0);
// 	else if (key == 126)
// 	{
// 		printf("up arrow\n");
// 	}
// 	else if (key == 125)
// 	{
// 		printf("down arrow\n");
// 	}
// 	else if (key == 123)
// 	{
// 		// printf("left arrow\n");
// 		map->fPlayerA -= 0.1f;
// 		if (map->fPlayerA <= 0.0f)
// 			map->fPlayerA += 2 * PI;
// 		//printf ("angle %f\n", map->fPlayerA);
// 	}
// 	else if (key == 124)
// 	{
// 		// printf("right arrow\n");
// 		map->fPlayerA += 0.1f;
// 		if (map->fPlayerA > 2 * PI)
// 			map->fPlayerA -= 2 * PI;
// 		//printf ("angle %f\n", map->fPlayerA);
// 	}
// 	else if (key == 13)
// 	{
// 		// printf("front (w)\n");
// 		map->fPlayerX += cos(map->fPlayerA) * 0.05;
// 		map->fPlayerY += sin(map->fPlayerA) * 0.05;
// 		//printf ("pos %f %f\n", map->fPlayerX, map->fPlayerY);
// 	}
// 	else if (key == 1)
// 	{
// 		// printf("rev (s)\n");
// 		map->fPlayerX -= cos(map->fPlayerA) * 0.05;
// 		map->fPlayerY -= sin(map->fPlayerA) * 0.05;
// 	}
// 	else if (key == 0)
// 	{
// 		// printf("left (a)\n");
// 		map->fPlayerX += sin(map->fPlayerA) * 0.05;
// 		map->fPlayerY -= cos(map->fPlayerA) * 0.05;
// 	}
// 	if (key == 2)
// 	{
// 		// printf("right (d)\n");
// 		map->fPlayerX -= sin(map->fPlayerA) * 0.05;
// 		map->fPlayerY += cos(map->fPlayerA) * 0.05;
// 	}
// 	mlx_clear_window(map->mlx_ptr, map->win_ptr);
// 	ft_draw(map);
// 	return (0);
// }

// int	ft_exit_x_button(t_map *map)
// {
// 	mlx_destroy_image(map->mlx_ptr, map->img);
// 	exit(1);
// }

t_point	init_point(int x, int y, int c)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.c = c;
	return (p);
}

t_fpoint	init_fpoint(float x, float y, int c)
{
	t_fpoint	p;

	p.x = x;
	p.y = y;
	p.c = c;
	return (p);
}

t_point	nullify_point(t_point p)
{
	p = init_point(0, 0, create_trgb(0, 0, 0, 0));
	return (p);
}

t_fpoint	nullify_fpoint(t_fpoint p)
{
	p = init_fpoint(0, 0, create_trgb(0, 0, 0, 0));
	return p;
}

// t_point	ft_pshift(t_point p, int x, int y)
// {
// 	p.x += x;
// 	p.y += y;
// 	return (p);
// }

t_fpoint	fpincr(t_fpoint p, t_fpoint dp)
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

t_fpoint	pdelta(t_point p1, t_point p2)
{
	t_fpoint	dfp;
	int			max;
	int			c[4];

	dfp.x = (float)(p2.x - p1.x);
	dfp.y = (float)(p2.y - p1.y);
	c[0] = get_t(p2.c) - get_t(p1.c);
	c[1] = get_r(p2.c) - get_r(p1.c);
	c[2] = get_g(p2.c) - get_g(p1.c);
	c[3] = get_b(p2.c) - get_b(p1.c);
	max = (int)fmaxf(fabsf(dfp.x), fabsf(dfp.y));
	if (max)
	{
		dfp.x /= max;
		dfp.y /= max;
		c[0] /= max;
		c[1] /= max;
		c[2] /= max;
		c[3] /= max;
		dfp.c = create_trgb(c[0], c[1], c[2], c[3]);
	}
	else
		return (nullify_fpoint(dfp));
	return (dfp);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *map, t_point p1, t_point p2)
{
	t_fpoint	dp;
	t_fpoint	p;

	p = init_fpoint((float)p1.x, (float)p1.y, p1.c);
	dp = pdelta(p1, p2);
	while (((int)(p.x - p2.x)) || ((int)(p.y - p2.y)))
	{
		if (p.x >= 0 && p.y >= 0 && p.x < WIN_W && p.y < WIN_H)
			my_mlx_pixel_put(map, (int)p.x, (int)p.y, p.c);
		p = fpincr(p, dp);
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
	while (y < map->img.h)
	{
		while (x < map->img.w)
		{
			if (map->map[y * map->img.w + x] == '1')
				c = WALL_COLOR;
			else
				c = BG_COLOR;
			p[0] = init_point(x * MAP_SIZE, y * MAP_SIZE, c);
			p[1] = init_point(x * MAP_SIZE, (y + 1) * MAP_SIZE - 1, c);
//			p[3] = init_point((x + 1) * MAP_SIZE - 1, (y + 1) * MAP_SIZE - 1, c);
			p[2] = init_point((x + 1) * MAP_SIZE - 1, y * MAP_SIZE, c);
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

int	find_player(t_data *map)
{
	int i = 0;
	int j = 0;

	while (i < map->img.h)
	{
		while (j < map->img.w)
		{
			if (map->map[i * map->img.w + j] == 'S')
			{
				map->fpx = (float)j + 0.5f;
				map->fpy = (float)i + 0.5f;
				map->fpa = 0.0f;
				return (1);
			}
			if (map->map[i * map->img.w + j] == 'E')
			{
				map->fpx = (float)j + 0.5f;
				map->fpy = (float)i + 0.5f;
				map->fpa = 0.0f;
				return (1);
			}
			if (map->map[i * map->img.w + j] == 'N')
			{
				map->fpx = (float)j + 0.5f;
				map->fpy = (float)i + 0.5f;
				map->fpa = 0.0f;
				return (1);
			}
			if (map->map[i * map->img.w + j] == 'W')
			{
				map->fpx = (float)j + 0.5f;
				map->fpy = (float)i + 0.5f;
				map->fpa = 0.0f;
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

	if (!map->fpx)
		printf("no player on map!");
	else
	{
		pos[0] = (int)fmaxf(MAP_SIZE/10.0f, 1.0f);
		i = pos[0];
		j = i;
		pos[1] = (int)(map->fpx * (float)MAP_SIZE);
		pos[2] = (int)(map->fpy * (float)MAP_SIZE);
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
			my_mlx_pixel_put(map, pos[1] + (i/10.0f) * pos[0] * cos(map->fpa), pos[2] + (i/10.0f) * pos[0] * sin(map->fpa), PLAYER_COLOR);
	}
}

void	my_clear_img(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_W)
	{
		j = 0;
		while (j < WIN_H)
		{
			my_mlx_pixel_put(map, i, j, BG_COLOR);
			j++;
		}
		i++;
	}
}

void	draw(t_data *map)
{
	my_clear_img(map);
	my_rays_put(map);
	my_map_put(map);
	my_player_put(map);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img.img, 0, 0);
}

int	handle_no_event(void *map)
{
	/* This function needs to exist, but it is useless for the moment */
	keydealer(map);
	return (0);
}
