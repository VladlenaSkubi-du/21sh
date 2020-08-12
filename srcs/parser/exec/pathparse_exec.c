/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathparse_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:53:47 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/12 22:03:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

/*
** Here we should find check and return execpath
** If the command does not exist or is not executable,
** return will be NULL;
*/

char	*path_start_exec(t_exec *exec)
{
	char			*path;

	path = NULL;
	if (exec->argc < 1)
		return (NULL);
	if (!ft_strchr(*exec->argv, '/'))
		path = search_cmd_exec(*exec->argv);
	else
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
		path = ft_strdup(*exec->argv);
	}
	return (path);
}

/*
** This is "just executable name case". We should check
** all directories in $PATH, find first match
** and check its accessibility
*/

char	*search_cmd_exec(char *name)
{
	char			**path_dirs;
	char			*path;
	char			*path_env;
	int				i;

	path_env = find_env("PATH");
	if (!(path_env && (path_dirs = ft_strsplit(path_env, ':')) && path_dirs[0]))
	{
		error_handler(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), name);
		return (NULL);
	}
	i = -1;
	while (path_dirs[++i])
	{
		path = cmd_binary_path(path_dirs[i], name);
		if (path)
			break ;
	}
	ft_arrdel(path_dirs);
	if (path == NULL)
	{
		error_handler(COMMAND_NOT_FOUND | (ERR_COMMAND << 9), name);
		return (NULL);
	}
	return (path);
}

/*
** We plus two to a @path string because we need to
** add "/" and a NULL
*/

char	*cmd_binary_path(char *cmd_dir, char *name)
{
	struct dirent	*entity;
	char			*path;
	DIR				*directory;

	path = NULL;
	directory = opendir(cmd_dir);
	if (directory == NULL)
		return (NULL);
	while ((entity = readdir(directory)))
	{
		if (ft_strcmp(entity->d_name, name) == 0)
		{
			path = form_absolute_path(cmd_dir, name);
			if (path)
				break ;
		}
	}
	closedir(directory);
	return (path);
}

char	*form_absolute_path(char *cmd_dir, char *name)
{
	char			*path;

	path = (char*)ft_xmalloc(ft_strlen(cmd_dir) + ft_strlen(name) + 2);
	ft_strcpy(path, cmd_dir);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	if (access(path, X_OK) == -1)
	{
		error_handler(COMMAND_NON_EXECUTABLE, name);
		free(path);
		return (NULL);
	}
	return (path);
}

int		builtins_exec_exec_init(t_exec *exec, int *i, int flag)
{
	int				j;
	int				tmp;

	j = *i;
	if (!(exec->flag & PIPED_IN) && !(exec->flag & PIPED_OUT))
		redirection_exec(exec, 0);
	if (flag == 0)
		tmp = builtins_call_void(j);
	else
		tmp = builtins_call(j, exec);
	exit_status_variables(tmp);
	*i = j;
	return (0);
}
