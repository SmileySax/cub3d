#include "../cub3d.h"

float distance(t_fpoint p1, t_fpoint p2)
{
	float	a;
	float	b;

	a = fabs(p2.x - p1.x);
	b = fabs(p2.y - p1.y);
	// printf("a %f | b %f | ", a, b);
	return (sqrt(a * a + b * b));
}

void	my_rays_put(t_data *map)
{
	int	r;
	int	mp, i, col;
	float	 fray_a, fline_h, fLine_o, a_tan, n_tan, dis_h, dis_v, dist;
	t_point	player, ray;
	t_fpoint	fray, vert, hor, offset;
	t_point		mappoint;

	fray_a = map->fpa - VIEW_ANGLE/2 * DEG;
	if (fray_a < 0)
		fray_a += 2 * PI;
	if (fray_a > 2 * PI)
		fray_a -= 2 * PI;
	r = 0;
	while (r < VIEW_ANGLE * RESOLUTION)
	{
		i = 0;//check horizontal lines
		dis_h = 1000000;
		hor.x = map->fpx * MAP_SIZE;
		hor.y = map->fpy * MAP_SIZE;
		a_tan = -1 / tan(fray_a);
		if (fray_a == 0 || fray_a == PI)
		{
			fray.x = (map->fpx + map->img.w);
			fray.y = map->fpy;
			i = map->img.w;
		}
		else if (fray_a > PI)
		{
			fray.y = ((int)map->fpy - 0.000001);
			fray.x = (map->fpy - fray.y) * a_tan + map->fpx;
			offset.y = -1;
			offset.x = -offset.y * a_tan;
		}
		else if (fray_a < PI)
		{
			fray.y = ((int)map->fpy + 1.0f);
			fray.x = (map->fpy - fray.y) * a_tan + map->fpx;
			offset.y = 1;
			offset.x = -offset.y * a_tan;
		}
		while (i < map->img.w)
		{
			mappoint.x = (int)fray.x;
			mappoint.y = (int)fray.y;
			mp = mappoint.y * map->img.w + mappoint.x;
			if (mp >= 0 && mp < map->img.w * map->img.h && (map->map)[mp] == '1')
			{
				i = map->img.w;
				hor.x = fray.x * MAP_SIZE;
				hor.y = fray.y * MAP_SIZE;
				dis_h = distance(init_fpoint(map->fpx, map->fpy, 0),
						init_fpoint(fray.x, fray.y, 0));
				// printf("mx %i | my %i | a %f | disH %f | ", mappoint.x, mappoint.y, fRayA, disH);
			}
			else
			{
				fray.x += offset.x;
				fray.y += offset.y;
				i++;
			}
		}

		i = 0; //check vertical lines
		dis_v = 1000000;
		vert.x = map->fpx * MAP_SIZE;
		vert.y = map->fpy * MAP_SIZE;
		n_tan = -tan(fray_a);
		if (fray_a == PI2 || fray_a == PI3)
		{
			fray.y = (map->fpy + map->img.w);
			fray.x = map->fpx;
			i = map->img.w;
		}
		else if (fray_a > PI2 && fray_a < PI3)
		{
			fray.x = ((int)map->fpx - 0.000001);
			fray.y = (map->fpx - fray.x) * n_tan + map->fpy;
			offset.x = -1;
			offset.y = -offset.x * n_tan;
		}
		else if (fray_a < PI2 || fray_a > PI3)
		{
			fray.x = ((int)map->fpx + 1);
			fray.y = (map->fpx - fray.x) * n_tan + map->fpy;
			offset.x = 1;
			offset.y = -offset.x * n_tan;
		}
		while (i < map->img.w)
		{
			mappoint.x = (int)fray.x;
			mappoint.y = (int)fray.y;
			mp = mappoint.y * map->img.w + mappoint.x;
			if (mp >= 0 && mp < map->img.w * map->img.h && (map->map)[mp] == '1')
			{
				i = map->img.w;
				vert.x = fray.x * MAP_SIZE;
				vert.y = fray.y * MAP_SIZE;
				dis_v = distance(init_fpoint(map->fpx, map->fpy, 0),
						init_fpoint(fray.x, fray.y, 0));
				// printf("mx %i | my %i | a %f | disV %f | ", mappoint.x, mappoint.y, fRayA, disV);
			}
			else
			{
				fray.x += offset.x;
				fray.y += offset.y;
				i++;
			}
		}
		if (dis_h > dis_v)
		{
			if (fray_a > PI2 && fray_a < PI3)
				col = RAY_COLOR1;
			else
				col = RAY_COLOR3;
			ray = init_point((int)vert.x, (int)vert.y, col);
			dist = dis_v;
			player = init_point((int)(map->fpx * MAP_SIZE), (int)(map->fpy * MAP_SIZE), col);
			// printf("minV %f\n", disV);
		}
		else
		{
			if (fray_a > PI)
				col = RAY_COLOR2;
			else
				col = RAY_COLOR4;
			ray = init_point((int)hor.x, (int)hor.y, col);
			dist = dis_h;
			player = init_point((int)(map->fpx * MAP_SIZE), (int)(map->fpy * MAP_SIZE), col);
			// printf("minH %f\n", disH);
		}
		my_mlx_line_put(map, player, ray);

		float ca = map->fpa - fray_a;
		if (ca <= 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		dist = dist * cos(ca);
		fline_h = (map->img.w * WIN_H) / (dist * 8);
		if (fline_h > WIN_H)
			fline_h = WIN_H;
		fLine_o = WIN_H/2.0f - fline_h/2.0f;
		// printf("dist %f, H %f, O %f \n", dist, fLineH, fLineO);
		i = 0;
		while (i < WALL_LINE_WID)
		{
			t_point a = init_point(r * WALL_LINE_WID + i, (int)fLine_o, col);
			t_point b = init_point(r * WALL_LINE_WID + i, (int)(fline_h + fLine_o), col);
			my_mlx_line_put(map, a, b);
			i++;
		}
		r++;
		fray_a += DEG / RESOLUTION;
		if (fray_a <= 0)
			fray_a += 2 * PI;
		if (fray_a > 2 * PI)
			fray_a -= 2 * PI;
	}
}
