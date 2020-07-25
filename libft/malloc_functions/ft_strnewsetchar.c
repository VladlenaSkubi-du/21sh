/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewsetchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:39:49 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:39:52 by sschmele         ###   ########.fr       */
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
