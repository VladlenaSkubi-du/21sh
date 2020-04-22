#include "shell21.h"
#include "parser.h"

int			redir_heredoc(t_pblks **current_cont,
							t_cmd **ptr_lcmd, int *i)
{
	t_fd	fd_inout;
	char	*file_name;

	if ((*ptr_lcmd)->tech[*i] == LTHAN && (*ptr_lcmd)->tech[*i + 1] == LTHAN)
	{

	}
	return (0);
}

int			check_heredoc_closure(void)
{
	return (0);
}