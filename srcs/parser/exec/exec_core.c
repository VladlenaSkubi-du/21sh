#include "shell21.h"
#include "parser.h"

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
