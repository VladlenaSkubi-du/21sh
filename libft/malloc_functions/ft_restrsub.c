/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restrsub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:57:18 by sbecker           #+#    #+#             */
/*   Updated: 2020/04/07 13:29:11 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_restrsub(char *s, int start, int len)
{
	char	*a;
	int		i;

	i = 0;
	if (!s)
		return (0);
	a = (char*)ft_xmalloc(len + 1);
	while (i < len)
	{
		a[i] = s[start];
		start++;
		i++;
	}
	free(s);
	return (a);
}
