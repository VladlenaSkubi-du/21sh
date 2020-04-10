#include "libft.h"

void				ft_putnendl_fd(char *str, int n, int fd)
{
	int				i;

	i = 0;
	while (i < n && str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}