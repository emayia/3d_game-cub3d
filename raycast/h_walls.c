#include "../cub3d.h"

/*	This function helps us determine if a ray is hitting a horizontal wall.	*/
/*	We first check if the ray is pointing directly right or left, if so, we	*/
/*	set the hit point (ray->ax and ray->ay), return 1 and continue on.		*/
/*	If the ray isn't pointing directly on the x axis (right or left), we	*/
/*	check if the ray is pointing upwards [0,π] or downwards [π,2π].			*/
/*	Based on that, we set the y position of the ray (ray->ay) to the top or	*/
/*	bottom edge of the player's current tile and also adjust the (incr_y)	*/
/*	var's to the length of the tile (negative if pointing upwards, positive	*/
/*	if down).																*/
int	check_h_wall(t_game *game, double angle, t_ray *ray, double *incr_y)
{
	if ((angle > 0 - ERR_MARG && angle < 0 + ERR_MARG)
		|| (angle > 2 * M_PI - ERR_MARG && angle < 2 * M_PI + ERR_MARG))
	{
		ray->ax = TILE * game->col;
		ray->ay = game->plr.y;
		return (1);
	}
	else if (angle > M_PI - ERR_MARG && angle < M_PI + ERR_MARG)
	{
		ray->ay = game->plr.y;
		ray->ax = 0;
		return (1);
	}
	else if (angle >= 0 && angle <= M_PI)
	{
		*incr_y -= TILE;
		ray->ay = floor(game->plr.y / TILE) * TILE - ERR_MARG;
	}
	else
	{
		*incr_y = TILE;
		ray->ay = floor(game->plr.y / TILE) * TILE + TILE;
	}
	return (0);
}

/*	This function checks whether the current horizontal intersection point	*/
/*	(ray->ax, ray->ay) is within the map and if the the tile at that point	*/
/*	is a floor ('0') or a wall ('1'). If the point is within the map and	*/
/*	the tile is a floor, we return 1, else we return 0.						*/
int	check_h_exists(t_game *game, t_ray *ray)
{
	int	x;
	int	y;

	x = (int)ray->ax / TILE;
	y = (int)ray->ay / TILE;
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

/*	This function casts a ray until it hits a wall, specifically for		*/
/*	horizontal intersections. We first start by calling check_h_wall() to	*/
/*	set the initial y position of the ray. If it returns 1 (which means the	*/
/*	ray is pointing directly to the right or left edge of the map), the		*/
/*	function sets ray->ax to that edge and ends early.						*/
/*	Else (if it returns 0), we calculate the x increment (incr_x) for each	*/
/*	step of the ray, based on the angle of the ray and the y increment		*/
/*	(incr_y). We also set the initial x position of the ray (ray->ax).		*/
/*	After that, we start a loop within which we move the ray one step at a	*/
/*	time by adding (incr_y) to (ray->ay) and (incr_x) to (ray->ax) until the*/
/*	ray is out of the map or hits a wall (when check_h_exists() returns 0).	*/
void	h_wall(t_game *game, double angle, t_ray *ray)
{
	double	incr_x;
	double	incr_y;

	incr_y = 0;
	if (check_h_wall(game, angle, ray, &incr_y))
		return ;
	incr_x = -incr_y / tan(angle);
	ray->ax = game->plr.x + (game->plr.y - ray->ay) / tan(angle);
	while (check_h_exists(game, ray))
	{
		ray->ay += incr_y;
		ray->ax += incr_x;
		if (ray->ax > TILE * game->col)
		{
			ray->ax = TILE * game->col;
			return ;
		}
		else if (ray->ax < 0)
		{
			ray->ax = 0;
			return ;
		}
	}
}
