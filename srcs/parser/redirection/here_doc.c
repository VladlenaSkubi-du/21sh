#include "shell21.h"
#include "parser.h"

/*
** It needs to check must to go to here-doc mode or not. If not - starts exe
*/

int		check_heredoc_closure(void)
{
	if (g_heredoc.list != NULL && g_prompt.prompt_func != heredoc_prompt)
	{
		g_prompt.prompt_func = heredoc_prompt;
		ft_g_init_heredoc();
	}
	else if (g_heredoc.list != NULL)
	{
		if (ft_check_heredoc_end() == OUT)
			return (0);
		ft_heredoc_fill(ret);
	}
	if (g_prompt.prompt_func == main_prompt)
	{
		ft_block_start(&g_start_list);
		return (0);
	}
	return (ret);
}

/*
** It needs to check here-docs correctly ends
*/

int		ft_check_heredoc_end(void)
{
	t_list	*tmp;
	char	**lines_in;
	int		i;
	t_stop	*find;
	
	tmp = g_heredoc.list;
	null_here_line();
	lines_in = g_heredoc.buf;
	i = -1;
	while (tmp)
	{
		find = (t_stop *)tmp->content;
		while (lines_in[++i])
		{
			if (!ft_strncmp(find->stop_w, lines_in[i],
				ft_strlen(lines_in[i]) - 1)	|| lines_in[i][0] == EOF)
			{
				tmp = tmp->next;
				break ;
			}
		}
		if (tmp != NULL && lines_in[i] == NULL)
			return (OUT);
	}
	return (0);
}

/*
** function fills fd of tmp files by here-docs
*/

int		ft_heredoc_fill(int ret)
{
	t_list	*tmp;
	char	**lines_in;
	int		i;
	t_stop	*find;
	
	tmp = g_heredoc.list;
	lines_in = g_heredoc.buf;
	i = -1;
	while (tmp)
	{
		find = (t_stop *)tmp->content;
		while (lines_in[++i])
		{
			if (find->flag == MINUS)
				here_tab_remove(&(lines_in[i]));
			if (!ft_strncmp(find->stop_w, lines_in[i],
				ft_strlen(lines_in[i]) - 1)	|| lines_in[i][0] == EOF)
				break ;
			ft_putstr_fd(lines_in[i], find->fd);			
		}
		tmp = tmp->next;
	}
	ft_heredoc_rem();
	g_prompt.prompt_func = main_prompt;
	return (ret);
}

/*
** function frees g_heredoc content
*/

int		ft_heredoc_rem(void)
{
	t_list	*tmp;
	t_stop	*find;

	tmp = g_heredoc.list;
	while(tmp)
	{
		find = (t_stop *)tmp->content;
		lseek(find->fd, 0, SEEK_SET);
		free(find->stop_w);
		tmp = tmp->next;
	}
	if (g_heredoc.buf)
		ft_arrdel(g_heredoc.buf);
	ft_lstclear(&g_heredoc.list);
	return (0);
}

int		ft_g_init_heredoc()
{
	g_heredoc.buf = (char **)ft_xmalloc(sizeof(char*) * (HEREDOC_BUF));
	g_heredoc.buf_size = HEREDOC_BUF;
	return (0);
}
