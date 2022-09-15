#include "cub3d.h"

float ft_dist(t_fpoint p1, t_fpoint p2)
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
	float	 fRayA, fLineH, fLineO, aTan, nTan, disH, disV, dist;
	t_point	player, ray;
	t_fpoint	fRay, vert, hor, offset;
	t_point		mappoint;

	fRayA = map->fPlayerA - VIEW_ANGLE/2 * DEG;
	if (fRayA < 0)
		fRayA += 2 * PI;
	if (fRayA > 2 * PI)
		fRayA -= 2 * PI;
	r = 0;
	while (r < VIEW_ANGLE * RESOLUTION)
	{
		i = 0;//check horizontal lines
		disH = 1000000;
		hor.x = map->fPlayerX * MAP_SIZE;
		hor.y = map->fPlayerY * MAP_SIZE;
		aTan = -1 / tan(fRayA);
		if (fRayA == 0 || fRayA == PI)
		{
			fRay.x = (map->fPlayerX + map->w);
			fRay.y = map->fPlayerY;
			i = map->w;
		}
		else if (fRayA > PI)
		{
			fRay.y = ((int)map->fPlayerY - 0.000001);
			fRay.x = (map->fPlayerY - fRay.y) * aTan + map->fPlayerX;
			offset.y = -1;
			offset.x = -offset.y * aTan;
		}
		else if (fRayA < PI)
		{
			fRay.y = ((int)map->fPlayerY + 1.0f);
			fRay.x = (map->fPlayerY - fRay.y) * aTan + map->fPlayerX;
			offset.y = 1;
			offset.x = -offset.y * aTan;
		}
		while (i < map->w)
		{
			mappoint.x = (int)fRay.x;
			mappoint.y = (int)fRay.y;
			mp = mappoint.y * map->w + mappoint.x;
			if (mp >= 0 && mp < map->w * map->h && (map->map)[mp] == '1')
			{
				i = map->w;
				hor.x = fRay.x * MAP_SIZE;
				hor.y = fRay.y * MAP_SIZE;
				disH = ft_dist(ft_init_fpoint(map->fPlayerX, map->fPlayerY, 0), ft_init_fpoint(fRay.x, fRay.y, 0));
				// printf("mx %i | my %i | a %f | disH %f | ", mappoint.x, mappoint.y, fRayA, disH);
			}
			else
			{
				fRay.x += offset.x;
				fRay.y += offset.y;
				i++;
			}
		}

		i = 0; //check vertical lines
		disV = 1000000;
		vert.x = map->fPlayerX * MAP_SIZE;
		vert.y = map->fPlayerY * MAP_SIZE;
		nTan = -tan(fRayA);
		if (fRayA == PI2 || fRayA == PI3)
		{
			fRay.y = (map->fPlayerY + map->w);
			fRay.x = map->fPlayerX;
			i = map->w;
		}
		else if (fRayA > PI2 && fRayA < PI3)
		{
			fRay.x = ((int)map->fPlayerX - 0.000001);
			fRay.y = (map->fPlayerX - fRay.x) * nTan + map->fPlayerY;
			offset.x = -1;
			offset.y = -offset.x * nTan;
		}
		else if (fRayA < PI2 || fRayA > PI3)
		{
			fRay.x = ((int)map->fPlayerX + 1);
			fRay.y = (map->fPlayerX - fRay.x) * nTan + map->fPlayerY;
			offset.x = 1;
			offset.y = -offset.x * nTan;
		}
		while (i < map->w)
		{
			mappoint.x = (int)fRay.x;
			mappoint.y = (int)fRay.y;
			mp = mappoint.y * map->w + mappoint.x;
			if (mp >= 0 && mp < map->w * map->h && (map->map)[mp] == '1')
			{
				i = map->w;
				vert.x = fRay.x * MAP_SIZE;
				vert.y = fRay.y * MAP_SIZE;
				disV = ft_dist(ft_init_fpoint(map->fPlayerX, map->fPlayerY, 0), ft_init_fpoint(fRay.x, fRay.y, 0));
				// printf("mx %i | my %i | a %f | disV %f | ", mappoint.x, mappoint.y, fRayA, disV);
			}
			else
			{
				fRay.x += offset.x;
				fRay.y += offset.y;
				i++;
			}
		}
		if (disH > disV)
		{
			if (fRayA > PI2 && fRayA < PI3)
				col = RAY_COLOR1;
			else
				col = RAY_COLOR3;
			ray = ft_init_point((int)vert.x, (int)vert.y, col);
			dist = disV;
			player = ft_init_point((int)(map->fPlayerX * MAP_SIZE), (int)(map->fPlayerY * MAP_SIZE), col);
			// printf("minV %f\n", disV);
		}
		else
		{
			if (fRayA > PI)
				col = RAY_COLOR2;
			else
				col = RAY_COLOR4;
			ray = ft_init_point((int)hor.x, (int)hor.y, col);
			dist = disH;
			player = ft_init_point((int)(map->fPlayerX * MAP_SIZE), (int)(map->fPlayerY * MAP_SIZE), col);
			// printf("minH %f\n", disH);
		}
		my_mlx_line_put(map, player, ray);

		float ca = map->fPlayerA - fRayA;
		if (ca <= 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		dist = dist * cos(ca);
		fLineH = (map->w * WIN_H) / (dist * 8);
		if (fLineH > WIN_H)
			fLineH = WIN_H;
		fLineO = WIN_H/2.0f - fLineH/2.0f;
		// printf("dist %f, H %f, O %f \n", dist, fLineH, fLineO);
		i = 0;
		while (i < WALL_LINE_WID)
		{
			t_point a = ft_init_point(r * WALL_LINE_WID + i, (int)fLineO, col);
			t_point b = ft_init_point(r * WALL_LINE_WID + i, (int)(fLineH + fLineO), col);
			my_mlx_line_put(map, a, b);
			i++;
		}
		r++;
		fRayA += DEG / RESOLUTION;
		if (fRayA <= 0)
			fRayA += 2 * PI;
		if (fRayA > 2 * PI)
			fRayA -= 2 * PI;
	}
}
