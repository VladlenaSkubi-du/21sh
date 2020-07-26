
#include "shell21.h"
#include "parser.h"

int			gramlex_analysis(void)
{
	t_list		*runner;
	t_pblks		*current_cont;
	t_cmd		*ptr_lcmd;
	char		*tmp;

	runner = g_grblks;
	while (runner)
	{
		current_cont = (t_pblks*)runner->content;
		tmp = ft_strndup(g_pline->cmd + current_cont->beg,
			current_cont->end - current_cont->beg);
		free_parser_line(&current_cont->lcmd);
		// current_cont->lcmd = init_parser_line(tmp);
		current_cont->lcmd = make_new_parser_line(tmp, g_pline->tech,
			current_cont->beg, current_cont->end),
		ptr_lcmd = current_cont->lcmd;
		delete_quotes_from_line(&current_cont, &ptr_lcmd);
		if (check_redirections(&current_cont, &ptr_lcmd) == OUT &&
				current_cont->err & REDIR_HARD)
		{
			free_pblocks_except_heredoc(&g_grblks);
			return (shift_harderror_to_last_heredoc());
		}
		runner = runner->next;
	}
	return (0);
}

int			delete_quotes_from_line(t_pblks **current_cont,
				t_cmd **ptr_lcmd)
{
	int			i;

	i = 0;
	while (i < (*ptr_lcmd)->len_tech)
	{
		if ((*ptr_lcmd)->tech[i] == SQUOTE || (*ptr_lcmd)->tech[i] == DQUOTE)
		{
			delete_or_insert_to_pline(ptr_lcmd, i + 1, -1);
			while (i < (*ptr_lcmd)->len_tech &&
					(*ptr_lcmd)->tech[i] != SQUOTE &&
					(*ptr_lcmd)->tech[i] != DQUOTE)
				i++;
			delete_or_insert_to_pline(ptr_lcmd, i + 1, -1);
		}
		if ((*ptr_lcmd)->tech[i] == ENTER)
			delete_or_insert_to_pline(ptr_lcmd, i + 1, -1);
		i++;
	}
	(*current_cont)->beg = -1;
	(*current_cont)->end = -1;
	return (0);
}

/*
** Errors to fly out of the whole cmd-line: nothing to redirect into
** All the other errors will not influence other blocks
*/

int			check_redirections(t_pblks **current_cont,
				t_cmd **ptr_lcmd)
{
	int			i;

	i = -1;
	while (++i < (*ptr_lcmd)->len_tech)
	{
		if ((*ptr_lcmd)->tech[i] == LTHAN)
		{
			if (redir_heredoc(current_cont, ptr_lcmd, &i) == OUT)
				return (OUT);
			if (redir_inand(current_cont, ptr_lcmd, &i) == OUT)
				return (OUT);
			if (redir_in(current_cont, ptr_lcmd, &i) == OUT)
				return (OUT);
		}
		else if ((*ptr_lcmd)->tech[i] == GTHAN)
		{
			if (redir_outout(current_cont, ptr_lcmd, &i) == OUT)
				return (OUT);
			if (redir_outand(current_cont, ptr_lcmd, &i) == OUT)
				return (OUT);
			if (redir_out(current_cont, ptr_lcmd, &i) == OUT)
				return (OUT);
		}
	}
	return (0);
}

int			redir_heredoc(t_pblks **current_cont,
							t_cmd **ptr_lcmd, int *i)
{
	t_list			*new_fd;
	t_fd			fd_inout;

	bzero_fd_redir(&fd_inout);
	if ((*ptr_lcmd)->tech[*i] == LTHAN && (*ptr_lcmd)->tech[*i + 1] == LTHAN)
	{
		if (find_fdbefore_redir(ptr_lcmd, &fd_inout, i) == OUT)
			return (activate_redir_error(current_cont, fd_inout));
		(fd_inout.fd_old == -1) ? fd_inout.fd_old = STDIN_FILENO : 0;
		delete_or_insert_to_pline(ptr_lcmd, *i + 2, -2);
		if (find_fdafter_redir(ptr_lcmd, &fd_inout, i) == OUT)
			return (activate_redir_error(current_cont, fd_inout));
		fd_inout.flag |= REDIRECTION_FD;
		g_herenum++;
		fd_inout.fd_new = ft_tmpfile();
		new_fd = add_redir_to_block(fd_inout);
		ft_lstadd_to_end(&(*current_cont)->fd, new_fd);
		if (*i == 0)
			*i = -1;
	}
	return (0);
}

int			shift_harderror_to_last_heredoc(void)
{
	t_list		*runner;
	t_pblks		*current_cont;
	t_list		*last_heredoc;

	runner = g_grblks;
	while (runner)
	{
		current_cont = (t_pblks*)runner->content;
		if (current_cont->fd)
			last_heredoc = runner;
		runner = runner->next;
	}
	current_cont = (t_pblks*)last_heredoc->content;
	current_cont->err |= REDIR_HARD;
	return (OUT);
}
