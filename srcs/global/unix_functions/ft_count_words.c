/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:34:15 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:34:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

size_t	ft_count_words(char const *s, char c, size_t len)
{
	size_t	k;
	size_t	i;

	k = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c || i + 1 == len))
			k++;
		i++;
	}
	return (k);
}
