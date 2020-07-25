#include "shell21.h"
#include "parser.h"

t_list			*add_redir_to_block(t_fd fd_inout)
{
	t_list		*result;
	t_fd		*ptr_fd;

	result = ft_lstnew(NULL, 0);
	result->content = (t_fd*)ft_xmalloc(sizeof(t_fd));
	ptr_fd = (t_fd*)result->content;
	ptr_fd->fd_old = fd_inout.fd_old;
	ptr_fd->fd_new = fd_inout.fd_new;
	ptr_fd->file = fd_inout.file;
	ptr_fd->flag = fd_inout.flag;
	return (result);
}

void			bzero_fd_redir(t_fd *fd_block)
{
	fd_block->fd_old = -1;
	fd_block->fd_new = -1;
	fd_block->file = NULL;
	fd_block->flag = 0;
}

/*
** We go through the list of fd_blocks and free all the blocks
** without heredoc but from the head, so that all the
** lists with heredoc are in the beginning but only till RUNNER is not NULL:
** 1) HEAD/RUNNER/NOT::next (step 0) -> NOT::next -> HERE::next-> NOT::next
** 2) HEAD/RUNNER/NOT::next (step 0) -> HERE::next-> NOT::next
** 3) HEAD/RUNNER/HERE::next (step 0) -> HERE::next-> NOT::next
** 4) HEAD/HERE::next-> RUNNER/HERE::next (step 1) -> NOT::next
** 5) HEAD/HERE::next-> HERE::next (step 1) -> RUNNER/NOT::next
** Finally we have: HEAD/HERE::next-> HERE::next (step 1) -> NULL
** @last_here_fd rememberes last heredoc in order to make right
** next link
** if there were no heredocs, step will be 0 and there will be NULL
** left in the @current_cont->fd
*/

int				free_fdredir_except_heredoc(t_pblks **current_cont)
{
	t_list		*runner_fd;
	t_list		*last_here_fd;
	t_fd		*ptr_fd;
	int			step;

	runner_fd = (*current_cont)->fd;
	last_here_fd = runner_fd;
	step = 0;
	while (runner_fd)
	{
		ptr_fd = (t_fd*)runner_fd->content;
		if (ptr_fd->flag && (ptr_fd->flag & REDIRECTION_FD))
		{
			if (step == 0)
				(*current_cont)->fd = runner_fd;
			last_here_fd = runner_fd;
			runner_fd = runner_fd->next;
			step++;
		}
		else
			free_fd_not_heredoc(&runner_fd, &last_here_fd,
				ptr_fd, step);
	}
	(step == 0) ? (*current_cont)->fd = NULL : 0;
	return (0);
}

int				free_fd_not_heredoc(t_list **runner_fd,
					t_list **last_here_fd, t_fd *ptr_fd, int step)
{
	free_fdredir_content(runner_fd, ptr_fd);
	ft_lstfree_current(runner_fd);
	if (step == 0)
		*last_here_fd = *runner_fd;
	else
		(*last_here_fd)->next = *runner_fd;
	return (0);
}

int				free_fdredir_from(t_list **fd_from)
{
	t_list		*runner_fd;
	t_list		*delete_fd;
	t_fd		*ptr_fd;

	runner_fd = *fd_from;
	while (runner_fd)
	{
		delete_fd = runner_fd;
		runner_fd = runner_fd->next;
		ptr_fd = (t_fd*)delete_fd->content;
		free_fdredir_content(&delete_fd, ptr_fd);
		free(delete_fd);
		delete_fd = NULL;
	}
	return (0);
}
