/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:21:58 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/11 13:43:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	i;
	unsigned char	m;
	size_t			j;

	if (n == 0)
		return (0);
	j = 0;
	while (s1[j] && s2[j] && s1[j] == s2[j] && j < n - 1)
		j++;
	i = (unsigned char)s1[j];
	m = (unsigned char)s2[j];
	return ((int)(i - m));
}
