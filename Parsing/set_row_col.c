#include "../cub3d.h"

void	set_col(t_game *game)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) > num)
			num = ft_strlen(game->map[i]);
		i++;
	}
	game->col = num;
}

void	set_row(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		i++;
	game->row = i;
}

void	set_row_col(t_game *game)
{
	set_row(game);
	set_col(game);
	fix_map(game);
}
