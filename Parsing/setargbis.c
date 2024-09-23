#include "../cub3d.h"

int	checkparsing(char **av, int ac, t_game *game)
{
	int	i;

	i = 0;
	if (ac != 2)
		return (errormsg(1));
	while (av[1][i])
	{
		if (av[1][i] == '.')
			break ;
		if (av[1][i + 1] == '\0')
			return (errormsg(10));
		i++;
	}
	i = 0;
	game->parsing.namecheck = ft_split(av[1], '.');
	while (game->parsing.namecheck[i])
		i++;
	if (ft_strcmp("cub", game->parsing.namecheck[i - 1]) != 0)
		return (errormsg(10));
	game->parsing.count = 1;
	game->parsing.i = 0;
	if (takethefile(av, game) == 1)
		return (1);
	prepamap(game);
	return (0);
}

int	takethefile(char **av, t_game *game)
{
	char	*str;

	game->parsing.fd = open(av[1], O_RDONLY);
	if (game->parsing.fd == -1)
		return (errormsg(3));
	str = get_next_line(game->parsing.fd);
	if (str == NULL)
		return (errormsg(2));
	while (1)
	{
		free(str);
		str = get_next_line(game->parsing.fd);
		if (str == NULL)
			break ;
		game->parsing.count++;
	}
	free(str);
	return (takethefilebis(game, av));
}

int	takethefilebis(t_game *game, char **av)
{
	game->parsing.tab = malloc(sizeof(char *) * (game->parsing.count + 1));
	close(game->parsing.fd);
	game->parsing.fd = open(av[1], O_RDONLY);
	while (1)
	{
		game->parsing.tab[game->parsing.i] = get_next_line(game->parsing.fd);
		if (game->parsing.tab[game->parsing.i] == NULL)
			break ;
		game->parsing.i++;
	}
	close(game->parsing.fd);
	return (prepbeforemap(game));
}

void	setgamevalue(t_game *game)
{
	game->parsing.tmp = malloc(sizeof(char *) * 7);
	game->parsing.i = 0;
	game->parsing.j = 0;
	game->parsing.count = 0;
	game->parsing.ea = 0;
	game->parsing.we = 0;
	game->parsing.no = 0;
	game->parsing.so = 0;
	game->parsing.f = 0;
	game->parsing.c = 0;
	game->parsing.erroronthemap = 0;
}

int	prepbeforemap(t_game *game)
{
	setgamevalue(game);
	while (game->parsing.tab && game->parsing.count < 6)
	{
		while (game->parsing.tab[game->parsing.i][game->parsing.j] == '\n')
			game->parsing.i++;
		while (game->parsing.tab[game->parsing.i][game->parsing.j] == ' ')
			game->parsing.j++;
		if (game->parsing.tab[game->parsing.i][game->parsing.j] >= 65
			&& game->parsing.tab[game->parsing.i][game->parsing.j] <= 90)
		{
			game->parsing.tmp[game->parsing.count]
				= ft_strdup(game->parsing.tab[game->parsing.i]);
			game->parsing.i++;
			game->parsing.j = 0;
			game->parsing.count++;
		}
		else
			return (errormsg(4));
	}
	game->parsing.tmp[game->parsing.count] = NULL;
	if (setvaluepremap(game) == 1)
		return (1);
	return (0);
}
