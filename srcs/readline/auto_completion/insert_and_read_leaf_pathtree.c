#include "shell21.h"
#include "parser.h"

/*
** In order to add a new leaf to the tree, we initialize the leaf
** If @root was empty, leaf becomes a root
** otherwise, leaf is inserted on the right or left side from the last
** leaf with the same parameters (alphabetically)
*/

int				insert_to_path_tree(char *entry_name,
					t_pathtree **root, int *len)
{
	t_pathtree			*new_leaf;

	new_leaf = (t_pathtree*)ft_xmalloc(sizeof(t_pathtree));
	new_leaf->name = ft_strdup(entry_name);
	new_leaf->right = NULL;
	new_leaf->left = NULL;
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

int				insert_new_leaf_to_tree(t_pathtree **root,
					t_pathtree **new_leaf, int *len)
{
	t_pathtree			*current;
	t_pathtree			*parent;

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
			if (!(insert_leaf_left(&current,
					&parent, new_leaf, len)))
				return (0);
		}
		else
		{
			if (!(insert_leaf_right(&current,
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

int				insert_leaf_left(t_pathtree **current,
					t_pathtree **parent, t_pathtree **temp, int *len)
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
** @current and @parent are equal in the beginning
** @temp is a new leaf to be inserted
** if @current->next is not NULL, we come back to the
** loop and try to find those current->next that will be NULL
*/

int				insert_leaf_right(t_pathtree **current, t_pathtree **parent,
					t_pathtree **temp, int *len)
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
** Here we recursively go through all the leaves and insert each
** program name in the alphabetic order into the array (one program name
** = one string in the array)
** And count the maximal program name length among all selected
*/

int				fill_array_from_tree(t_pathtree **root, char **list,
					int *len, int *max)
{
	int					len_word;

	len_word = 0;
	if (root != NULL && *root != NULL)
	{
		fill_array_from_tree(&((*root)->left), list, len, max);
		if ((*root)->name != NULL)
		{
			list[*len] = ft_strdup((*root)->name);
			len_word = ft_strlen((*root)->name);
			*max = (len_word > *max) ? len_word : *max;
			(*len)++;
		}
		fill_array_from_tree(&((*root)->right), list, len, max);
	}
	return (0);
}