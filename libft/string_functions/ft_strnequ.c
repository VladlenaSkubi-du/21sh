/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:23:44 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/02 17:40:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	if (s1 == 0 || s2 == 0)
		return (0);
	else if (*s1 == '\0' && *s2 == '\0')
		return (1);
	i = 0;
	while ((s1[i] || s2[i]) && n)
	{
		if (s1[i] == s2[i])
		{
			i++;
			n--;
		}
		else
			return (0);
	}
	return (1);
}
