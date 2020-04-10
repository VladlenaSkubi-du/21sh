/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:31:30 by sschmele          #+#    #+#             */
/*   Updated: 2018/11/27 16:32:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				res;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	res = 0;
	while (n > 0)
	{
		res = (unsigned char)*str1 - (unsigned char)*str2;
		if (res == 0)
		{
			str1++;
			str2++;
		}
		else
			break ;
		n--;
	}
	return (res);
}
