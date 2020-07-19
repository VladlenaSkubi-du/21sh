/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:02:47 by jcorwin           #+#    #+#             */
/*   Updated: 2020/05/23 20:11:30 by vladlenasku      ###   ########.fr       */
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
