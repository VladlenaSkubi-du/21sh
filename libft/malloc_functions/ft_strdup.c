/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:36:53 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:36:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		le;
	char	*temp;

	if (!s1)
		return ((char*)s1);
	le = ft_strlen(s1);
	temp = (char*)ft_xmalloc((le + 1) * sizeof(*s1));
	while (*s1 != '\0')
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	return (temp -= le);
}
