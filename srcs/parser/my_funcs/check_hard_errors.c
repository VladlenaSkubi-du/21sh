#include "shell21.h"
#include "parser.h"

int			check_hard_errors(void)
{
	t_list		*pblk_hered;
	t_list		*fd_runner;
	t_pblks		*pblk_cont;

	pblk_hered = g_grblks;
	while (pblk_hered)
	{
		pblk_cont = pblk_hered->content;
		if (check_empty_pblock(&pblk_cont) == OUT)
			return (OUT);
		fd_runner = pblk_cont->fd;
		while (fd_runner)
		{
			if (pblk_cont->err & REDIR_HARD)
			{
				close_empty_fd_blocks(&fd_runner);
				error_handler(SYNTAX_ERROR | ERR_REDIR << 9, NULL);
				return (OUT);
			}
			fd_runner = fd_runner->next;
		}
		pblk_hered = pblk_hered->next;
	}
	return (0);
}

int			check_empty_pblock(t_pblks **pblk_cont)
{
	char		*final;
	t_cmd		*ptr_lcmd;

	ptr_lcmd = (*pblk_cont)->lcmd;
	final = ft_strtrim(ptr_lcmd->cmd);
	if ((final == NULL || final[0] == 0) &&
			(*pblk_cont)->fd == NULL)
	{
		if ((*pblk_cont)->flag)
			error_handler(SYNTAX_ERROR | ERR_PIPE << 9, NULL);
		else
			error_handler(SYNTAX_ERROR | ERR_SCOLON << 9, NULL);
		free(final);
		return (OUT);
	}
	free_parser_line(&(*pblk_cont)->lcmd);
	ptr_lcmd = init_parser_line(final);
	(*pblk_cont)->lcmd = ptr_lcmd;
	return (0);
}

int			close_empty_fd_blocks(t_list **fd_runner)
{
	t_fd		*fd_cont;

	fd_cont = (*fd_runner)->content;
	if (fd_cont->flag & REDIRECTION_FD)
		close(fd_cont->fd_new);
	return (0);
}