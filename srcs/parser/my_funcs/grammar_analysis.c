
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
		current_cont = runner->content;
		tmp = ft_strndup(g_pline->cmd + current_cont->beg,
			current_cont->end - current_cont->beg);
		current_cont->lcmd = init_parser_line(tmp);
		ptr_lcmd = current_cont->lcmd;
		delete_quotes_from_line(&current_cont, &ptr_lcmd);
		if (check_redirections(&current_cont, &ptr_lcmd) == OUT)
		{
			if (current_cont->err & REDIR_HARD)
			{
				free_pblocks_except_heredoc(&g_grblks);
				return (OUT);
			}
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
			delete_symbols_from_parser_line(ptr_lcmd, i + 1, -1);
			while (i < (*ptr_lcmd)->len_tech &&
					(*ptr_lcmd)->tech[i] != SQUOTE &&
					(*ptr_lcmd)->tech[i] != DQUOTE)
				i++;
			delete_symbols_from_parser_line(ptr_lcmd, i + 1, -1);
		}
		if ((*ptr_lcmd)->tech[i] == ENTER)
			delete_symbols_from_parser_line(ptr_lcmd, i + 1, -1);
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