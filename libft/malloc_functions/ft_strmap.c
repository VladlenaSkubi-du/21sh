/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:50:15 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:33:56 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = (char*)ft_xmalloc((len + 1) * sizeof(*s));
	while (*s)
	{
		*str = f(*s);
		str++;
		s++;
	}
	return (str - len);
}
