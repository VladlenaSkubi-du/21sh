/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:41:58 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:42:00 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr_d;
	char	*ptr_s;
	size_t	*l_d;
	size_t	*l_s;

	if (!src && !dst)
		return (NULL);
	l_d = (size_t *)dst;
	l_s = (size_t *)src;
	while (n >= sizeof(size_t))
	{
		*l_d++ = *l_s++;
		n -= sizeof(size_t);
	}
	ptr_d = (char *)l_d;
	ptr_s = (char *)l_s;
	while (n--)
		*ptr_d++ = *ptr_s++;
	return (dst);
}
