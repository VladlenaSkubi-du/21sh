/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremerge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:22:34 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:37:51 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strremerge(char *s1, size_t len_s1, char *s2, size_t n)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	new = (char*)ft_xmalloc(len_s1 + n + 1);
	ft_memcpy(new, s1, len_s1);
	while ((size_t)i < len_s1)
		i++;
	while ((size_t)j < n)
		new[i++] = s2[j++];
	ft_strdel(&s1);
	return (new);
}
