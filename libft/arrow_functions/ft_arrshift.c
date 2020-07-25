/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:12:59 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 16:13:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @arr should have enough space for positive shift
** If you need to add 3 str after the 2nd str (after 'b-str'):
** arr = "abcdef0000" - is the buffer (len 10) with some content
**        abcdef
** where each str goes down
** ft_arrshift(arr + 2, 10, 3)
** Result: arr = "ab000cdef0"
**                ab   cdef
**
** If you neew to delete 3 str before d-str:
** arr = "abcdef0000" - is the buffer (len 10) with some content
**        abcdef
** ft_arrshift(arr + 3, 10, -3)
** Result: arr = "def0000000"
**                def
**
** If you neew to delete d-str:
** arr = "abcdef0000" - is the buffer (len 10) with some content
**        abcdef
** ft_arrshift(arr + 3, 10, -3)
** Result: arr = "abcef00000"
**                abcef
**
** THERE IS NO "PROTECTION" for the negative shift - should be done
** from the function that calls
*/

void			ft_arrshift(char **arr, int size, int shift)
{
	char		**buff;
	int			i;

	if (arr == (char**)NULL)
		return ;
	buff = (char**)ft_xmalloc(sizeof(char*) * (size + 1));
	ft_memcpy(buff, arr, sizeof(char*) * size);
	if (shift < 0)
	{
		i = shift - 1;
		while (++i)
			free(arr[i]);
	}
	ft_memcpy(arr + shift, buff, sizeof(char*) * (size - shift));
	i = 0;
	while (i < shift)
	{
		arr[i] = (char*)NULL;
		i++;
	}
	free(buff);
}
