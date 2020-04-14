#include "shell21.h"
#include "parser.h"

char	**path_parse(void)
{
	char	*path_value;
	char	**ret;

	if (!(path_value = get_env("PATH")))
		return (0);
	ret = ft_strsplit(path_value, ':');
	free(path_value);
	return (ret);
}

char	*form_path(char *ret, char *env_path, char *name)
{
	ft_bzero(ret, ft_strlen(env_path) + ft_strlen(name) + 2);
	ft_strcpy(ret, env_path);
	ft_strcat(ret, "/");
	ft_strcat(ret, name);
	if (access(ret, X_OK) == -1)
	{
		error_handler(COMMAND_NON_EXECUTABLE, name);
		free(ret);
		ret = 0;
	}
	return (ret);
}

char	*locate_file(char *env_path, char *name)
{
	struct dirent	*entity;
	char			*ret;
	DIR				*path;

	ret = 0;
	path = opendir(env_path);
	if (path == NULL)
		return (NULL);
	while ((entity = readdir(path)))
	{
		if (!ft_strcmp(entity->d_name, name))
		{
			ret = (char*)ft_xmalloc(ft_strlen(env_path) + ft_strlen(name) + 2);
			ret = form_path(ret, env_path, name);
			if (ret)
				break;
		}
	}
	closedir(path);
	return (ret);
}

/*
** This is "just executable name case". We should check all directories in $PATH, find first match
** and check its accessibility
*/

char	*path_search(char *name)
{
	char			**path_array;
	char			**to_clean;
	char			*ret;

	if (!(path_array = path_parse()))
		return (0);
	to_clean = path_array;
	while (*path_array)
	{
		ret = locate_file(*path_array, name);
		if (ret)
			break;
		path_array++;
	}
	free_vec(to_clean);
	if (!ret)
		error_handler(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), name);
	return (ret);  /* Returns zero if we did not find anything */
}

/*
** Here we should find check and return execpath
*/

char	*path_init(t_ltree *pos)
{
	char *ret;

	if (pos->ar_c < 1)
		return (NULL);
	if (!ft_strchr(*pos->ar_v, '/')) /* Builtin or $PATH case */
		ret = path_search(*pos->ar_v);
	else /* Execution path case */
	{
		if (access(*pos->ar_v, F_OK) == -1)
		{
			error_handler(COMMAND_NOT_FOUND |
				(ERR_NO_FILE << 9), *pos->ar_v);
			return (NULL);
		}
		else if (access(*pos->ar_v, X_OK) == -1)
		{
			error_handler(COMMAND_NON_EXECUTABLE, *pos->ar_v);
			return (NULL);
		}
		ret = ft_strdup(*pos->ar_v);
	}
	return (ret); /* ret could be NULL */
}
