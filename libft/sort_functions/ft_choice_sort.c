/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choice_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:11:11 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/08 17:13:13 by sschmele         ###   ########.fr       */
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

void			ft_choice_sort(char *s)
{
	int			i;
	int			min;

	i = 1;
	min = 0;
	if (*s == '\0')
		;
	else
	{
		while (s[i])
		{
			if (s[i] < s[min])
				min = i;
			i++;
		}
		i = 0;
		ft_swap(s, i, min);
		s++;
		ft_choice_sort(s);
	}
}
