/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delelem_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:15:09 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 16:15:11 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_len(char **arr)
{
	int			i;
	int			len_arr;

	i = -1;
	len_arr = 0;
	while (arr[++i])
		len_arr++;
	return (len_arr);
}

void			ft_delelem_array(char ***array, int len, int start, int num)
{
	int			i;
	char		**arr;

	arr = *array;
	if (arr == NULL)
		return ;
	if (len == 0)
		len = ft_count_len(arr);
	if (start > len)
		return ;
	i = start - 1;
	while (++i < start + num)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	i = start - 1;
	while (++i < len - num)
		arr[i] = arr[i + num];
	while (i < len)
	{
		arr[i] = NULL;
		i++;
	}
	*array = arr;
}
