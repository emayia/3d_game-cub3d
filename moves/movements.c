#include "../cub3d.h"

/*	This function is handling the forward movement of the player. We first	*/
/*	determine the value of len, which represents the greatest distance the	*/
/*	player needs to cover either on the x or y axis. We do that by setting	*/
/*	len to the absolute value of the larger difference between the			*/
/*	x-coordinates (game->fin_x - game->plr.x) or the y-coordinates			*/
/*	(game->fin_y - game->plr.y).											*/
/*	We then use that len value to calculate d_x and d_y variables. These	*/
/*	variables represent the increments in the x and y directions for each	*/
/*	step. We get these increments by dividing the difference in x and y		*/
/*	coordinates by len. This effectively scales down the larger difference	*/
/*	to a unit step, which ensures a uniform speed of movement in each step.	*/
/*	We then assign the new x and y coordinates to the i and j variables.	*/
/*	Before actually moving, we check if the calculated coordinates would	*/
/*	make the player overshoot their destination (the distance from current	*/
/*	position to the new position is compared with game->distance). If it	*/
/*	overshoots, we adjust the step to land just a bit behind destination.	*/
/*	Then we update the map by checking if the player lands on a new tile,	*/
/*	if he does, we mark the old tile as empty ('0') and set the new one to	*/
/*	player. Finaly, we update the player's position and redraw the game.	*/
void	forward(t_game *game)
{
	if (fabs(game->fin_x - game->plr.x) >= fabs(game->fin_y - game->plr.y))
		game->moves.len = (fabs(game->plr.x - game->fin_x));
	else
		game->moves.len = (fabs(game->plr.y - game->fin_y));
	game->moves.d_x = (game->fin_x - game->plr.x) / game->moves.len;
	game->moves.d_y = (game->fin_y - game->plr.y) / game->moves.len;
	game->moves.i = game->plr.x + (game->moves.d_x * STEP);
	game->moves.j = game->plr.y + (game->moves.d_y * STEP);
	if (game->distance <= (sqrt((pow(game->plr.x - game->moves.i, 2)
					+ pow(game->plr.y - game->moves.j, 2)))))
	{
		game->moves.i = game->fin_x - game->moves.d_x / 6;
		game->moves.j = game->fin_y - game->moves.d_y / 6;
	}
	if (game->plr.x / TILE != game->moves.i / TILE
		|| game->plr.y / TILE != game->moves.j / TILE)
	{
		game->map[(int)game->plr.y / TILE][(int)game->plr.x / TILE] = '0';
		game->map[(int)game->moves.j / TILE][(int)game->moves.i
			/ TILE] = game->player;
	}
	game->plr.x = game->moves.i;
	game->plr.y = game->moves.j;
	draw_loop(game);
}

/*	This function works in a similar way to the forward function. We first	*/
/*	calculate the len value, then calculate the d_x and d_y increments.		*/
/*	After that, we set the new x and y coordinates to i and j.				*/
/*	Contrary to the forward() function, here, we substract the d_x and d_y	*/
/*	increments to the player's position, effectively moving them backwards.	*/
/*	Once that's done, we check if the new position is a wall or not and		*/
/*	update the current tile and then assign the new i,j coordinates to the	*/
/*	player. Finally, we redraw the game.									*/
void	backward(t_game *game)
{
	if (fabs(game->fin_x - game->plr.x) >= fabs(game->fin_y - game->plr.y))
		game->moves.len = (fabs(game->plr.x - game->fin_x));
	else
		game->moves.len = (fabs(game->plr.y - game->fin_y));
	game->moves.d_x = (game->fin_x - game->plr.x) / game->moves.len;
	game->moves.d_y = (game->fin_y - game->plr.y) / game->moves.len;
	game->moves.i = game->plr.x - (game->moves.d_x * STEP);
	game->moves.j = game->plr.y - (game->moves.d_y * STEP);
	if (game->map[(int)game->moves.j / TILE][(int)game->moves.i / TILE] != '1')
	{
		if (game->plr.x / TILE != game->moves.i / TILE
			|| game->plr.y / TILE != game->moves.j / TILE)
		{
			game->map[(int)game->plr.y / TILE][(int)game->plr.x / TILE] = '0';
			game->map[(int)game->moves.j / TILE][(int)game->moves.i
				/ TILE] = game->player;
		}
		game->plr.x = game->moves.i;
		game->plr.y = game->moves.j;
	}
	draw_loop(game);
}

