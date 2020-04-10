/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrejoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:39:33 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:44:24 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrejoin(char *s1, char *s2)
{
	char	*str;
	int		len_1;
	int		len_2;

	str = 0;
	if (s1 && s2)
	{
		len_1 = ft_strlen(s1);
		len_2 = ft_strlen(s2);
		str = (char*)ft_memalloc(len_1 + len_2 + 1);
		ft_strcat(str, s1);
		ft_strcat(str, s2);
	}
	ft_strdel(&s1);
	return (str);
}
