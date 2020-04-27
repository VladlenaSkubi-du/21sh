/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrdiff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 13:42:18 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/04/27 13:42:41 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strchrdiff(const char *s1, const char *s2, char sy)
{
	int i;

	if (s1 == 0 || s2 == 0)
		return (0);
	else if (*s1 == '\0' && *s2 == '\0')
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] != sy)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if ((s1[i] == '\0' || s1[i] == sy) && !(s2[i] == '\0'))
		return (0);
	if (s2[i] == '\0' && !(s1[i] == '\0' || s1[i] == sy))
		return (0);
	return (1);
}