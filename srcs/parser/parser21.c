/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser21.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:52:58 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:52:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		if (parser_if_heredoc() == OUT)
			return (OUT);
	}
	else
	{
		if (parser_if_mainprompt() == OUT)
			return (OUT);
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
	if (!(g_prompt.prompt_func == main_prompt ||
			g_prompt.prompt_func == heredoc_prompt))
		free(line);
	return (0);
}

int			parser_if_heredoc(void)
{
	if (check_heredoc_closure(g_pline) == OUT)
	{
		clean_parser();
		return (OUT);
	}
	prepare_and_exec();
	free_parser_blocks_all(&g_grblks);
	return (0);
}

int			parser_if_mainprompt(void)
{
	g_herenum = 0;
	if (start_quotes(g_pline->tech) != OUT)
	{
		slice_by_scolons();
		slice_by_pipes_cycle();
		gramlex_analysis();
		if (g_herenum > 0 && check_heredoc_closure(g_pline) == OUT)
		{
			clean_parser();
			return (OUT);
		}
			// print_all_lists(); //DELETE
		prepare_and_exec();
		free_parser_blocks_all(&g_grblks);
	}
	return (0);
}
