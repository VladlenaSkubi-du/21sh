/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeinit_leaf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:27:38 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/05/25 16:32:34 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_avltree			*ft_treeinit_leaf(char *key)
{
	t_avltree			*new_leaf;

	new_leaf = (t_avltree*)ft_xmalloc(sizeof(t_avltree));
	new_leaf->key = ft_strdup(key);
	new_leaf->value = NULL;
	new_leaf->right = NULL;
	new_leaf->left = NULL;
	return (new_leaf);
}