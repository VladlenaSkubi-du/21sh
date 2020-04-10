/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 12:51:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:16:23 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memalloc(size_t size)
{
	unsigned char	*str;
	void			*p;
	size_t			i;

	p = (void*)ft_xmalloc(size);
	i = -1;
	str = p;
	while (++i < size)
		str[i] = '\0';
	return (p);
}
