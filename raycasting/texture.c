#include "../cub3d.h"

void	load_img(t_data *map, int *texture, char *path)
{
	int	x;
	int	y;

	y = 0;
	map->img.img = mlx_xpm_file_to_image(map->mlx_ptr, path,
			&map->img.w, &map->img.h);
	map->img.data = (int *)mlx_get_data_addr(map->img.img, \
		&map->img.bits_per_pixel, &map->img.size, &map->img->endian);
	while (y < map->img.h)
	{
		x = 0;
		while (x < map->img.w)
		{
			texture[map->img.w * y + x] = map->img.data[map->img.w * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(map->mlx_ptr, map->img.img);
}

void	load_texture(t_data *map)
{
//	load_img(map, map->texture.texture[0], map->texture.north);
//	load_img(map, map->texture.texture[1], map->texture.south);
//	load_img(map, map->texture.texture[2], map->texture.west);
//	load_img(map, map->texture.texture[3], map->texture.east);
	load_img(map, map->texture.texture[0], "./texture/NO2");
	load_img(map, map->texture.texture[1], "./texture/SO2");
	load_img(map, map->texture.texture[2], "./texture/WE2");
	load_img(map, map->texture.texture[3], "./texture/EA2");
}

void	image_draw(t_data *map) // ВОПРОС?????
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			map->img.data[y * WIN_W + x] = map->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img.img, 0, 0);
}

void	ceiling_floor(t_data *map)
{
	int	x;
	int	y;
	int	color_c;
	int	color_f;

	x = 0;
	color_c = create_trgb(map->texture.ceiling[0],
			map->texture.ceiling[1], map->texture.ceiling[2],
			map->texture.ceiling[3]);
	color_f = create_trgb(map->texture.floor[0],
			map->texture.floor[1], map->texture.floor[2],
			map->texture.floor[3]);
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			map->buf[y][x] = color_c;
			map->buf[WIN_H - y - 1][x] = color_f;
			y++;
		}
		x++;
	}
}

int	init_texture(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	map->texture.texture = (int **)malloc(sizeof(int *) * 4);
	if (map->texture.texture == NULL)
		return (-1);
	while (i < 4)
	{
		map->texture.texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W));
		if (map->texture.texture[i] == NULL)
			return (-1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < TEX_H * TEX_W)
			map->texture.texture[i][j++] = 0;
		i++;
	}
	return (0);
}
