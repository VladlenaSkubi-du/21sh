/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hard_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:43:50 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:48:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pblk_cont = (t_pblks*)pblk_hered->content;
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
	int			i;
	int			check;
	t_cmd		*new_ptr;

	ptr_lcmd = (*pblk_cont)->lcmd;
	i = -1;
	check = 0;
	while (++i < ptr_lcmd->len_tech - 1)
		if (ptr_lcmd->tech[i] != SPACE)
			check = 1;
	final = (check == 0) ? NULL : ft_strdup(ptr_lcmd->cmd);
	if (final == NULL && (*pblk_cont)->fd == NULL)
	{
		error_handler(SYNTAX_ERROR | (((*pblk_cont)->flag) ?
			ERR_PIPE << 9 : ERR_SCOLON << 9), NULL);
		return (OUT);
	}
	new_ptr = make_new_parser_line(final, ptr_lcmd->tech,
		0, ptr_lcmd->len_tech);
	free_parser_line(&(*pblk_cont)->lcmd);
	(*pblk_cont)->lcmd = new_ptr;
	return (0);
}

int			close_empty_fd_blocks(t_list **fd_runner)
{
	t_fd		*fd_cont;

	fd_cont = (t_fd*)(*fd_runner)->content;
	if (fd_cont->flag & REDIRECTION_FD)
		close(fd_cont->fd_new);
	return (0);
}
