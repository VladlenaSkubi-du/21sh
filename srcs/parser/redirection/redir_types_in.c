#include "shell21.h"
#include "parser.h"

/*
** Function to detect "[n]< word"
*/

int		ft_redir_less(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (final->l_tline.line[*i] == LTHAN &&
		(final->l_tline.line[*i + 1] != LTHAN &&
		(final->l_tline.line[*i + 1] != AND ||
		final->l_tline.line[*i + 1] == PIPE)))
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(final, *i, 1);
		(*i)++;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_in = open(f_name, O_RDONLY |
			O_CLOEXEC | O_SYNC | O_NOCTTY)) == -1)
				return (ft_access_check(&f_name, final, R_OK));
			else
				add_redir_fd(final, &fd_open);
		}
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]<<stop_word" here-document
*/

int		ft_redir_dless(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (final->l_tline.line[*i] == LTHAN && final->l_tline.line[*i + 1] == LTHAN
		&&	final->l_cmd[*i + 2] != '-')
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(final, *i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_heredoc_form(&fd_open, f_name, final, 0));
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]<<- stop_word" here-document with TAB delete
*/

int		ft_redir_dless_min(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (final->l_tline.line[*i] == LTHAN && final->l_tline.line[*i + 1] == LTHAN
		&& final->l_cmd[*i + 2] == '-')
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(final, *i, 3);
		(*i) += 3;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_heredoc_form(&fd_open, f_name, final, MINUS));
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(f_name);
	return (0);
}

/*
** Function to detect "[n]<&[m]" (input from fd or file if)
*/

int		ft_redir_lessand(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	fd_open.type = IN_R;
	if (final->l_tline.line[*i] == LTHAN && (final->l_tline.line[*i + 1] == AND))
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDIN_FILENO);
		ft_null_redir(final, *i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_num_or_word_in(&f_name, &fd_open, final));
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	free(f_name);
	return (0);
}

int		ft_heredoc_form(t_fd_redir *fd_open, char *f_name, t_ltree *final,
		int flag)
{
	if (g_prompt.prompt_func == main_prompt)
	{
		fd_open->fd_in = ft_tmpfile(TMPL);
		add_redir_fd(final, fd_open);
		g_heredoc.stop.stop_w = ft_strdup(f_name);
		g_heredoc.stop.fd = fd_open->fd_in;
		g_heredoc.stop.flag = flag;
		ft_add_list_to_end(&(g_heredoc.list),
			ft_lstnew(&g_heredoc.stop, sizeof(t_stop)));
	}
	return (0);
}
