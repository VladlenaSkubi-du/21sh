/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:32:09 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 13:34:48 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*temp;
	int		i;

	i = 0;
	if (!s1 || s1[0] == '\0')
		return (NULL);
	if ((n + 1) < n)
		return (NULL);
	temp = (char*)ft_xmalloc((n + 1) * sizeof(*s1));
	while (n)
	{
		temp[i] = s1[i];
		i++;
		n--;
	}
	return (temp);
}
