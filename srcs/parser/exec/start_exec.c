#include "shell21.h"
#include "parser.h"

int			form_and_exec(t_pblks *pblk_cont)
{
	t_exec			*exec;

	exec = (t_exec*)ft_xmalloc(sizeof(t_exec));
	exec->argv = form_argv(pblk_cont->lcmd, &exec->argc);
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

int			start_exec(t_exec *exec) //28 строк
{
	pid_t			child_pid;
	char			*path;
	static int		pipe_prev;
	static int		pipe_next[2];

	path = NULL;
	child_pid = 0;
	save_streams(0);
	if (builtins_exec(exec, 0) == -1 && !(path = path_start_exec(exec)))
	{
		close(pipe_next[1]);
		save_streams(1);
		return (exec_clean(path, -1, 0));
	}
	(exec->flag & PIPED_IN) ? (pipe_prev = pipe_next[0]) : 0;
	if ((exec->flag & PIPED_OUT) && pipe(pipe_next) == -1)
		return (exec_clean(path, -1, "21sh: Pipe failed")); //через hadler
	redirection_exec(exec, 0);
	(exec->flag & PIPED_OUT) ? dup2(pipe_next[1], 1) : 0;
	(exec->flag & PIPED_IN) ? dup2(pipe_prev, 0) : 0;
	child_pid = 0;
	if (builtins_exec(exec, 1) == -1 &&
		cmd_fork_and_exec(exec, path, &child_pid) == -1)
		return (-1);
	(exec->flag & PIPED_OUT) ? close(pipe_next[1]) : 0;
	(exec->flag & PIPED_IN) ? close(pipe_prev) : 0;
	redirection_exec(exec, 1);
	return (exec_clean(path, WIFEXITED(child_pid) ?
		WEXITSTATUS(child_pid) : (-1), 0));
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
			if (flag && i < 3)
			{
				tmp = builtins_call_void(i);
				exit_status_variable(tmp);
			}
			else if (flag && i >= 3)
			{
				tmp = builtins_call(i, exec);
				exit_status_variable(tmp);
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
** consider changing architecture to... well, something else
*/

int			exec_clean(char *path, int exit_status, char *err_msg) //думаю, вообще может быть удалено
{
	if (path)
		exit_status_variable(exit_status);
	free(path);
	if (err_msg) //cделать вывод не через эту функцию, а через error_handler
		ft_putendl_fd(err_msg, STDERR_FILENO);  //если что, Леша должен был исправить в 42
	return (exit_status);
}

int			redirection_exec(t_exec *exec, int mode)
{
	t_list			*fd_runner;
	t_fd			*fd_cont;

	fd_runner = exec->fd;
	if (mode)
	{
		save_streams(1);
		return (0);
	}
	save_streams(0);
	while (fd_runner)
	{
		fd_cont = (t_fd*)fd_runner->content;
		if (fd_cont->flag != CLOSE_FD)
			dup2(fd_cont->fd_new, fd_cont->fd_old);
		else
		{
			close(fd_cont->fd_old);
		}
		fd_runner = fd_runner->next;
	}
	if (exec->flag == REDIR_SOFT)
		error_handler(SYNTAX_ERROR | ERR_REDIR_SOFT << 9, NULL);
	return (0);
}