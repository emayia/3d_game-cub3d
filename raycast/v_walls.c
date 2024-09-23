#include "../cub3d.h"

/*	This function checks whether the current vertical intersection point	*/
/*	(ray->bx, ray->by) is within the map and if the the tile at that point	*/
/*	is a floor ('0') or a wall ('1'). If the point is within the map and	*/
/*	the tile is a floor, we return 1, else we return 0.						*/
int	check_v_exists(t_game *game, t_ray *ray)
{
	int	x;
	int	y;

	x = (int)ray->bx / TILE;
	y = (int)ray->by / TILE;
	if ((x >= 0 && x < game->col) && (y >= 0 && y < game->row))
	{
		if (game->map[y][x] == '0' || is_char(game->map[y][x]))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

/*	This function helps us determine if a ray is hitting a vertical wall.	*/
/*	We first check if the ray is pointing directly up or down, if so, we	*/
/*	set the hit point (ray->bx and ray->by), return 1 and continue on.		*/
/*	If the ray isn't pointing directly on the y axis (up or down), we		*/
/*	check if the ray is pointing left [π/2,3π/2] or right [3π/2,π/2].		*/
/*	Based on that, we set the y position of the ray (ray->bx) to the left or*/
/*	right edge of the player's current tile and also adjust the (incr_x)	*/
/*	var to the length of the tile (negative if pointing left, positive		*/
/*	if right).																*/
int	check_v_wall(t_game *game, double angle, t_ray *ray, double *incr_x)
{
	if (angle < 3 * M_PI / 2 + ERR_MARG && angle > 3 * M_PI / 2 - ERR_MARG)
	{
		ray->by = TILE * game->row;
		ray->bx = game->plr.x;
		return (1);
	}
	else if (angle < M_PI / 2 + ERR_MARG && angle > M_PI / 2 - ERR_MARG)
	{
		ray->by = 0;
		ray->bx = game->plr.x;
		return (1);
	}
	else if (angle < 3 * M_PI / 2 && angle > M_PI / 2)
	{
		*incr_x = -TILE;
		ray->bx = floor((double)game->plr.x / TILE) * TILE - ERR_MARG;
	}
	else
	{
		*incr_x = TILE;
		ray->bx = floor((double)game->plr.x / TILE) * TILE + TILE;
	}
	return (0);
}

/*	This function casts a ray from the player's position towards a specific	*/
/*	angle and calls check_v_exists until it finds a wall or goes out of the	*/
/*	map. The ray's coordinates (ray->bx, ray->by) are incremented using the	*/
/*	incr_x and incr_y variables. These variables are calculated based on	*/
/*	the angle of the ray and the player's position.							*/
void	v_wall(t_game *game, double angle, t_ray *ray)
{
	double	incr_x;
	double	incr_y;

	incr_x = 0;
	if (check_v_wall(game, angle, ray, &incr_x))
		return ;
	incr_y = -incr_x * tan(angle);
	ray->by = game->plr.y + (game->plr.x - ray->bx) * tan(angle);
	while (check_v_exists(game, ray))
	{
		ray->by += incr_y;
		ray->bx += incr_x;
		if (ray->by > game->row * TILE)
		{
			ray->by = game->row * TILE;
			return ;
		}
		else if (ray->by < 0)
		{
			ray->by = 0;
			return ;
		}
	}
}
