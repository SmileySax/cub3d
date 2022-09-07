#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "mlx/mlx.h"

#define WIN_W 1000
#define WIN_H 1000

#define MAP_SIZE 100
#define PLAYER_COLOR 0x0000FF00
#define WALL_COLOR 0x00FFFFFF
#define BG_COLOR 0x00000000
#define MINIMAP_X 0
#define MINIMAP_Y 0
#define PI 3.14159

typedef struct s_point
{
	int	x;
	int	y;
	int	c;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
	int		c;
}	t_fpoint;

typedef struct	s_data {
	void	*img;
	char	*addr;
	char	*mlx_ptr;
	char	*win_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*map;
	float	fPlayerX;
	float	fPlayerY;
	float	fPlayerA;
	int		h;
	int		w;
}				t_data;

void	ft_draw(t_data *img);

#endif
