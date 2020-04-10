/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:02:24 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/03 15:24:47 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	a;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	a = 0;
	if (size > 0)
	{
		while (i < len_dst)
			i++;
		while ((i < (size - 1)) && src[a])
			dst[i++] = src[a++];
		dst[i] = '\0';
	}
	if ((size + 1) < size)
		return (len_src);
	if (len_dst > size)
		return (size + len_src);
	else
		return (len_dst + len_src);
}
