/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewsetchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 09:41:22 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:36:48 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnewsetchar(size_t size, char c)
{
	char			*s;
	size_t			i;

	if ((size + 1) < size)
		return (NULL);
	i = -1;
	s = (char*)ft_xmalloc(size + 1);
	while (++i < size)
		s[i] = (unsigned char)c;
	return (s);
}
