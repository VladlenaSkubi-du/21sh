#include "shell21.h"
#include "parser.h"

#define INIT_BUF	1
#define ADD_BUF		2
#define CLEAR_BUF	-1

int			redir_heredoc(t_pblks **current_cont,
							t_cmd **ptr_lcmd, int *i)
{
	t_list		*new_fd;
	t_fd		fd_inout;

	bzero_fd_redir(&fd_inout);
	if ((*ptr_lcmd)->tech[*i] == LTHAN && (*ptr_lcmd)->tech[*i + 1] == LTHAN)
	{
		if (find_fdbefore_redir(ptr_lcmd, &fd_inout, i) == OUT)
			return (activate_redir_error(current_cont, fd_inout));
		(fd_inout.fd_out == -1) ? fd_inout.fd_out = STDIN_FILENO : 0;
		delete_symbols_from_parser_line(ptr_lcmd, *i + 2, -2);
		if (find_fdafter_redir(ptr_lcmd, &fd_inout, i) == OUT)
			return (activate_redir_error(current_cont, fd_inout));
		fd_inout.flag |= REDIRECTION_FD;
		g_herenum++;
		fd_inout.fd_in = ft_tmpfile();
		new_fd = add_redir_to_block(fd_inout);
		ft_lstadd_to_end(&(*current_cont)->fd, new_fd);
		if (*i == 0)
			*i = -1;
	}
	return (0);
}

static void	print_fd(t_list *fd_hered)
{
	t_fd *ptr_fd = fd_hered->content;

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
}

int			check_heredoc_closure(t_cmd *pline)
{
	static t_list	*fd_hered;
	static char		*heredoc_buf;
	static int		buf_size;

	if (g_prompt.prompt_func != heredoc_prompt)
	{
		g_prompt.prompt_func = heredoc_prompt;
		save_heredoc_buffer(&heredoc_buf, &buf_size, NULL, INIT_BUF);
		fd_hered = find_first_heredoc();
		print_fd(fd_hered);
		return (OUT);
	}
	if (fd_hered == NULL)
	{
		
	}
	if (close_heredoc(&fd_hered, pline,
			&heredoc_buf, &buf_size) == OUT)
		return (OUT);
	fd_hered = find_first_heredoc();
	return (0);
}

t_list		*find_first_heredoc(void)
{
	t_list		*pblk_hered;
	t_list		*fd_runner;
	t_pblks		*pblk_cont;
	t_fd		*fd_cont;

	pblk_hered = g_grblks;
	while (pblk_hered)
	{
		pblk_cont = pblk_hered->content;
		fd_runner = pblk_cont->fd;
		while (fd_runner)
		{
			fd_cont = fd_runner->content;
			if (fd_cont->flag &&
				(fd_cont->flag & REDIRECTION_FD) &&
				fd_cont->file)
				return (fd_runner);
			fd_runner = fd_runner->next;
		}
		pblk_hered = pblk_hered->next;
	}
	return (NULL);
}

/*
** Expression: pline->len_tech - 2 means that we compare the line
** coming to parser without the last '\n'
** If ft_strncmp function returns 0, it means that the heredoc is
** closed and we rewrite the whole buffer to the file and
** delete the heredoc
*/

int			close_heredoc(t_list **fd_hered,
				t_cmd *pline, char **heredoc_buf, int *buf_size)
{
	t_fd		*fd_cont;
	char		*final;
	
	fd_cont = (*fd_hered)->content;
	if (ft_strchrdiff(pline->cmd, fd_cont->file, '\n') || pline->cmd[0] == EOF)
	{
		g_prompt.prompt_func = main_prompt;
		final = ft_strdup(*heredoc_buf);
		dollar_expansion(&final);
		load_heredocbuf_into_file(fd_cont->fd_in, final);
		free(final);
		free(fd_cont->file);
		fd_cont->file = NULL;
		save_heredoc_buffer(heredoc_buf, buf_size, NULL, CLEAR_BUF);
		g_herenum--;
		if (g_herenum > 0)
		{
			if (check_heredoc_closure(pline) == OUT)
				return (OUT);
		}
		return (0);
	}
	save_heredoc_buffer(heredoc_buf, buf_size, pline->cmd, ADD_BUF);
	return (OUT);
}

int			load_heredocbuf_into_file(int fd, char *heredoc_buf)
{
	int			i;
	int			start;
	
	i = 0;
	start = 0;
	while (heredoc_buf[i])
	{
		if (heredoc_buf[i] == '\n')
		{
			write(fd, heredoc_buf + start, i + 1);
			start = i + 1;
		}
		i++;
	}
	lseek(fd, 0, SEEK_SET);
	return (0);
}

int			save_heredoc_buffer(char **here_buf, int *buf_size,
				char *cmd, int mode)
{
	int			buf_len;

	if (mode == INIT_BUF)
	{
		*here_buf = (char*)ft_xmalloc(HEREDOC_BUF);
		*buf_size = HEREDOC_BUF;
	}
	else if (mode == ADD_BUF)
	{
		buf_len = ft_strlen(*here_buf);
		if (buf_len + (int)ft_strlen(cmd) + 1 >= (*buf_size))
		{
			*here_buf = ft_realloc(*here_buf, (size_t)buf_len,
				(size_t)*buf_size, (size_t)*buf_size * 2);
			*buf_size *= 2;
		}
		ft_strcat(*here_buf, cmd);
	}
	else if (mode == CLEAR_BUF)
	{
		free(*here_buf);
		*here_buf = NULL;
		*buf_size = 0;
	}
	return (0);
}