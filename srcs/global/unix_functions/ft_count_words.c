#include "shell21.h"

size_t	ft_count_words(char const *s, char c, size_t len)
{
	size_t	k;
	size_t	i;

	k = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c || i + 1 == len))
			k++;
		i++;
	}
	return (k);
}
