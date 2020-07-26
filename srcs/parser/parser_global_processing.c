/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_global_processing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:50:44 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:52:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

void			print_all_lists(void)
{
	t_list		*runner;
	t_pblks		*ptr_block_cont;
	t_cmd		*ptr_lcmd;

	if (g_grblks == NULL)
		ft_printf("empty grammar blocks\n");
	runner = g_grblks;
	while (runner)
	{
		ptr_block_cont = (t_pblks*)runner->content;
		ft_printf("NEW LIST\n******************************\n");
		ft_printf("beg = %d, end = %d\n", ptr_block_cont->beg,
			ptr_block_cont->end);
		ptr_lcmd = ptr_block_cont->lcmd;
		ft_printf("Lcmd: %s\nTechlen: %d\n", ptr_lcmd->cmd, ptr_lcmd->len_tech);
		(ptr_block_cont->fd) ? print_fd_blocks(ptr_block_cont) : 0;
		ft_printf("******************************\n");
		(ptr_block_cont->flag & PIPED_IN) ? ft_printf("pipe in\n") : 0;
		(ptr_block_cont->flag & PIPED_OUT) ? ft_printf("pipe out\n") : 0;
		(ptr_block_cont->err & REDIR_HARD) ? ft_printf("redir_hard\n") : 0;
		(ptr_block_cont->err & REDIR_SOFT) ? ft_printf("redir_soft\n") : 0;
		ft_printf("______________________________\n\n");
		runner = runner->next;
	}
}

void			print_fd_blocks(t_pblks *ptr_block_cont)
{
	t_list		*fd_runner;
	t_fd		*ptr_fd;

	fd_runner = ptr_block_cont->fd;
	while (fd_runner)
	{
		ptr_fd = (t_fd*)fd_runner->content;
		ft_printf("******************************\n");
		ft_putstr("Fd_old is ");
		ft_putnbr(ptr_fd->fd_old);
		ft_putstr("\nFd_new is ");
		ft_putnbr(ptr_fd->fd_new);
		ft_printf("\nFd_file is %s\n", ptr_fd->file);
		if (ptr_fd->flag)
		{
			(ptr_fd->flag & CLOSE_FD) ? ft_printf("close fd\n") : 0;
			(ptr_fd->flag & CREATE_FD) ? ft_printf("create file\n") : 0;
			(ptr_fd->flag & OPEN_FD) ? ft_printf("open file\n") : 0;
			(ptr_fd->flag & REDIRECTION_FD) ? ft_printf("redirection\n") : 0;
		}
		fd_runner = fd_runner->next;
	}
}

void			free_fdredir_content(t_list **runner_fd,
					t_fd *ptr_fd)
{
	free(ptr_fd->file);
	ptr_fd->file = NULL;
	free((*runner_fd)->content);
	(*runner_fd)->content = NULL;
}

void			free_pblock_content(t_pblks **ptr_cont)
{
	free_parser_line(&(*ptr_cont)->lcmd);
	free(*ptr_cont);
	*ptr_cont = NULL;
}

t_cmd			*make_new_parser_line(char *line, char *techline,
					int start, int end)
{
	t_cmd		*parser;
	int			len_cmd;
	int			i;

	parser = (t_cmd*)ft_xmalloc(sizeof(t_cmd));
	parser->cmd = line;
	len_cmd = ft_strlen(parser->cmd);
	parser->tech = (char*)ft_xmalloc(len_cmd + 2);
	i = -1;
	while (++i < end - start)
	{
		if (techline[start + i] == TEXT)
			parser->tech[i] = TEXT;
		else
			parser->tech[i] = get_tech_num(parser->cmd[i]);
	}
	parser->tech[i] = END_T;
	parser->len_tech = len_cmd + 1;
	return (parser);
}
