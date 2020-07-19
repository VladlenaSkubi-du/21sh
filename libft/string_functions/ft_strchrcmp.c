#include "libft.h"

int			ft_strchrcmp(const char *s1, const char *s2, char x)
{
	size_t			i;
	unsigned char	end;

	i = 0;
	end = '\0';
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] && s2[i] && s1[i] != x && s1[i] != x)
		i++;
	if (s1[i] == x && s2[i] == x)
		return (0);
	if (s1[i] == x)
		return (end - (unsigned char)s2[i]);
	if (s2[i] == x)
		return ((unsigned char)s1[i] - end);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
