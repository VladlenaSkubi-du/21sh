#include "shell21.h"
#include "parser.h"

int			redir_inand(t_pblks **current_cont,
							t_cmd **ptr_lcmd, int *i)
{
	t_list	*new_fd;
	t_fd	fd_inout;
	int		tmp;

	bzero_fd_block(&fd_inout);
	if ((*ptr_lcmd)->tech[*i] == LTHAN && (*ptr_lcmd)->tech[*i + 1] == AND)
	{
		if (find_fdbefore_redir(ptr_lcmd, &fd_inout, *i) == OUT)
			return (activate_redir_error(current_cont, fd_inout.flag));
		(fd_inout.fd_out == -1) ? fd_inout.fd_out = STDIN_FILENO : 0;
		delete_symbols_from_parser_line(ptr_lcmd, *i + 2, -2);
		if ((*ptr_lcmd)->cmd[*i] == '-')
		{
			fd_inout.flag |= CLOSE;
			delete_symbols_from_parser_line(ptr_lcmd, *i + 1, -1);
			new_fd = add_redir_to_block(current_cont, fd_inout);
			ft_lstadd_after(&(*current_cont)->fd, new_fd);
			return (0);
		}
		if (find_fdafter_redir(ptr_lcmd, &fd_inout, *i, 'n') == OUT)
			return (activate_redir_error(current_cont, fd_inout.flag));
	}
	return (0);
}

int			redir_in(t_pblks **current_cont,
				t_cmd **ptr_lcmd, int *i)
{
	t_fd	fd_inout;
	char	*file_name;

	if ((*ptr_lcmd)->tech[*i] == LTHAN && (*ptr_lcmd)->tech[*i + 1] != PIPE)
	{

	}
	return (0);
}

int			redir_outout(t_pblks **current_cont,
				t_cmd **ptr_lcmd, int *i)
{
	t_fd	fd_inout;
	char	*file_name;

	if ((*ptr_lcmd)->tech[*i] == GTHAN && (*ptr_lcmd)->tech[*i + 1] == GTHAN)
	{

	}
	return (0);
}

int			redir_outand(t_pblks **current_cont,
				t_cmd **ptr_lcmd, int *i)
{
	t_fd	fd_inout;
	char	*file_name;

	if ((*ptr_lcmd)->tech[*i] == GTHAN && (*ptr_lcmd)->tech[*i + 1] == AND)
	{

	}
	return (0);
}

int			redir_out(t_pblks **current_cont,
				t_cmd **ptr_lcmd, int *i)
{
	t_fd	fd_inout;
	char	*file_name;

	if ((*ptr_lcmd)->tech[*i] == GTHAN && (*ptr_lcmd)->tech[*i + 1] != PIPE)
	{
		
	}
	return (0);
}