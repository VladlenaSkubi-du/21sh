#include "shell21.h"
#include "parser.h"

/*
** This func needs to fill path in the struct of file
*/

// char			*ft_take_path(char *dir_name)
// {
// 	char	*new;

// 	if (dir_name[0] == '/' && dir_name[1] == '\0')
// 		new = ft_strdup(dir_name);
// 	else
// 	{
// 		new = ft_strnew(ft_strlen(dir_name) + 1);
// 		new = ft_strcpy(new, dir_name);
// 		new = ft_strcat(new, "/");
// 	}
// 	return (new);
// }

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
			*max = (len_word > *max) ? len_word : *max; //исправила 0 на max
			(*len)++;
		}
		fill_array_from_tree(&((*root)->next), list, len, max);
	}
	return (0);
}

char			**form_result_array(t_path **root, int len, int *max)
{
	char		**list;
	int			l;

	l = 0;
	list = (char**)ft_xmalloc(sizeof(char*) * (len + 1));
	fill_array_from_tree(root, list, &l, max);
	return (list);
}
