#include "../cub3d.h"

/*	This function returns the hexadecimal representation of either the	*/
/*	floor or ceiling color. These operations are used to create a		*/
/*	single integer that represents an RGB color in hexadecimal format.	*/
int	rgb_hex(t_game *game, int j)
{
	if (j == 1)
		return (0 << 24 | (int)game->rgb.floor_r << 16
			| (int)game->rgb.floor_g << 8 | (int)game->rgb.floor_b);
	else
		return (0 << 24 | (int)game->rgb.ceil_r << 16
			| (int)game->rgb.ceil_g << 8 | (int)game->rgb.ceil_b);
	return (0);
}

/*	This function is responsible for drawing the background of the game	*/
/*	window. It fills the top half of the window with a color and the	*/
/*	bottom half with another color.										*/
void	draw_bg(t_game *data)
{
	int	col;
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			col = rgb_hex(data, 2);
		else
			col = rgb_hex(data, 1);
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, col);
			x++;
		}
		x = 0;
		y++;
	}
}

/*	This function initializes the textures for the walls and retrieves	*/
/*	their pixel data for the rendering process.							*/
void	init_3d(t_game *game)
{
	game->txtr.ea = mlx_xpm_file_to_image(game->mlx, game->parsing.eatxt,
			&game->txtr.img_w, &game->txtr.img_h);
	game->txtr.no = mlx_xpm_file_to_image(game->mlx, game->parsing.notxt,
			&game->txtr.img_w, &game->txtr.img_h);
	game->txtr.we = mlx_xpm_file_to_image(game->mlx, game->parsing.wetxt,
			&game->txtr.img_w, &game->txtr.img_h);
	game->txtr.so = mlx_xpm_file_to_image(game->mlx, game->parsing.sotxt,
			&game->txtr.img_w, &game->txtr.img_h);
	game->txtr.a_ea = (int *)mlx_get_data_addr(game->txtr.ea,
			&game->txtr.bpp_2, &game->txtr.len, &game->txtr.end);
	game->txtr.a_no = (int *)mlx_get_data_addr(game->txtr.no,
			&game->txtr.bpp_2, &game->txtr.len, &game->txtr.end);
	game->txtr.a_we = (int *)mlx_get_data_addr(game->txtr.we,
			&game->txtr.bpp_2, &game->txtr.len, &game->txtr.end);
	game->txtr.a_so = (int *)mlx_get_data_addr(game->txtr.so,
			&game->txtr.bpp_2, &game->txtr.len, &game->txtr.end);
}

/*	This function takes care of initializing the textures, raycasting and	*/
/*	then displaying the final images to the window using the MLX.			*/
int	draw_loop(t_game *game)
{
	init_3d(game);
	rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

/*	Thanks to this function, we are able to display a pixel at a given		*/
/*	position (x,y) and with a given color.									*/
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.line_size + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}
