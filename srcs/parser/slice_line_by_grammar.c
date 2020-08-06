/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_line_by_grammar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:58:38 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/06 17:17:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

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
	while (++i < g_pline->len_tech - 1)
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
	ptr_block_cont->end = i - 1;
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
