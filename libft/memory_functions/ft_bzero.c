/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:41:40 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/13 19:00:30 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			*l_ptr;
	unsigned char	*str;

	l_ptr = (size_t *)s;
	while (n >= sizeof(size_t))
	{
		*l_ptr++ = 0;
		n -= sizeof(size_t);
	}
	str = (unsigned char *)l_ptr;
	while (n--)
		*str++ = 0;
}
