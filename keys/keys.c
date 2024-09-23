#include "../cub3d.h"

/*	This function assigns the game's controls (WASD, Left, Right, ESC) to	*/
/*	their matching functions.												*/
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == R_L)
		rotate_l(game);
	else if (keycode == R_R)
		rotate_r(game);
	else if (keycode == W)
		forward (game);
	else if (keycode == A)
		left(game);
	else if (keycode == S)
		backward(game);
	else if (keycode == D)
		right(game);
	return (0);
}
