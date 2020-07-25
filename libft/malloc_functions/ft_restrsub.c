/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restrsub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:36:38 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:36:42 by sschmele         ###   ########.fr       */
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
