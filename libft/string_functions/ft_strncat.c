/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:14:06 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/06 11:27:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*p;
	int		i;
	int		a;

	if ((n + 1) < n)
		return (NULL);
	p = s1;
	i = 0;
	a = 0;
	while (s1[i] != '\0')
		i++;
	while ((a < (int)n) && s2[a] != '\0')
	{
		s1[i] = s2[a];
		i++;
		a++;
	}
	s1[i] = '\0';
	return (p);
}
