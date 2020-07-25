/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeadd_leaf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:07:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 16:09:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @current and @parent are equal in the beginning
** @temp is a new leaf to be inserted
** if @current->next is not NULL, we come back to the
** loop and try to find those current->next that will be NULL
*/

static int		insert_leaf_right(t_avltree **current,
					t_avltree **parent, t_avltree **temp, int *len)
{
	*current = (*current)->right;
	if (*current == NULL)
	{
		(*parent)->right = *temp;
		(*len) += 1;
		return (0);
	}
	return (1);
}

/*
** @current and @parent are equal in the beginning
** @temp is a new leaf to be inserted
** if @current->prev is not NULL, we come back to the
** loop and try to find those current->prev that will be NULL
*/

static int		insert_leaf_left(t_avltree **current,
					t_avltree **parent, t_avltree **temp, int *len)
{
	*current = (*current)->left;
	if (*current == NULL)
	{
		(*parent)->left = *temp;
		(*len) += 1;
		return (0);
	}
	return (1);
}

/*
** First "if" is for the equal names - the coming @new is freed then
** "else if" is for name that is alphabetically lower than the one we
** are on
** "else" is for the name that is alphabetically higher than the
** one we are on
*/

static int		insert_new_leaf_to_tree(t_avltree **root,
					t_avltree **new_leaf, int *len)
{
	t_avltree			*current;
	t_avltree			*parent;

	current = *root;
	while (1)
	{
		parent = current;
		if (!(ft_strcmp((*new_leaf)->key, parent->key)))
		{
			ft_treefree(new_leaf);
			return (0);
		}
		else if (ft_strcmp((*new_leaf)->key, parent->key) < 0)
		{
			if (!(insert_leaf_left(&current, &parent, new_leaf, len)))
				return (0);
		}
		else
		{
			if (!(insert_leaf_right(&current, &parent, new_leaf, len)))
				return (0);
		}
	}
	return (0);
}

/*
** In order to add a new leaf to the tree, we initialize the leaf
** If @root was empty, leaf becomes a root
** otherwise, leaf is inserted on the right or left side from the last
** leaf with the same parameters (alphabetically)
*/

int				ft_treeadd_leaf(t_avltree **root,
					t_avltree *new_leaf, int *len)
{
	if (*root == NULL)
	{
		*root = new_leaf;
		(*len) += 1;
	}
	else
		insert_new_leaf_to_tree(root, &new_leaf, len);
	return (0);
}
