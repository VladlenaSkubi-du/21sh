
#include "libft.h"

int			ft_strrchri(char *s, int c)
{
    int		i;
	char	*p;

	i = 0;
	p = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			p = (char*)s + i;
			break ;
		}
		i--;
	}
	if (i == 0 && p == 0)
		return (-1);
	return (p - s);
}