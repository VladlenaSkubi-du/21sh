#include "shell21.h"
#include "parser.h"

/*
** First we check if the line from readline is not empty
** and after save the line to history in order to finish
** with readline-part,
** save the global parser structure,
** check quotes
** After we start to divide into blocks according to
** the grammar
*/

int		parser(char *line)
{
	if (g_prompt.prompt_func == main_prompt
		&& (line == NULL || line[0] == 0))
	{
		free(line);
		return (0);
	}
	add_to_history(line);
	g_pline.cmd = line;
	g_pline.len = ft_strlen(line) + 1;
	g_pline.tech = ft_make_techline(g_pline.cmd, g_pline.len);
	if (g_prompt.prompt_func == heredoc_prompt)
		gramlex_analysis_exec();
	else
	{
		if (start_quotes() != OUT)
			gramlex_analysis_exec();
	}
	clean_parser();
	return (0);
}

int		gramlex_analysis_exec(void)
{
	t_ltree		block;
	int			i;

	i = -1;
	ltree_init(&block);
	if (g_prompt.prompt_func != heredoc_prompt)
	{
		g_heredoc.list = NULL;
		g_start_list = NULL;
		while (++i <= g_pline.len + 1)
		{
			if (g_pline.tech[i] == SCOLON || g_pline.cmd[i] == '\0')
			{
				block.end = i;
				if (ft_block_add_to_list(&block, &g_start_list) == OUT)
					return (OUT);
				block.start = i + 1;
			}
		}
	}
	// ft_check_is_heredoc(0);
	return (0);
}

int		ltree_init(t_ltree *final)
{
	final->start = 0;
	final->end = 0;
	final->flags = 0;
	final->fd = NULL;
	final->token = NULL;
	final->envir = NULL;
	final->ar_v = NULL;
	final->err = NULL;
	final->err_i = 0;
	final->lcmd.cmd = NULL;
	final->lcmd.tech = NULL;
	final->lcmd.len = 0;
	return (0);
}