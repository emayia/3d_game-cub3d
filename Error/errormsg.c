#include "../cub3d.h"

int	errormsg(int nb)
{
	if (nb == 1)
		ft_putstr_fd("Error\nInvalid nb of arguments\n", 2);
	if (nb == 2)
		ft_putstr_fd("Error\nInvalid file\n", 2);
	if (nb == 3)
		ft_putstr_fd("Error\nInvalid file or permissions\n", 2);
	if (nb == 4)
		ft_putstr_fd("Error\nPremap values incorrect\n", 2);
	if (nb == 5)
		ft_putstr_fd("Error\nDuplicate elements detected\n", 2);
	if (nb == 6)
		ft_putstr_fd("Error\nTexture not found\n", 2);
	if (nb == 7)
		ft_putstr_fd("Error\nWrong color setting\n", 2);
	if (nb == 10)
		ft_putstr_fd("Error\nInvalid map name\n", 2);
	return (1);
}
