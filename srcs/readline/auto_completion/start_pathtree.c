#include "shell21.h"
#include "parser.h"

/*
** The first function from which we fill root variable (that is a tree)
** with program names: builtin that will be always and commands that
** will be available if PATH variable will be valid and there will be
** permission to read directories in PATH
** @find is a null/letter(s)/word to be found (coincidences)
** @path is the value of PATH variable: PATH=/user/bin:/bin - will be
** @path = "/usr/bin:/bin"
** @total and @max are values to be filled while building the tree:
** @total = number of program names found and @max - the longest word
*/

char			**start_search_in_path(char *find, char *path,
					int *total, int *max)
{
	t_path			*root;
	char			**list;
	int				len;
	int				i;

	len = 0;
	root = NULL;
	save_builtins(&root, &len, find);
	if ((list = ft_strsplit(path, ':')) != NULL)
	{
		i = -1;
		while (list[++i])
		{
			save_path_entry(list[i], &root, &len, find);
			free(list[i]);
		}
		free(list);
	}
	*total = len;
	list = form_result_array(&root, len, max);
	free_path_tree(&root);
	return (list);
}

/*
** Go through builtin-global and save all the builtin names to tree
*/

int				save_builtins(t_path **root, int *len, char *find)
{
	int				i;
	int				find_len;

	i = 0;
	find_len = ft_strlen(find);
	while (g_builtins[i])
	{
		if (ft_strncmp(g_builtins[i], find, find_len) == 0)
			insert_to_path_tree(g_builtins[i], root, len);
		i++;
	}
	return (0);
}

/*
** If path can be open, reading its content and saving to tree
*/

int				save_path_entry(char *dir_path, t_path **root, int *len,
					char *find)
{
	DIR				*dir_name;
	struct dirent	*entry;
	int				find_len;

	if (!(dir_name = opendir(dir_path)))
		return (1);
	find_len = ft_strlen(find);
	while ((entry = readdir(dir_name)))
	{
		if (ft_strnequ(entry->d_name, find, find_len) &&
			ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, ".."))
			insert_to_path_tree(entry->d_name, root, len);
	}
	closedir(dir_name);
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

int				free_path_tree(t_path **root)
{
	if (root != NULL && *root != NULL)
	{
		free_path_tree(&((*root)->next));
		free((*root)->name);
		free_path_tree(&((*root)->prev));
		free(*root);
	}
	return (0);
}
