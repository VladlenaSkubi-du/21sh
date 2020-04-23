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
	while (runner_fd)
	{
		tmp_fd = runner_fd;
		runner_fd = runner_fd->next;
		ptr_fd = tmp_fd->content;
		free(ptr_fd->file);
		free(ptr_fd);
		free(tmp_fd);
		tmp_fd = NULL;
	}
	(*current_cont)->fd = NULL;
	return (0);
}