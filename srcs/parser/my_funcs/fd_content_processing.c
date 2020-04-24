#include "shell21.h"
#include "parser.h"

t_list			*add_redir_to_block(t_fd fd_inout)
{
	t_list		*result;
	t_fd		*ptr_fd;

	result = ft_lstnew(NULL, 0);
	result->content = (t_fd*)ft_xmalloc(sizeof(t_fd));
	ptr_fd = result->content;
	ptr_fd->fd_in = fd_inout.fd_in;
	ptr_fd->fd_out = fd_inout.fd_out;
	ptr_fd->file = fd_inout.file;
	ptr_fd->flag = fd_inout.flag;
	return (result);
}

void			bzero_fd_redir(t_fd *fd_block)
{
	fd_block->fd_in = -1;
	fd_block->fd_out = -1;
	fd_block->file = NULL;
	fd_block->flag = 0;
}

int				free_fd_redir(t_pblks **current_cont)
{
	t_list		*runner_fd;
	t_list		*tmp_fd;
	t_fd		*ptr_fd;

	runner_fd = (*current_cont)->fd;
	while (runner_fd && runner_fd->next)
	{
		ptr_fd = runner_fd->content;
		if (ptr_fd->flag && (ptr_fd->flag & REDIRECTION_FD))
			runner_fd = runner_fd->next;
		else
			free_if_not_redir(&(*current_cont)->fd, &runner_fd, ptr_fd);
	}
	ptr_fd = runner_fd->content;
	if (ptr_fd->flag && (ptr_fd->flag & REDIRECTION_FD))
		return (0);
	tmp_fd = (*current_cont)->fd;
	while (tmp_fd->next != runner_fd)
		tmp_fd = tmp_fd->next;
	ptr_fd = tmp_fd->next->content;
	free_if_not_redir(NULL, &tmp_fd, ptr_fd);
	return (0);
}

int				free_if_not_redir(t_list **start_fd, t_list **runner_fd,
					t_fd *ptr_fd)
{
	free(ptr_fd->file);
	free(ptr_fd);
	if (start_fd && runner_fd && *runner_fd == *start_fd)
	{
		ft_lstfree_current(start_fd);
		*runner_fd = *start_fd;
	}
	else
		ft_lstfree_after(runner_fd);
	return (0);
}