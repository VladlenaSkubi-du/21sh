/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:40:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:40:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @str should have enough space for positive shift
** If you need to add 3 chars after the 2nd char (after 'b'):
** str = "abcdef0000" - is the buffer (len 10) with some content
** ft_strshift(str + 2, 3)
** Result: str = "ab000cdef0"
**
** If you neew to delete 3 chars before d:
** str = "abcdef0000" - is the buffer (len 10) with some content
** ft_strshift(str + 3, -3)
** Result: str = "def0000000"
**
** If you neew to delete d:
** str = "abcdef0000" - is the buffer (len 10) with some content
** ft_strshift(str + 4, -1)
** Result: str = "abcef00000"
**
** THERE IS NO "PROTECTION" for the negative shift - should be done
** from the function that calls
*/

void			ft_strshift(char *str, int shift)
{
	char		*buff;
	int			i;

	if (str == (char*)NULL || str[0] == '\0')
		return ;
	buff = (char*)ft_xmalloc(ft_strlen(str) + 1);
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	i = 0;
	while (i < shift)
	{
		str[i] = '\0';
		i++;
	}
	free(buff);
}
