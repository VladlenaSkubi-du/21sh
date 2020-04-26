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

int			check_heredoc_closure(t_cmd *pline)
{
	t_list		*fd_hered;
	static char	*heredoc_buf;
	static int	buf_size;

	fd_hered = NULL;
	if (g_prompt.prompt_func != heredoc_prompt)
	{
		g_prompt.prompt_func = heredoc_prompt;
		save_heredoc_buffer(&heredoc_buf, &buf_size, NULL, INIT_BUF);
	}
	fd_hered = find_first_heredoc();
	if (fd_hered == NULL) //циклится здесь
	{
		printf("error - can't find redir\n"); //DELETE
		return (0);
	}
	return ((close_heredoc(&fd_hered,
		pline, &heredoc_buf, &buf_size) == OUT) ? OUT : 0);
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
	if (ft_strncmp(pline->cmd, fd_cont->file, pline->len_tech - 2) == 0)
	{
		final = ft_strdup(*heredoc_buf);
		save_heredoc_buffer(heredoc_buf, buf_size, NULL, CLEAR_BUF);
		dollar_expansion(&final);
		load_heredocbuf_into_file(fd_cont->fd_in, final);
		free(final);
		free(fd_cont->file);
		fd_cont->file = NULL;
		g_herenum--;
	}
	else
		save_heredoc_buffer(heredoc_buf, buf_size, pline->cmd, ADD_BUF);
	return (0);
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
		ft_strcpy(*here_buf, cmd);
	}
	else if (mode == CLEAR_BUF)
	{
		free(*here_buf);
		*here_buf = NULL;
		*buf_size = 0;
	}
	return (0);
}