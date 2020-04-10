/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 18:09:40 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:41:20 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits_u(unsigned long value, int base)
{
	int		res;

	res = 0;
	if (value == 0)
		return (1);
	while (value)
	{
		value /= base;
		res++;
	}
	return (res);
}

char		*ft_utoa_base(unsigned long nb, int base)
{
	int		i;
	char	*str;
	int		len;
	char	*core;

	if (!nb && !base && !(base >= 2 && base <= 16))
		return (NULL);
	i = 0;
	core = "0123456789ABCDEF";
	len = count_digits_u(nb, base);
	str = (char*)ft_xmalloc(len + 1);
	if (nb == 0)
		str[0] = 0 + '0';
	while (nb)
	{
		str[len - ++i] = core[nb % base];
		nb /= base;
	}
	return (str);
}
