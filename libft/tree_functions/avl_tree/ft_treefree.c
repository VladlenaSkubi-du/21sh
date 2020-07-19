/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treefree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:36:54 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/05/25 16:39:18 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_treefree(t_avltree **root)
{
	if (root != NULL && *root != NULL)
	{
		ft_treefree(&((*root)->right));
		free((*root)->key);
		(*root)->key = NULL;
		free((*root)->value);
		(*root)->value = NULL;
		ft_treefree(&((*root)->left));
		free(*root);
	}
}