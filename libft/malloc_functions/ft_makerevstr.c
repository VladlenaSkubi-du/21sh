/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makerevstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:27:59 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:15:03 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_makerevstr(char *s)
{
	char	*str;
	int		i;
	int		len;

	str = 0;
	if (s && *s != '\0')
	{
		i = 0;
		len = ft_strlen(s);
		str = (char*)ft_xmalloc(len * sizeof(char));
		while (len--)
		{
			str[i] = s[len];
			i++;
		}
	}
	return (str);
}
