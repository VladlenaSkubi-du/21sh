/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makerevstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:36:11 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:36:13 by sschmele         ###   ########.fr       */
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
