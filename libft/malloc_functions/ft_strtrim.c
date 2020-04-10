/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:18:52 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:40:39 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	int		a;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	str = 0;
	if (!s || s[0] == '\0')
		return (NULL);
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	a = i;
	while (s[i])
		i++;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\n'
		|| s[i] == '\t' || s[i] == '\0'))
		i--;
	while (a++ <= i)
		len++;
	str = (char*)ft_xmalloc(len + 1);
	ft_strncpy(str, s, len);
	return (str);
}
