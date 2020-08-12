/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:52:54 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/12 21:05:18 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

int			form_and_exec(t_pblks *pblk_cont)
{
	t_exec			*exec;
	int				len;

	exec = (t_exec*)ft_xmalloc(sizeof(t_exec));
	len = ARGV_LOCAL;
	exec->argv = form_argv(pblk_cont->lcmd, &exec->argc, len);
	exec->flag = pblk_cont->flag;
	if (pblk_cont->err & REDIR_SOFT)
		exec->flag |= REDIR_SOFT;
	exec->fd = pblk_cont->fd;
	start_exec(exec);
	ft_arrdel(exec->argv);
	free(exec);
	exec = NULL;
	return (0);
}

int			start_exec(t_exec *exec)
{
	pid_t			child_pid;
	char			*path;
	static int		fd[3];

	// int i=-1;
	// while (exec->argv[++i])
	//  	printf("olo>>%s\n", exec->argv[i]);
	
	// print_all_lists();
	path = NULL;
	child_pid = 0;
	if (builtins_exec(exec, 0) == -1 && !(path = path_start_exec(exec)))
		return (clean_exec(&path, 0));
	(exec->flag & PIPED_IN) ? fd[0] = fd[1] : 0;
	if ((exec->flag & PIPED_OUT) && pipe(&fd[1]) == -1)
		return (clean_exec(&path, PIPE_FAIL));
	save_streams(0);
	if ((exec->flag & PIPED_OUT) || (exec->flag & PIPED_IN))
		cmd_fork_and_exec(exec, path, &child_pid, fd);
	else if (builtins_exec(exec, 1) == -1)
		cmd_fork_and_exec(exec, path, &child_pid, fd);
	if (exec->flag & PIPED_OUT)
		close(fd[2]);
	if (exec->flag & PIPED_IN)
		close(fd[0]);
	redirection_exec(exec, 1);
	return (clean_exec(&path, (WIFEXITED(child_pid) ?
		WEXITSTATUS(child_pid) : EXEC_FAIL)));
}

int			clean_exec(char **path, int exit_status)
{
	free(*path);
	(*path) = NULL;
	if (exit_status == PIPE_FAIL)
		error_handler(PIPE_FAIL, NULL);
	else if (exit_status == FORK_FAIL)
		error_handler(FORK_FAIL, NULL);
	exit_status = btin_return_exit_status();
	return (exit_status);
}

int			builtins_exec(t_exec *exec, int flag)
{
	int				i;
	int				tmp;

	i = 0;
	if (exec->argv == NULL)
		return (-1);
	while (g_builtins[i])
	{
		if (!ft_strcmp(exec->argv[0], g_builtins[i]))
		{
			if (flag && i < 1)
			{
				if (!(exec->flag & PIPED_IN) && !(exec->flag & PIPED_OUT))
					redirection_exec(exec, 0);
				tmp = builtins_call_void(i);
				exit_status_variables(tmp);
			}
			else if (flag && i >= 1)
			{
				if (!(exec->flag & PIPED_IN) && !(exec->flag & PIPED_OUT))
					redirection_exec(exec, 0);
				tmp = builtins_call(i, exec);
				exit_status_variables(tmp);
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int			redirection_exec(t_exec *exec, int mode)
{
	t_list			*fd_runner;
	t_fd			*fd_cont;

	if (mode)
	{
		save_streams(1);
		return (0);
	}
	fd_runner = exec->fd;
	while (fd_runner)
	{
		fd_cont = (t_fd*)fd_runner->content;
		if (fd_cont->flag != CLOSE_FD)
			dup2(fd_cont->fd_new, fd_cont->fd_old);
		else
			close(fd_cont->fd_old);
		fd_runner = fd_runner->next;
	}
	return (0);
}
