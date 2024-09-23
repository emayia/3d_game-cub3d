#include "../cub3d.h"

int	prepamap(t_game *game)
{
	game->parsing.maptmp = NULL;
	while (game->parsing.tab[game->parsing.k][0] == '\n')
		game->parsing.k++;
	while (game->parsing.tab[game->parsing.k])
	{
		if (game->parsing.maptmp == NULL)
			game->parsing.maptmp
				= ft_strdup(game->parsing.tab[game->parsing.k]);
		else
			game->parsing.maptmp
				= ft_strjoin(game->parsing.maptmp,
					game->parsing.tab[game->parsing.k]);
		free(game->parsing.tab[game->parsing.k]);
		if (game->parsing.tab[game->parsing.k + 1]
			!= NULL && game->parsing.tab[game->parsing.k + 1][0]
				== '\n')
			break ;
		game->parsing.k++;
	}
	game->map = ft_split(game->parsing.maptmp, '\n');
	set_row_col(game);
	return (checkforbiddencharonmap(game));
}

int	checkforbiddencharonmap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->parsing.count = 0;
	while (game->map[i])
	{
		if (checkerforforbidden(game->map[i][j]
			, game, i, j) == 1)
			return (errormsgmap(0, game));
		if (game->map[i][j + 1] == '\0')
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	if (game->parsing.count < 1 || game->parsing.count > 1)
		return (errormsgmap(1, game));
	i = 0;
	j = 0;
	return (checkifclose(game, i, j));
}

int	checkerforforbidden(char c, t_game *game, int i, int j)
{
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
	{
		game->plr.x = j * 64 + 32;
		game->plr.y = i * 64 + 32;
		game->player = c;
		game->parsing.count++;
		set_angle(game);
		return (0);
	}
	if (c == ' ' || c == '1' || c == '0')
		return (0);
	return (1);
}

void	set_angle(t_game *game)
{
	if (game->player == 'E')
		game->plr.agl = 2 * M_PI;
	else if (game->player == 'N')
		game->plr.agl = M_PI / 2;
	else if (game->player == 'W')
		game->plr.agl = M_PI;
	else if (game->player == 'S')
		game->plr.agl = 3 * M_PI / 2;
}

int	checkifclose(t_game *game, int i, int j)
{
	while (game->map[i])
	{
		if (game->map[i][j] == '0')
		{
			if (i == 0 || j == 0 || game->map[i][j + 1] == '\0'
				|| game->map[i + 1] == NULL
				|| game->map[i][j + 1] == ' '
				|| game->map[i][j - 1] == ' '
				|| game->map[i + 1][j] == ' '
				|| game->map[i - 1][j] == ' ')
				return (errormsgmap(2, game));
		}
		if (game->map[i][j + 1] == '\0')
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (0);
}
