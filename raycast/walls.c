#include "../cub3d.h"

/*	This is a simple check used by the check_wall functions. We verify if	*/
/*	the current tile is set to a cardinal point or not.						*/
int	is_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/*	This function handles the rendering of the textured wall to the screen.	*/
/*	We first get the top and bottom y-coordinates of the wall on the screen.*/
/*	Then we loop from the top of the wall to the bottom, drawing each pixel.*/
/*	For each pixel, we calculate the corresponding y-coordinate within the	*/
/*	texture. Its color is found from the texture, using the txtr_x and		*/
/*	txtr_y coordinates. The texture is stored as a 1D array, so the x and y	*/
/*	coordinates are converted using the following formula:					*/
/*	x + y * width															*/
/*	Then we draw the pixel to the screen at the mirrored x-coordinate		*/
/*	(WIDTH - i - 1) and the current y-coordinate (wall_top). We repeat this	*/
/*	process from the top of the wall to the bottom, effectively drawing a	*/
/*	textured vertical line representing a wall on the screen.				*/
void	wall2(t_game *game, t_ray *ray, int i)
{
	int		wall_top;
	int		wall_bottom;
	int		color;
	int		mirrored_x;
	double	idx;

	wall_top = HEIGHT / 2 - (ray->height / 2);
	wall_bottom = HEIGHT / 2 + ray->height / 2;
	if (wall_top < 0)
		wall_top = 0;
	while (wall_top < wall_bottom && wall_top < HEIGHT)
	{
		game->txtr.txt_y = (1.0 - (double)(wall_bottom - wall_top)
				/ ray->height) * 64.0;
		idx = (double)game->txtr.txt_x
			+ (double)game->txtr.txt_y * (double)64;
		color = game->txtr.a_fnl[(int)idx];
		mirrored_x = WIDTH - i - 1;
		my_mlx_pixel_put(game, mirrored_x, wall_top, color);
		wall_top++;
	}
}

/*	In order to determine which texture to use for a given wall, we use		*/
/*	this function. To do that we follow these steps:						*/
/*	First we check if the ray hits a horizontal wall, there, we check if it	*/
/*	hits a North or South wall (game->txtr.a_no, game->txtr.a_so) and pick	*/
/*	the right texture to display.											*/
/*	If the ray hits a vertical wall, we check if it hits an East or West	*/
/*	wall (game->txtr.a_ea, game->txtr.a_we) and pick the right texture to	*/
/*	display. Then we get the texture's x-coordinate by calculating the		*/
/*	fractional part of (ray->fin_x / 64.0) or (ray->fin_y / 64.0), depending*/
/*	on whether the wall is horizontal or vertical, then we scale this		*/
/*	fraction up to texture size (64*64px). This gives us the x-coordinate	*/
/*	of the part of the texture hit by the ray.								*/
/*	After that, we follow up with wall2() to render the wall on the screen.	*/
void	wall(t_game *game, t_ray *ray, double angle, int i)
{
	if (!(ray->vertical))
	{
		if (angle < M_PI && angle > 0)
			game->txtr.a_fnl = (int *)game->txtr.a_no;
		else
			game->txtr.a_fnl = (int *)game->txtr.a_so;
		game->txtr.txt_x = fmod(ray->fin_x / 64.0, 1.0) * 64.0;
	}
	else if (ray->vertical)
	{
		if ((angle > 0 && angle < M_PI / 2) || (angle < 2 * M_PI
				&& angle > 3 * (M_PI / 2)))
			game->txtr.a_fnl = (int *)game->txtr.a_ea;
		else
			game->txtr.a_fnl = (int *)game->txtr.a_we;
		game->txtr.txt_x = fmod(ray->fin_y / 64.0, 1.0) * 64.0;
	}
	wall2(game, ray, i);
}
