/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treefill_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:10:48 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 16:10:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Here we recursively go through all the leaves and insert each key
** (for eg. program name) in the alphabetic order into the array
** (one key name = one string in the array)
** And count the maximal key name length among all selected
*/

int				ft_treefill_array(t_avltree **root, char **list,
					int *len, int *max)
{
	int					len_word;

	len_word = 0;
	if (root != NULL && *root != NULL)
	{
		ft_treefill_array(&((*root)->left), list, len, max);
		if ((*root)->key != NULL)
		{
			list[*len] = ft_strdup((*root)->key);
			len_word = ft_strlen((*root)->key);
			*max = (len_word > *max) ? len_word : *max;
			(*len)++;
		}
		ft_treefill_array(&((*root)->right), list, len, max);
	}
	return (0);
}
