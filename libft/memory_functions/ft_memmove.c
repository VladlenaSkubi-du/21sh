/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:25:56 by sschmele          #+#    #+#             */
/*   Updated: 2019/04/04 20:05:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (!(dst || src))
		return (NULL);
	dest = dst;
	source = (unsigned char*)src;
	if (source >= dest)
		while (len--)
			*dest++ = *source++;
	else if (source < dest)
		while (len--)
			dest[len] = source[len];
	return (dst);
}
