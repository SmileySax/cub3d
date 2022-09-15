#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "mlx/mlx.h"

#define WIN_W 1000
#define WIN_H 800

#define VIEW_ANGLE 60
#define RESOLUTION 10
#define WALL_LINE_WID 20/RESOLUTION

#define MAP_SIZE 25
#define PLAYER_COLOR 0x0000FF00
#define RAY_COLOR1 0x0066FF66
#define RAY_COLOR2 0x00661166
#define RAY_COLOR3 0x7766FF66
#define RAY_COLOR4 0x77661166
#define WALL_COLOR 0x00FFFFFF
#define BG_COLOR 0x00000000
#define MINIMAP_X 0
#define MINIMAP_Y 0
#define PI 3.14159
#define PI2 PI/2
#define PI3 3*PI/2
#define DEG 0.0174533


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

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	la;
	int	ra;
}	t_keys;

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
	t_keys	key;
}				t_data;

void	ft_draw(t_data *img);
t_fpoint	ft_init_fpoint(float x, float y, int c);
t_point	ft_init_point(int x, int y, int c);
void	my_mlx_line_put(t_data *map, t_point p1, t_point p2);
void	my_rays_put(t_data *map);

#endif
