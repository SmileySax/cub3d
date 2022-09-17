#include "cub3d.h"

void	load_img(t_cub *cub, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(cub->mlx, path, &img->w, &img->h);
	img->data = (int *)mlx_get_data_addr(img->img, \
		&img->bpp, &img->size, &img->endian);
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			texture[img->w * y + x] = img->data[img->w * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(cub->mlx, img->img);
}

void	load_texture(t_cub *cub)
{
	t_img	img;

	load_img(cub, cub->texture[0], cub->textur.north, &img);
	load_img(cub, cub->texture[1], cub->textur.south, &img);
	load_img(cub, cub->texture[2], cub->textur.west, &img);
	load_img(cub, cub->texture[3], cub->textur.east, &img);
}

void	image_draw(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < SHEIGHT)
	{
		x = 0;
		while (x < SWIGHT)
		{
			cub->img.data[y * SWIGHT + x] = cub->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	potolok(t_cub *cub)
{
	int	x;
	int	y;
	int	color;
	int	color2;

	x = 0;
	color = ft_hex(cub->textur.color_ceiling[0], \
		cub->textur.color_ceiling[1], cub->textur.color_ceiling[2]);
	color2 = ft_hex(cub->textur.color_floor[0], \
		cub->textur.color_floor[2], cub->textur.color_floor[2]);
	while (x < SWIGHT)
	{
		y = 0;
		while (y < SHEIGHT)
		{
			cub->buf[y][x] = color;
			cub->buf[SHEIGHT - y - 1][x] = color2;
			y++;
		}
		x++;
	}
}

int	init_texture(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	cub->texture = (int **)malloc(sizeof(int *) * 4);
	if (cub->texture == NULL)
		return (-1);
	while (i < 4)
	{
		cub->texture[i] = (int *)malloc(sizeof(int) * (TEXH * TEXW));
		if (cub->texture[i] == NULL)
			return (-1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < TEXH * TEXW)
			cub->texture[i][j++] = 0;
		i++;
	}
	return (0);
}