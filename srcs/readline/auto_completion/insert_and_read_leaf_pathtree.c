#include "shell21.h"
#include "parser.h"

/*
** In order to add a new leaf to the tree, we initialize the leaf
** If @root was empty, leaf becomes a root
** otherwise, leaf is inserted on the right or left side from the last
** leaf with the same parameters (alphabetically)
*/

int				insert_to_path_tree(char *entry_name,
					t_path **root, int *len)
{
	t_path			*new_leaf;

	new_leaf = (t_path*)ft_xmalloc(sizeof(t_path));
	new_leaf->name = ft_strdup(entry_name);
	new_leaf->prev = NULL;
	new_leaf->next = NULL;
	new_leaf->flag = 0;
	if (*root == NULL)
	{
		*root = new_leaf;
		(*len) += 1;
	}
	else
		insert_new_leaf_to_tree(root, &new_leaf, len);
	return (0);
}

/*
** First "if" is for the equal names - the coming @new is freed then
** "else if" is for name that is alphabetically lower than the one we
** are on
** "else" is for the name that is alphabetically higher than the
** one we are on
*/

int				insert_new_leaf_to_tree(t_path **root,
					t_path **new_leaf, int *len)
{
	t_path			*current;
	t_path			*parent;

	current = *root;
	while (1)
	{
		parent = current;
		if (!(ft_strcmp((*new_leaf)->name, parent->name)))
		{
			free_path_tree(new_leaf);
			return (0);
		}
		else if (ft_strcmp((*new_leaf)->name, parent->name) < 0)
		{
			if (!(insert_leaf_prev(&current,
					&parent, new_leaf, len)))
				return (0);
		}
		else
		{
			if (!(insert_leaf_next(&current,
					&parent, new_leaf, len)))
				return (0);
		}
	}
	return (0);
}

/*
** @current and @parent are equal in the beginning
** @temp is a new leaf to be inserted
** if @current->prev is not NULL, we come back to the
** loop and try to find those current->prev that will be NULL
*/

int				insert_leaf_prev(t_path **current,
					t_path **parent, t_path **temp, int *len)
{
	*current = (*current)->prev;
	if (*current == NULL)
	{
		(*parent)->prev = *temp;
		(*len) += 1;
		return (0);
	}
	return (1);
}

/*
** @current and @parent are equal in the beginning
** @temp is a new leaf to be inserted
** if @current->next is not NULL, we come back to the
** loop and try to find those current->next that will be NULL
*/

int				insert_leaf_next(t_path **current, t_path **parent,
					t_path **temp, int *len)
{
	*current = (*current)->next;
	if (*current == NULL)
	{
		(*parent)->next = *temp;
		(*len) += 1;
		return (0);
	}
	return (1);
}

/*
** Here we recursively go through all the leaves and insert each
** program name in the alphabetic order into the array (one program name
** = one string in the array)
** And count the maximal program name length among all selected
*/

int				fill_array_from_tree(t_path **root, char **list,
					int *len, int *max)
{
	int			len_word;

	len_word = 0;
	if (root != NULL && *root != NULL)
	{
		fill_array_from_tree(&((*root)->prev), list, len, max);
		if ((*root)->name != NULL)
		{
			list[*len] = ft_strdup((*root)->name);
			len_word = ft_strlen((*root)->name);
			*max = (len_word > *max) ? len_word : *max;
			(*len)++;
		}
		fill_array_from_tree(&((*root)->next), list, len, max);
	}
	return (0);
}