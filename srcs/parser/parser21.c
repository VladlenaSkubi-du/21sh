#include "shell21.h"
#include "parser.h"

int		parser(char *line)
{
	if (g_prompt.prompt_func == main_prompt
		&& (line == NULL || line[0] == 0))
	{
		free(line);
		return (0);
	}
	g_cmd = line;
	g_cmd_size = ft_strlen(g_cmd);
	ft_get_techline(g_cmd, &g_techline);
	add_to_history(g_cmd);
	g_hist.counter = g_hist.last + 1;
	pars_lex_exec();
	return (0);
}

int		pars_lex_exec(void)
{
	init_builtins();
	if (g_prompt.prompt_func != heredoc_prompt)
		if (nullify(&g_techline.line, g_cmd_size) == OUT)
		{
			clean_parser21();
			return (0);
		}
	ft_slice_fg();
	clean_parser21();
	return (0);
}

/*
** Function to check if find char is in use or just text
*/

char	get_tech_num(char check)
{
	char	*base;
	int		i;

	base = " \\;&\"\'()[]{}$~|><*=\n#\t";
	i = 0;
	while (base[i])
	{
		if (base[i] == check)
		{
			if (i == 21)
				return (2);
			else			
				return (i + 2);
		}
		i++;
	}
	if (check == EOF)
		return (EOF);
	return (1);
}

int		ft_get_techline(char *cmd, t_tech *result)
{
	size_t	i;

	i = 0;
	result->line = (char *)ft_xmalloc(ft_strlen(cmd) + 2);
	while (cmd[i])
	{
		result->line[i] = get_tech_num(cmd[i]);
		i++;
	}
	result->line[i] = END_T;
	result->len = i;
	result->alloc_size = i + 2;
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
	final->l_cmd = NULL;
	final->l_tline.line = NULL;
	return (0);
}