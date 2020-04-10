/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:53:37 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/08 17:15:44 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_swap(char *s, int dst, int src)
{
	char		tmp;

	tmp = s[dst];
	s[dst] = s[src];
	s[src] = tmp;
}

void			ft_bubble_sort(char *s)
{
	int			i;
	int			j;
	int			len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		while (j < (len - 1))
		{
			if (s[j] > s[j + 1])
				ft_swap(s, j, j + 1);
			j++;
		}
		j = 0;
		i++;
	}
}
