/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 18:09:40 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:13:58 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_dig(long value, int base)
{
	int				res;

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

static char		*ft_ltoa_base_exceptions(long nb)
{
	char			*s;

	s = NULL;
	if (nb == 0)
		return ("0");
	return (s);
}

char			*ft_ltoa_base(long nb, int base)
{
	int				i;
	char			*str;
	int				len;
	char			*core;

	if ((!nb && !base && !(base >= 2 && base <= 16)) || nb == 0)
		return (ft_ltoa_base_exceptions(nb));
	i = 0;
	core = "0123456789ABCDEF";
	len = nb < 0 && base == 10 ? count_dig(nb, base) + 1 : count_dig(nb, base);
	str = (char*)ft_xmalloc(len + 1);
	str[0] = (nb < 0) ? '-' : 0;
	if (str[0] == '-')
		while (nb)
		{
			str[len - ++i] = core[-(nb % base)];
			nb /= base;
		}
	else
		while (nb)
		{
			str[len - ++i] = core[nb % base];
			nb /= base;
		}
	return (str);
}
