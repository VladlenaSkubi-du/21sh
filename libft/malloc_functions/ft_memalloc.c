/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:36:19 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:36:21 by sschmele         ###   ########.fr       */
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
