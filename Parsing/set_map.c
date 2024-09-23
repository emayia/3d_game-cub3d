#include "../cub3d.h"

void	alloc_mem(t_game *game, char **tmp_map)
{
	int	i;

	i = 0;
	while (i < game->row)
	{
		tmp_map[i] = malloc(sizeof(char) * game->col + 1);
		i++;
	}
	tmp_map[i] = NULL;
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	fix_map(t_game *game)
{
	char	**tmp_map;
	int		i;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (game->row + 1));
	alloc_mem(game, tmp_map);
	while (i < game->row)
	{
		ft_strncpy(tmp_map[i], game->map[i], game->col + 1);
		i++;
	}
	tmp_map[i] = NULL;
	free_map(game);
	game->map = tmp_map;
}
