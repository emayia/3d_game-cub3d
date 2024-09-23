#include "../cub3d.h"

int	addvaluetorighttab(char **str, t_game *game)
{
	int	fd;

	fd = 0;
	if (addeano(str, game, fd) == 1)
		return (1);
	if (addsowe(str, game, fd) == 1)
		return (1);
	if (addfc(str, game) == 1)
		return (1);
	return (0);
}

int	checkandfillrgbvalue(char *str, t_game *game, char s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] != '\0')
				count++;
			else
				return (errormsg(7));
		}
		i++;
	}
	if (count != 2 || colorcheck(str) == 1)
		return (errormsg(7));
	game->parsing.colorcheck = ft_split(str, ',');
	i = 0;
	if (setvalueforcolorbis(game, s, i) == 1)
		return (1);
	return (0);
}

int	setvalueforcolorbis(t_game *game, char s, int i)
{
	while (game->parsing.colorcheck[i])
	{
		game->parsing.atoitest = ft_atoi(game->parsing.colorcheck[i]);
		if (game->parsing.atoitest < 0 || game->parsing.atoitest > 255)
			return (errormsg(7));
		i++;
	}
	if (s == 'f')
	{
		game->rgb.floor_r = ft_atoi(game->parsing.colorcheck[0]);
		game->rgb.floor_g = ft_atoi(game->parsing.colorcheck[1]);
		game->rgb.floor_b = ft_atoi(game->parsing.colorcheck[2]);
	}
	else
	{
		game->rgb.ceil_r = ft_atoi(game->parsing.colorcheck[0]);
		game->rgb.ceil_g = ft_atoi(game->parsing.colorcheck[1]);
		game->rgb.ceil_b = ft_atoi(game->parsing.colorcheck[2]);
	}
	freetabcf(game, s);
	return (0);
}

void	freetabcf(t_game *game, char s)
{
	int	i;

	i = 0;
	if (s == 'f')
		free(game->parsing.ftab);
	else
		free(game->parsing.ctab);
	while (game->parsing.colorcheck[i])
	{
		free(game->parsing.colorcheck[i]);
		i++;
	}
	free(game->parsing.colorcheck);
}
