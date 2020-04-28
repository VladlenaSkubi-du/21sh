#include "shell21.h"
#include "parser.h"

void			print_fd_blocks(t_pblks	*ptr_block_cont)
{
	t_list		*fd_runner;
	t_fd		*ptr_fd;

	fd_runner = ptr_block_cont->fd;
	while (fd_runner)
	{
		ptr_fd = fd_runner->content;
		ft_printf("******************************\n");
		// ft_printf("Fd_in %d\nFd_out %d\n", ptr_fd->fd_in, ptr_fd->fd_out);
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

void			print_all_lists(void)
{
	t_list		*runner;
	t_pblks		*ptr_block_cont;
	t_cmd		*ptr_lcmd;
	int			end;

	if (g_grblks == NULL)
		ft_printf("empty grammar blocks\n");
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

void			print_techline(char *cmd, char *techline, int len_tech)
{
	int			i;

	i = -1;
	ft_printf("g_cmd = %s\n", cmd);
	ft_printf("techline cur:");
	while (++i <= len_tech)
		ft_printf("%3d", techline[i]);
	ft_printf("\n");
}