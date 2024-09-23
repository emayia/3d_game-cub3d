#include "../cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		lenword1;
	int		lenword2;
	char	*str;

	i = -1;
	if (s1 && s2)
	{
		lenword1 = ft_strlen(s1);
		lenword2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (lenword1 + lenword2 + 1));
		if (str == 0)
			return (0);
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
			str[lenword1 + i] = s2[i];
		str[lenword1 + i] = 0;
		free(s1);
		return (str);
	}
	return (NULL);
}
