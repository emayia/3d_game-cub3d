#include "../cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*strdupgnl(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	while (buffer[i])
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	comparegnl(char *box)
{
	int	i;

	i = 0;
	if (!box || box[i] == '\0')
		return (0);
	while (box[i])
	{
		if (box[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*strjoingnl(char *box, char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (buffer[0] == '\0' || !buffer)
		return (box);
	str = malloc(sizeof(char) * (ft_strlen(box) + ft_strlen(buffer) + 1));
	while (box[i])
	{
		str[i] = box[i];
		i++;
	}
	while (buffer[j])
	{
		str[i + j] = buffer[j];
		j++;
	}
	str[i + j] = '\0';
	free(box);
	return (str);
}
