
#include "shell21.h"
#include "parser.h"

int			gramlex_analysis(void)
{
	t_list		*runner;
	t_pblks		*ptr_block_cont;
	char		*tmp;

	runner = g_grblks;
	while (runner)
	{
		ptr_block_cont = runner->content;
		tmp = ft_strndup(g_pline->cmd + ptr_block_cont->beg,
			ptr_block_cont->end - ptr_block_cont->beg);
		ptr_block_cont->lcmd = init_parser_line(tmp);
		delete_quotes_from_line(ptr_block_cont);
		if (check_redirections(&runner) == OUT)
		{
			free_parser_blocks(&g_grblks);
			return (1);
		}
		runner = runner->next;
	}
	return (check_heredoc_closure());
}

int			delete_quotes_from_line(t_pblks *ptr_block_cont)
{
	int			i;
	t_cmd		*ptr_lcmd;

	i = 0;
	ptr_lcmd = ptr_block_cont->lcmd;
	while (ptr_lcmd->tech[i] != END_T)
	{
		if (ptr_lcmd->tech[i] == SQUOTE || ptr_lcmd->tech[i] == DQUOTE)
		{
			delete_symbols_from_parser_line(&ptr_lcmd, i + 1, -1);
			while (ptr_lcmd->tech[i] != SQUOTE &&
					ptr_lcmd->tech[i] != DQUOTE && ptr_lcmd->tech[i] != END_T)
				i++;
			delete_symbols_from_parser_line(&ptr_lcmd, i + 1, -1);
		}
		if (ptr_lcmd->tech[i] == ENTER)
			delete_symbols_from_parser_line(&ptr_lcmd, i + 1, -1);
		i++;
	}
	ptr_block_cont->beg = -1;
	ptr_block_cont->end = -1;
	return (0);
}
