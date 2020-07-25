/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treefree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:11:05 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 16:11:07 by sschmele         ###   ########.fr       */
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
