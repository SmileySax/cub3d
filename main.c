#include <math.h>
#include "mlx.h"

int	main(void)
{
	float	fPlayerX;
	float	fPlayerY;
	float	fPlayerAngle;
	int		nMapWid = 6;
	int		nMapHeigh = 6;
	int		nScreenWid = 120;
	float	fFOV;
	int		x;
	int		a0[6] = (1, 1, 1, 1, 1, 1);
	int		a1[6] = (1, 0, 1, 0, 0, 1);
	int		a2[6] = (1, 0, 1, 0, 1, 1);
	int		a3[6] = (1, 0, 0, 0, 0, 1);
	int		a4[6] = (1, 0, 0, 0, 0, 1);
	int		a5[6] = (1, 1, 1, 1, 1, 1);
	int		*a[6] = (a0, a1, a2, a3, a4, a5);
	float	fRayAngle;
	float	fDistToWall;

	fPlayerX = 0.0f;
	fPlayerY = 0.0f;
	fPlayerAngle = 0.0f;
	fFOV = 3.14159 / 4.0f;

	x = 0;
	while (1)
	{
		while (x < nScreenWid)
		{
			fRayAngle = (fPlayerAngle - fFOV / 2.0f) + ((float)x / (float)nScreenWid) * fFOV;
			fDistToWall = 0;

		}
	}
}
