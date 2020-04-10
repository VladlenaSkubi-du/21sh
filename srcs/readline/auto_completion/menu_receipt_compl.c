#include "shell21.h"
#include "readline.h"

char				**get_variables(char *complete, int *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	root = fill_tree_with_variables(complete, total);
	menu = form_result_array(&root, *total, max_len);
	free_path_tree(&root);
	return (menu);
}

int					insert_variables_to_tree(char *array, char *complete,
						t_path **root, int *total)
{
	char			*tmp;
	int				len;

	len = ft_strlen(complete);
	tmp = ft_strndup(array, ft_strchri(array, '='));
	if (ft_strnequ(tmp, complete, len))
		insert_to_path_tree(tmp, root, total);
	free(tmp);
	return (0);
}

t_path				*fill_tree_with_variables(char *complete, int *total)
{
	int				i;
	t_path			*root;

	i = 0;
	root = NULL;
	while (g_env[i])
	{
		insert_variables_to_tree(g_env[i], complete, &root, total);
		i++;
	}
	i = 0;
	while (g_shvar[i])
	{
		insert_variables_to_tree(g_shvar[i], complete, &root, total);
		i++;
	}
	i = 0;
	while (g_lovar[i]) //TODO correct
	{
		insert_variables_to_tree(g_lovar[i], complete, &root, total);
		i++;
	}
	return (root);
}

char				**get_arguments(char **complete,
						int *total, int *max_len)
{
	char			**menu;
	char			*path;
	char			*compl;
	int				tmp;
	t_path			*root;

	tmp = ft_strchri(*complete, '/');
	path = find_path_compl(*complete, tmp);
	compl = (tmp >= 0 && tmp < (int)ft_strlen(*complete))
			? ft_strdup(*complete + tmp + 1) : NULL;
	if (compl != NULL)
	{
		free(*complete);
		*complete = compl;
	}
	root = fill_tree_with_arguments(path, *complete, total);
	if (root == NULL)
	{
		free(path);
		return (NULL);
	}
	menu = form_result_array(&root, *total, max_len);
	free_path_tree(&root);
	free(path);
	return (menu);
}

t_path				*fill_tree_with_arguments(char *path,
						char *complete, int *total)
{
	t_path			*root;
	int				len;
	DIR				*dir_name;
	struct dirent	*entry;

	root = NULL;
	if (path == NULL)
		return (NULL);
	len = ft_strlen(complete);
	if (!(dir_name = opendir(path)))
		return (NULL);
	while ((entry = readdir(dir_name)))
	{
		if ((entry->d_name[0] == '.' && entry->d_name[1] == '\0') ||
			(entry->d_name[0] == '.' && entry->d_name[1] &&
			entry->d_name[1] == '.' && entry->d_name[2] == '\0') ||
			ft_isprint(entry->d_name[0]) == 0)
			continue ;
		if (ft_strnequ(entry->d_name, complete, len))
			insert_to_path_tree(entry->d_name, &root, total);
	}
	closedir(dir_name);
	return (root);
}
