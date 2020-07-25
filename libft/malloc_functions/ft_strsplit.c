/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:40:12 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:40:14 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*make_the_line(int j, char **av, char *p, int len_p)
{
	av[j] = (char*)ft_xmalloc((len_p + 1) * sizeof(char));
	ft_strncpy(av[j], p, len_p);
	return (av[j]);
}

static char		**split_it_for_me(const char *s, char c, int len_p, char **av)
{
	int			j;
	int			i;
	char		*p;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			i++;
		p = (char*)s + i;
		if (((unsigned char)s[i] != (unsigned char)c) && (s[i] != '\0'))
		{
			len_p = 0;
			while (((unsigned char)s[i] != (unsigned char)c) && s[i])
			{
				len_p++;
				i++;
			}
			make_the_line(j, av, p, len_p);
			j++;
		}
	}
	return (av);
}

static int		get_words_nb(const char *s, char c)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if ((char)s[i] == c)
			i++;
		else
		{
			nb++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (nb);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**av;
	int			ac;
	int			len_p;

	if (!(s && c))
		return (NULL);
	len_p = 0;
	ac = get_words_nb(s, c);
	av = (char**)ft_xmalloc((ac + 1) * (sizeof(char*)));
	split_it_for_me(s, c, len_p, av);
	return (av);
}
