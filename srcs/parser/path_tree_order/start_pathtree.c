#include "shell21.h"
#include "parser.h"

char			**start_search_in_path(char *find, char *path,
					int *total, int *max)
{
	t_path			*root;
	char			**list;
	int				len;
	int				i;

	if ((list = ft_strsplit(path, ':')) == NULL)
		return (NULL);
	len = 0;
	root = NULL;
	save_builtins(&root, &len, find);
	i = -1;
	while (list[++i])
	{
		save_path_entry(list[i], &root, &len, find); //have adequate out-ways
		free(list[i]);
	}
	free(list);
	*total = len;
	list = form_result_array(&root, len, max);
	free_path_tree(&root);
	return (list);
}

int				save_path_entry(char *name_d, t_path **root, int *len,
					char *find)
{
	DIR				*dir_name;
	struct stat		*stat_b;
	struct dirent	*entry;
	int				find_len;

	stat_b = (struct stat*)ft_xmalloc(sizeof(struct stat));
	if (lstat(name_d, stat_b) == -1) //зачем? проверка доступа к папке?
	{
		free(stat_b);
		return (1);
	}
	free(stat_b);
	if (!(dir_name = opendir(name_d)))
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

int				save_builtins(t_path **root, int *len, char *find)
{
	int				i;

	i = 0;
	while (g_builtins[i])
	{
		if (ft_strcmp(g_builtins[i], find) == 0)
			insert_to_path_tree(g_builtins[i], root, len);
		i++;
	}
	return (0);
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
