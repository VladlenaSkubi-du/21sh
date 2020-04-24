#include "shell21.h"
#include "parser.h"

int			redir_heredoc(t_pblks **current_cont,
							t_cmd **ptr_lcmd, int *i)
{
	t_list	*new_fd;
	t_fd	fd_inout;

	bzero_fd_redir(&fd_inout);
	if ((*ptr_lcmd)->tech[*i] == LTHAN && (*ptr_lcmd)->tech[*i + 1] == LTHAN)
	{
		if (find_fdbefore_redir(ptr_lcmd, &fd_inout, i) == OUT)
			return (activate_redir_error(current_cont, fd_inout));
		(fd_inout.fd_out == -1) ? fd_inout.fd_out = STDIN_FILENO : 0;
		delete_symbols_from_parser_line(ptr_lcmd, *i + 2, -2);
		if (find_fdafter_redir(ptr_lcmd, &fd_inout, i) == OUT)
			return (activate_redir_error(current_cont, fd_inout));
		fd_inout.flag |= REDIRECTION_FD;
		fd_inout.fd_in = ft_tmpfile();
		new_fd = add_redir_to_block(fd_inout);
		ft_lstadd_to_end(&(*current_cont)->fd, new_fd);
		if (*i == 0)
			*i = -1;
	}
	return (0);
}

int			check_heredoc_closure(void)
{
	return (0);
}