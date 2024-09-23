#include "../cub3d.h"

int	errormsgmap(int nb, t_game *game)
{
	int	i;

	i = -1;
	if (nb == 0)
	{
		ft_putstr_fd("Error\nInvalid char on the map\n", 2);
		while (game->map[++i])
			free(game->map[i]);
		free(game->map);
	}
	if (nb == 1)
	{
		ft_putstr_fd("Error\nToo many player on the map\n", 2);
		while (game->map[++i])
			free(game->map[i]);
		free(game->map);
	}
	if (nb == 2)
	{
		ft_putstr_fd("Error\nMap not closed\n", 2);
		while (game->map[++i])
			free(game->map[i]);
		free(game->map);
	}
	exit (EXIT_FAILURE);
}
