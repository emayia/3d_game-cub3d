#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (checkparsing(argv, argc, game) == 1)
		return (1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_size, &game->img.endian);
	draw_loop(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_hook(game->win, KEY_EVENT_PRESS, 0, key_press, game);
	mlx_hook(game->win, KEY_EVENT_EXIT, 0, exit_button, game);
	mlx_loop(game->mlx);
	free(game->parsing.eatxt);
	free(game->parsing.wetxt);
	free(game->parsing.notxt);
	free(game->parsing.sotxt);
	free_map(game);
	return (0);
}
