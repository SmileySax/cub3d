#include "cub3d.h"

int	main(int ac, char **av)
{
	char	*m = "111111101001101011100001100X01111111";
	// 			(1, 1, 1, 1, 1, 1,
	// 			1, 0, 1, 0, 0, 1,
	// 			1, 0, 1, 0, 1, 1,
	// 			1, 0, 0, 0, 0, 1,
	// 			1, 0, 0, X, 0, 1,
	// 			1, 1, 1, 1, 1, 1);
	t_data	map;

	map.map = m;
	map.img.h = 6;
	map.img.w = 6;
	map.key.la = 0;
	map.key.ra = 0;
	map.key.w = 0;
	map.key.s = 0;
	map.key.a = 0;
	map.key.d = 0;
	(void) av;
	if (ac != 1)
		print_error("Probably the number of arguments\n", NULL, NULL, NULL);
//	parser(&map, av[1]);
	terminal_map(m);
	map.mlx_ptr = mlx_init();
	map.win_ptr = mlx_new_window(map.mlx_ptr, WIN_W, WIN_H, "cub3d");
	map.img.img = mlx_new_image(map.mlx_ptr, WIN_W, WIN_H);
	map.addr = mlx_get_data_addr(map.img.img, &map.img.bits_per_pixel, &map.line_length,
								 &map.img.endian);
	if(!find_player(&map))
		printf("no player on map!");
	draw(&map);
	mlx_loop_hook(map.mlx_ptr, &handle_no_event, (void *)&map);
	mlx_hook(map.win_ptr, 2, 1L << 0, &keydown, (void *)&map);
	mlx_hook(map.win_ptr, 3, 1L << 1, &keyup, (void *)&map);
	// mlx_hook(mlx_win, 17, 0, ft_exit_x_button, map);
	mlx_loop(map.mlx_ptr);
	return 0;
}
