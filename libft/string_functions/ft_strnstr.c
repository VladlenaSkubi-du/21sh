/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:47:38 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/06 16:20:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[i] && len)
	{
		a = 0;
		while (haystack[i + a] == needle[a] && a < len)
		{
			if (needle[a + 1] != '\0' && len == 0)
				return (NULL);
			else if (needle[a + 1] == '\0' && len != 0)
				return ((char*)haystack + i);
			a++;
		}
		i++;
		len--;
	}
	return (NULL);
}
