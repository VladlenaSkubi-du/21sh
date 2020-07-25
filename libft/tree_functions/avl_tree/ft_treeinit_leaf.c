/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeinit_leaf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:11:13 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 16:11:15 by sschmele         ###   ########.fr       */
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
