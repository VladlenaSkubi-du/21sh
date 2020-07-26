/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_blocks_processing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:50:26 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:50:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

t_list			*create_new_list(void)
{
	t_list		*result;
	t_pblks		*ptr_cont;

	result = ft_lstnew(NULL, 0);
	result->content = (t_pblks*)ft_xmalloc(sizeof(t_pblks));
	ptr_cont = (t_pblks*)result->content;
	ptr_cont->lcmd = (t_cmd*)ft_xmalloc(sizeof(t_cmd));
	bzero_grammar_block((t_pblks*)result->content);
	return (result);
}

void			bzero_grammar_block(t_pblks *block)
{
	t_cmd		*ptr_lcmd;

	ptr_lcmd = block->lcmd;
	ptr_lcmd->cmd = NULL;
	ptr_lcmd->tech = NULL;
	ptr_lcmd->len_tech = 0;
	block->beg = 0;
	block->end = 0;
	block->fd = NULL;
	block->err = 0;
	block->flag = 0;
}

int				free_pblocks_except_heredoc(t_list **head)
{
	t_list		*runner_blk;
	t_list		*last_here_blk;
	t_pblks		*ptr_cont;
	int			step;

	runner_blk = *head;
	last_here_blk = runner_blk;
	step = 0;
	while (runner_blk)
	{
		ptr_cont = (t_pblks*)runner_blk->content;
		if (ptr_cont->fd)
		{
			(step == 0) ? *head = runner_blk : 0;
			last_here_blk = runner_blk;
			runner_blk = runner_blk->next;
			step++;
		}
		else
			free_pblock_not_heredoc(&runner_blk, &last_here_blk, step);
	}
	(step == 0) ? *head = NULL : 0;
	return (0);
}

int				free_pblock_not_heredoc(t_list **runner_blk,
					t_list **last_here_blk, int step)
{
	t_pblks		*ptr_cont;

	ptr_cont = (t_pblks*)(*runner_blk)->content;
	free_pblock_content(&ptr_cont);
	ft_lstfree_current(runner_blk);
	if (step == 0)
		*last_here_blk = *runner_blk;
	else
		(*last_here_blk)->next = *runner_blk;
	return (0);
}

int				free_parser_blocks_all(t_list **head)
{
	t_list		*runner_blk;
	t_list		*delete_blk;
	t_list		*delete_fd;
	t_pblks		*ptr_cont;

	runner_blk = *head;
	while (runner_blk)
	{
		delete_blk = runner_blk;
		runner_blk = runner_blk->next;
		ptr_cont = (t_pblks*)delete_blk->content;
		delete_fd = ptr_cont->fd;
		free_fdredir_from(&delete_fd);
		ptr_cont->fd = NULL;
		free_pblock_content(&ptr_cont);
		delete_blk->content = NULL;
		free(delete_blk);
		delete_blk = NULL;
	}
	*head = NULL;
	return (0);
}
