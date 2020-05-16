#include "shell21.h"
#include "parser.h"

/*
** Here we should find check and return execpath
*/

char	*path_start_exec(t_exec *exec)
{
	char 			*ret;

	ret = NULL;
	if (exec->argc < 1)
		return (NULL);
	if (!ft_strchr(*exec->argv, '/')) /* Builtin or $PATH case */
	{
		if ((ret = search_cmd_exec(*exec->argv)) == 0)
			return (NULL);
	}
	else /* Execution path case */
	{
		if (access(*exec->argv, F_OK) == -1)
		{
			error_handler(COMMAND_NOT_FOUND |
				(ERR_NO_FILE << 9), *exec->argv);
			return (NULL);
		}
		else if (access(*exec->argv, X_OK) == -1)
		{
			error_handler(COMMAND_NON_EXECUTABLE, *exec->argv);
			return (NULL);
		}
		ret = ft_strdup(*exec->argv);
	}
	return (ret); /* ret could be NULL */
}

/*
** This is "just executable name case". We should check all directories in $PATH, find first match
** and check its accessibility
*/

char	*search_cmd_exec(char *name)
{
	char			**path_array;
	char			**to_clean;
	char			*ret;
	int				li;
	int				co;

	li = find_in_variables(g_env, &co, "PATH");
	if (li < 0 || ((path_array = ft_strsplit(&g_env[li][co], ':')) == NULL) ||
			path_array[0] == NULL)
		return (0);
	to_clean = path_array;
	while (*path_array)
	{
		ret = cmd_binary_path(*path_array, name);
		if (ret)
			break;
		path_array++;
	}
	ft_arrdel(to_clean);
	if (!ret)
		error_handler(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), name);
	return (ret);  /* Returns zero if we did not find anything */
}

char	*cmd_binary_path(char *env_path, char *name)
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
		if (ft_strcmp(entity->d_name, name) == 0)
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

char	*form_path(char *ret, char *env_path, char *name)
{
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
