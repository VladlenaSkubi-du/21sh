/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:49:53 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:32:14 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		le;
	char	*temp;

	if (!s1)
		return ((char*)s1);
	le = ft_strlen(s1);
	temp = (char*)ft_xmalloc((le + 1) * sizeof(*s1));
	while (*s1 != '\0')
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	return (temp -= le);
}
