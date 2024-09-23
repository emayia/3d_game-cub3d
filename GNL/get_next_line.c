#include "../cub3d.h"

char	*writeligne(char *box)
{
	int		i;
	char	*str;

	i = 0;
	while (box[i] != '\n')
		i++;
	str = malloc(sizeof(char) * i + 2);
	i = 0;
	while (box[i] != '\n')
	{
		str[i] = box[i];
		i++;
	}
	if (box[i] == '\n')
	{
		str[i] = box[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*newbox(char *box)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (box[i] != '\n')
		i++;
	if (box[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (ft_strlen(box) - i + 1));
	while (box[i])
	{
		str[j] = box[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(box);
	return (str);
}

char	*gnlbis(int fd, char *box)
{
	int		count;
	char	buffer[BUFFER_SIZE + 1];

	count = 1;
	while (count >= 1 && comparegnl(box) != 1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		buffer[count] = '\0';
		if ((count == 0 && !box) || (count == 0 && box[0] == '\0'))
		{
			free(box);
			return (NULL);
		}
		if (box == NULL)
			box = strdupgnl(buffer);
		else
			box = strjoingnl(box, buffer);
	}
	return (box);
	free(box);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*box;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	box = gnlbis(fd, box);
	if (!box)
		return (NULL);
	if (comparegnl(box) == 1)
	{
		line = writeligne(box);
		box = newbox(box);
		return (line);
	}
	else if (box && comparegnl(box) == 0)
	{
		line = strdupgnl(box);
		free(box);
		box = malloc(sizeof(char) * 1);
		box[0] = '\0';
		return (line);
	}
	return (NULL);
}
