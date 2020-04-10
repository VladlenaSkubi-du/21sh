/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:20:45 by sschmele          #+#    #+#             */
/*   Updated: 2018/11/28 15:43:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		a = 0;
		while (haystack[i + a] == needle[a])
		{
			if (needle[a + 1] == '\0')
				return ((char*)haystack + i);
			a++;
		}
		i++;
	}
	return (NULL);
}
