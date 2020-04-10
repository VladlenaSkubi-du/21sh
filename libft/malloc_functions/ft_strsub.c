/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:42:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:40:01 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	if ((len + 1) < len)
		return (NULL);
	if (s)
	{
		str = (char*)ft_xmalloc((len + 1) * sizeof(*s));
		while (len)
		{
			str[i] = s[start + i];
			i++;
			len--;
		}
	}
	return (str);
}
