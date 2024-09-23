#include "../cub3d.h"

/*	This function removes the fish-eye effect. To do that, we adjust the	*/
/*	distance by multiplying the cosine of the difference between the		*/
/*	player's angle and the ray's angle.										*/
void	remove_fish_eye(t_game *game, t_ray *ray, double angle)
{
	ray->distance = ray->distance * (cos(game->plr.agl - angle));
}

/*	With this function we calculate the projection plane distance, which is	*/
/*	used to scale objects in the game world. This is based on the width of	*/
/*	the screen and the field of view.										*/
/*	Finally, we calculate the height of the wall on the screen. This is the	*/
/*	height that will be used when rendering the wall. The calculation uses	*/
/*	the tile size, the corrected distance to the wall (ray->distance) and	*/
/*	the projection plane distance (ray->plane).								*/
void	get_wall_height(t_ray *ray)
{
	ray->plane = (WIDTH / 2) / tan(FOV / 2);
	ray->height = abs((int)(TILE / ray->distance * ray->plane));
}

/*	This function does mutiple things. First, we calculate the player's		*/
/*	position to the first horizontal hit point (ray->ax, ray->ay) and the	*/
/*	first vertical hit point (ray->bx, ray->by). These a and b distances	*/
/*	are calculated using the Euclidian distance formula:					*/
/*	√[(x2 – x1)2 + (y2 – y1)2												*/
/*	We then compare these a and b distances. If the horizontal hit point (a)*/
/*	is smaller, we set the ray->vertical variable to 0, which indicates that*/
/*	the ray hits a horizontal wall first. After that we update the final	*/
/*	hit point coordinates (ray->fin_x, ray->fin_y) to the horizontal hit	*/
/*	point coordinates. If the distance to the vertical hit point (b) is		*/
/*	smaller, we do the opposite, which indicates that the ray hits a		*/
/*	vertical wall first.													*/
/*	Next, we calculate the actual distance from the player to the wall hit	*/
/*	point using the Euclidian distance between the player's position and	*/
/*	the final hit point (ray->fin_x, ray->fin_y).							*/
void	chose_right_wall(t_game *game, t_ray *ray)
{
	double	a;
	double	b;

	a = sqrtf(pow(game->plr.x - ray->ax, 2) + pow(game->plr.y - ray->ay, 2));
	b = sqrtf(pow(game->plr.x - ray->bx, 2) + pow(game->plr.y - ray->by, 2));
	if (a < b)
	{
		ray->vertical = 0;
		ray->fin_x = ray->ax;
		ray->fin_y = ray->ay;
	}
	else
	{
		ray->vertical = 1;
		ray->fin_x = ray->bx;
		ray->fin_y = ray->by;
	}
	ray->distance = sqrt((pow(game->plr.x - ray->fin_x, 2)
				+ pow(game->plr.y - ray->fin_y, 2)));
}

/*	This function is used to cast rays in front of the player to calculate	*/
/*	what should be displayed on the screen. The distance from the player to	*/
/*	the wall along each ray is used to calculate how tall the wall should	*/
/*	appear on the screen.													*/
void	rays(t_game *game)
{
	int		i;
	double	angle;
	double	fov_pr;

	i = 0;
	angle = add_angle(game->plr.agl, -FOV / 2);
	fov_pr = FOV / WIDTH;
	cast_ray(game, &game->ray[WIDTH / 2], game->plr.agl);
	game->distance = game->ray[WIDTH / 2].distance;
	draw_bg(game);
	while (i < WIDTH)
	{
		if (i == WIDTH / 2)
		{
			cast_ray(game, &game->ray[i], angle);
			game->fin_x = game->ray[i].fin_x;
			game->fin_y = game->ray[i].fin_y;
		}
		else
			cast_ray(game, &game->ray[i], angle);
		wall(game, &game->ray[i], angle, i);
		angle = add_angle(angle, fov_pr);
		i++;
	}
}

/*	This function is the main part of our ray casting. We first look for	*/
/*	horizontal walls by calling h_wall() and do the same for vertical walls	*/
/*	by calling v_wall(), then we compare which wall is being hit first by	*/
/*	the ray thanks to the chose_right_wall() function. That function itself	*/
/*	then calls other helper functions to remove the fish-eye effect from	*/
/*	the game and also gets the walls' height.								*/
/*	After that, we remove the fish-eye effect by calling the				*/
/*	remove_fish_eye() function.												*/
/*	Finally, we calculate the projection plane distance and the height of	*/
/*	the wall using the get_wall_height() function.							*/
void	cast_ray(t_game *game, t_ray *ray, double angle)
{
	h_wall(game, angle, ray);
	v_wall(game, angle, ray);
	chose_right_wall(game, ray);
	remove_fish_eye(game, ray, angle);
	get_wall_height(ray);
}
