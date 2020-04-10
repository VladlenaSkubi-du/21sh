#include "shell21.h"
#include "parser.h"

//сделать адекватные выходы

int				insert_to_path_tree(char *entry_name,
					t_path **root, int *len)
{
	t_path			*new;

	init_new_leaf(entry_name, &new);
	if (*root == NULL)
	{
		*root = new;
		(*len) += 1;
	}
	else
		insert_new_leaf_to_tree(root, &new, len);
	return (0);
}

void			init_new_leaf(char *entry_name, t_path **tmp)
{
	*tmp = (t_path*)ft_xmalloc(sizeof(t_path));
	(*tmp)->name = ft_strdup(entry_name);
	(*tmp)->prev = NULL;
	(*tmp)->next = NULL;
	(*tmp)->flag = 0;
}

int				insert_new_leaf_to_tree(t_path **root,
					t_path **new, int *len)
{
	t_path			*current;
	t_path			*parent;

	current = *root;
	while (1)
	{
		parent = current;
		if (!(ft_strcmp((*new)->name, parent->name)))
		{
			free_path_tree(new);
			return (0);
		}
		else if (ft_strcmp((*new)->name, parent->name) < 0)
		{
			if (!(insert_leaf_prev(&current, &parent, new, len)))
				return (0);
		}
		else
		{
			if (!(insert_leaf_next(&current, &parent, new, len)))
				return (0);
		}
	}
	return (0);
}

int				insert_leaf_prev(t_path **current, t_path **parent,
					t_path **temp, int *len)
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
