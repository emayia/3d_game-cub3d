#include "../cub3d.h"

/*	This function updates the current angle of the player while keeping it	*/
/*	in the [0, 2π] range. This allows the player's angle to always stay in	*/
/*	a valid range, independent of how many times we rotate left or right.	*/
/*	To do that, we first calculate the new angle by adding the start and	*/
/*	delta angles together, then taking the remainder of the result with 2π.	*/
/*	The result of this operation is an angle in the [-2π, 2π] range.		*/
/*	That's why the if condition is in place, so that if the result is < 0,	*/
/*	we add 2π to it so that it moves to the equivalent positive angle and	*/
/*	we remain in the correct [0, 2π] range.									*/
double	add_angle(double start_agl, double delta_agl)
{
	double	res;

	res = fmod(start_agl + delta_agl, 2 * M_PI);
	if (res < 0)
		res += 2 * M_PI;
	return (res);
}

/*	This function makes the player's angle decrease by x degrees (-π/y)		*/
/*	which in effect produces a right rotation. If the player's angle drops	*/
/*	below 0, the add_angle() function will correct it to the equivalent		*/
/*	positive angle.															*/
void	rotate_r(t_game *game)
{
	game->plr.agl = add_angle(game->plr.agl, (-M_PI / 36));
	draw_loop(game);
}

/*	This function makes the player's angle increase by x degrees (+π/y)		*/
/*	which produces a left rotation. If the player's angle exceeds 2π, the	*/
/*	add_angle() function will correct it to the equivalent angle in the		*/
/*	[0,2π] range.															*/
void	rotate_l(t_game *game)
{
	game->plr.agl = add_angle(game->plr.agl, (+M_PI / 36));
	draw_loop(game);
}