/*	Same method as the other movement functions. We first calculate the len	*/
/*	and then we get the d_x and d_y increments. The difference though is	*/
/*	that contrary to forward() and backward(), here we compute d_x and d_y	*/
/*	in a way that sets the trajectory of the player on a perpendicular line	*/
/*	to the middle ray going from the player's position.						*/
/*	Once that's done, we check if the new position is a wall or not and		*/
/*	update the current tile and then assign the new i,j coordinates to the	*/
/*	player. Finally, we redraw the game.									*/
void	left(t_game *game)
{
	if (fabs(game->fin_x - game->plr.x) >= fabs(game->fin_y - game->plr.y))
		game->moves.len = (fabs(game->plr.x - game->fin_x));
	else
		game->moves.len = (fabs(game->plr.y - game->fin_y));
	game->moves.d_x = (game->fin_y - game->plr.y) / game->moves.len;
	game->moves.d_y = (game->plr.x - game->fin_x) / game->moves.len;
	game->moves.i = game->plr.x + (game->moves.d_x * STEP);
	game->moves.j = game->plr.y + (game->moves.d_y * STEP);
	if (game->map[(int)game->moves.j / TILE][(int)game->moves.i / TILE] == '1')
		return ;
	if (game->plr.x / TILE != game->moves.i / TILE
		|| game->plr.y / TILE != game->moves.j / TILE)
	{
		game->map[(int)game->plr.y / TILE][(int)game->plr.x / TILE] = '0';
		game->map[(int)game->moves.j / TILE][(int)game->moves.i
			/ TILE] = game->player;
	}
	game->plr.x = game->moves.i;
	game->plr.y = game->moves.j;
	draw_loop(game);
}

/*	Same method as the left movement. We first calculate the len and then	*/
/*	we get the d_x and d_y increments. We compute d_x and d_y in a way that	*/
/*	sets the trajectory of the player on a perpendicular line to the middle	*/
/*	ray going from the player's position.									*/
/*	Once that's done, we check if the new position is a wall or not and		*/
/*	update the current tile and then assign the new i,j coordinates to the	*/
/*	player. Finally, we redraw the game.									*/
void	right(t_game *game)
{
	if (fabs(game->fin_x - game->plr.x) >= fabs(game->fin_y - game->plr.y))
		game->moves.len = (fabs(game->plr.x - game->fin_x));
	else
		game->moves.len = (fabs(game->plr.y - game->fin_y));
	game->moves.d_x = (game->plr.y - game->fin_y) / game->moves.len;
	game->moves.d_y = (game->fin_x - game->plr.x) / game->moves.len;
	game->moves.i = game->plr.x + (game->moves.d_x * STEP);
	game->moves.j = game->plr.y + (game->moves.d_y * STEP);
	if (game->map[(int)game->moves.j / TILE][(int)game->moves.i / TILE] == '1')
		return ;
	if (game->plr.x / TILE != game->moves.i / TILE
		|| game->plr.y / TILE != game->moves.j / TILE)
	{
		game->map[(int)game->plr.y / TILE][(int)game->plr.x / TILE] = '0';
		game->map[(int)game->moves.j / TILE][(int)game->moves.i
			/ TILE] = game->player;
	}
	game->plr.x = game->moves.i;
	game->plr.y = game->moves.j;
	draw_loop(game);
}
