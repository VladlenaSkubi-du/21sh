#include "shell21.h"
#include "parser.h"

//int count
// printf("g_cmd nul=%s\n", g_pline->cmd);//печать для проверки
		// printf("techline cur:");
		// count = -1;
		// while (++count <= g_pline->len_tech)
		// 	printf("%3d", g_pline->tech[count]);
		// printf("\n");

	// printf("g_cmd nul=%s - len=%d\n", (*ptr_lcmd)->cmd, (*ptr_lcmd)->len_tech);//печать для проверки
	// printf("techline cur:");
	// int count = -1;
	// while (++count < (*ptr_lcmd)->len_tech)
	// 	printf("%3d", (*ptr_lcmd)->tech[count]);
	// printf("\n");

	// runner_fd = start_fd;
	// while (runner_fd)
	// {
	// 	ptr_fd = runner_fd->content;
	// 	printf("******************************\n");
	// 	printf("Fd_in is %d\n", ptr_fd->fd_in);
	// 	printf("Fd_out is %d\n", ptr_fd->fd_out);
	// 	printf("Fd_file is %s\n", ptr_fd->file);
	// 	if (ptr_fd->flag)
	// 	{
	// 		(ptr_fd->flag & CLOSE_FD) ? printf("close fd\n") : 0;
	// 		(ptr_fd->flag & CREATE_FD) ? printf("create file\n") : 0;
	// 		(ptr_fd->flag & OPEN_FD) ? printf("open file\n") : 0;
	// 		(ptr_fd->flag & REDIRECTION_FD) ? printf("redirection\n") : 0;
	// 	}
	// 	runner_fd = runner_fd->next;
	// }

static void		print_fd_blocks(t_pblks	*ptr_block_cont)
{
	t_list		*fd_runner;
	t_fd		*ptr_fd;

	fd_runner = ptr_block_cont->fd;
	while (fd_runner)
	{
		ptr_fd = fd_runner->content;
		ft_printf("******************************\n");
		// ft_printf("Fd_in %d\nFd_out %d\n", ptr_fd->fd_in, ptr_fd->fd_out);
		ft_putstr("Fd_in is ");
		ft_putnbr(ptr_fd->fd_in);
		ft_putstr("\nFd_out is ");
		ft_putnbr(ptr_fd->fd_out);
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

void			print_all_lists(void)
{
	t_list		*runner;
	t_pblks		*ptr_block_cont;
	t_cmd		*ptr_lcmd;
	int			end;

	runner = g_grblks;
	while (runner)
	{
		ptr_block_cont = runner->content;
		end = ptr_block_cont->end -
			((g_pline->tech[ptr_block_cont->end] == END_T) ? 1 : 0);
		ft_printf("NEW LIST\n******************************\n");
		ft_printf("beg = %d, end = %d\n", ptr_block_cont->beg, end);
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

t_cmd			*init_parser_line(char *line)
{
	t_cmd		*parser;
	int			len_cmd;

	parser = (t_cmd*)ft_xmalloc(sizeof(t_cmd));
	parser->cmd = line;
	len_cmd = ft_strlen(parser->cmd);
	parser->tech = ft_make_techline(parser->cmd, len_cmd);
	parser->len_tech = len_cmd + 1;
	return (parser);
}

void			free_parser_line(t_cmd **pline)
{
	free((*pline)->cmd);
	(*pline)->cmd = NULL;
	free((*pline)->tech);
	(*pline)->tech = NULL;
	free(*pline);
	*pline = NULL;
}

int				delete_symbols_from_parser_line(t_cmd **pline,
					int i, int num)
{
	str_shift((*pline)->cmd + i, num);
	str_shift((*pline)->tech + i, num);
	(*pline)->len_tech += num;
	return (0);
}
