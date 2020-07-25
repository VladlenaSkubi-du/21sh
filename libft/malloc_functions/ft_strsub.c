/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:41:12 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:41:14 by sschmele         ###   ########.fr       */
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
