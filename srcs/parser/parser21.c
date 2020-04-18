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

int			parser(char *line)
{
	if (prepare_parser(line) == OUT)
		return (0);
	if (g_prompt.prompt_func == heredoc_prompt)
		check_heredoc_closure();
	else
	{
		if (start_quotes(g_pline->tech) != OUT)
		{
			slice_by_scolons();
			slice_by_pipes_cycle();
			gramlex_analysis();
			print_all_lists();
			free_parser_blocks(&g_grblks);
			// prepare_and_exec();
		}
	}
	clean_parser();
	return (0);
}

int			prepare_parser(char *line)
{
	if (g_prompt.prompt_func == main_prompt &&
		(line == NULL || line[0] == 0))
	{
		free(line);
		return (OUT);
	}
	if (g_prompt.prompt_func == main_prompt ||
			g_prompt.prompt_func == heredoc_prompt)
		g_pline = init_parser_line(line);
	add_to_history(line);
	// printf("g_cmd nul=%s\n", g_pline.cmd);
	// printf("techline cur:");
	// int count = -1;
	// while (++count < g_pline.len_tech)
	// 	printf("%3d", g_pline.tech[count]);
	// printf("\n");
	return (0);
}

/*
** First we create a list that consists of the t_pblks as
** content, its size as content_size and a pointer to NULL
** @tmp_pdata is needed for list initialization
** @ptr_block_cont is needed for convenient structure and
** its variable usage - it is just a pointer
** @new_block is a list that is created and added after the
** global @g_grblks - if only ';' is found
** the number of lists in @g_grblks depends on the number of
** ';' signes met
*/

int			slice_by_scolons(void)
{
	t_list		*new_block;
	t_pblks		*ptr_block_cont;
	int			i;

	g_grblks = create_new_list();
	new_block = g_grblks;
	i = -1;
	while (g_pline->tech[++i] != END_T)
		if (g_pline->tech[i] == SCOLON)
		{
			ptr_block_cont = new_block->content;
			ptr_block_cont->end = i;
			new_block = create_new_list();
			ft_lstadd_to_end(&g_grblks, new_block);
			ptr_block_cont = new_block->content;
			ptr_block_cont->beg = i + 1;
		}
	ptr_block_cont = new_block->content;
	ptr_block_cont->end = i;
	return (0);
}

int			slice_by_pipes_cycle(void)
{
	t_list		*runner;
	t_pblks		*ptr_block_cont;

	runner = g_grblks;
	while (runner)
	{
		ptr_block_cont = runner->content;
		slice_by_pipes(&runner, ptr_block_cont->beg,
			ptr_block_cont->end, ptr_block_cont);
		runner = runner->next;
	}
	return (0);
}

int			slice_by_pipes(t_list **current, int beg, int end,
				t_pblks *ptr_block_cont)
{
	t_list		*runner;
	t_list		*new_block;
	int			i;

	runner = *current;
	new_block = runner;
	i = beg - 1;
	while (++i < end)
		if (g_pline->tech[i] == PIPE)
		{
			ptr_block_cont = new_block->content;
			ptr_block_cont->flag |= PIPED_OUT;
			ptr_block_cont->end = i;
			new_block = create_new_list();
			ft_lstadd_after(&runner, new_block);
			runner = runner->next;
			ptr_block_cont = new_block->content;
			ptr_block_cont->flag |= PIPED_IN;
			ptr_block_cont->beg = i + 1;
		}
	ptr_block_cont = runner->content;
	ptr_block_cont->end = i;
	*current = runner;
	return (0);
}