#include "shell21.h"
#include "parser.h"

/*
** Delete pipe process and simplify, leaving only dealing with EXECPATH
*/

int		std_save(int mode)
{
	static int	save[3];

	if (!mode)
	{
		save[0] = dup(STDIN_FILENO);
		save[1] = dup(STDOUT_FILENO);
		save[2] = dup(STDERR_FILENO);
	}
	else
	{
		dup2(save[0], STDIN_FILENO);
		dup2(save[1], STDOUT_FILENO);
		dup2(save[2], STDERR_FILENO);
	}
	return (0);
}

int		fork_and_exec(t_ltree *pos, char *path, pid_t *child_pid)
{
	*child_pid = fork();
	if (!*child_pid)
	{
		if (execve(path, pos->ar_v, pos->envir) == -1) //TODO испрвить на все виды очисток
			exit(-1);
	}
	else if (*child_pid < 0)
		return (exec_clean(path, -1, "21sh: Fork failed"));
	wait(child_pid);
	return (0);
}

int		exec_core(t_ltree *pos)
{
	pid_t			child_pid;
	char			*path;
	static int		pipe_prev;
	static int		pipe_next[2];

	path = NULL;
	child_pid = 0;
	if (ft_builtins_check(pos, 0) == -1 && !(path = path_init(pos)))
	{
		close(pipe_next[1]);
		return (exec_clean(path, -1, 0));
	}
	(pos->flags & PIPED_IN) ? (pipe_prev = pipe_next[0]) : 0;
	if ((pos->flags & PIPED_OUT) && pipe(pipe_next) == -1)
		return (exec_clean(path, -1, "21sh: Pipe failed"));
	std_save(0);
	(pos->flags & PIPED_OUT) ? dup2(pipe_next[1], 1) : 0;
	(pos->flags & PIPED_IN) ? dup2(pipe_prev, 0) : 0;
	fd_list_process(pos);
	child_pid = 0;
	if (ft_builtins_check(pos, 1) == -1 &&
		fork_and_exec(pos, path, &child_pid) == -1)
		return (-1);
	(pos->flags & PIPED_OUT) ? close(pipe_next[1]) : 0;
	(pos->flags & PIPED_IN) ? close(pipe_prev) : 0;
	std_save(1);
	return (exec_clean(path, WIFEXITED(child_pid) ? \
	WEXITSTATUS(child_pid) : (-1), 0));
}
