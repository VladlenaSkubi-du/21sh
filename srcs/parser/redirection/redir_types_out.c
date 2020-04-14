#include "shell21.h"
#include "parser.h"

/*
** Function to detect "[n]>word" n = STDOUT_FILENO- defualt
*/

int		ft_redir_great(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	if (final->l_tline.line[*i] == GTHAN && (final->l_tline.line[*i + 1] != GTHAN &&
		(final->l_tline.line[*i + 1] != AND)))
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(final, *i, 1);
		(*i)++;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_in = open(f_name, O_CREAT | O_WRONLY | O_TRUNC |
			O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRUSR | S_IWUSR)) == -1)
				return (ft_access_check(&f_name, final, W_OK));
			else
				add_redir_fd(final, &fd_open);
		}
		else
			return (final->flags |= ERR_OUT | ERR_REDIR << 16);
	}
	(f_name != NULL) ? free(f_name) : 0;
	return (0);
}

/*
** Function to detect ">>word" (write to end)
*/

int		ft_redir_dgreat(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	if (final->l_tline.line[*i] == GTHAN && final->l_tline.line[*i + 1] == GTHAN)
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(final, *i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
		{
			if ((fd_open.fd_in = open(f_name, O_CREAT | O_WRONLY | O_APPEND |
				O_CLOEXEC | O_SYNC | O_NOCTTY, S_IRUSR | S_IWUSR)) == -1)
				return (ft_access_check(&f_name, final, W_OK));
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
** Function to detect "[n]>&[m]"
** fcntl used to check access to write in fd
*/

int		ft_redir_greatand(t_ltree *final, size_t *i)
{
	t_fd_redir	fd_open;
	char		*f_name;

	f_name = NULL;
	if (final->l_tline.line[*i] == GTHAN && (final->l_tline.line[*i + 1] == AND))
	{
		fd_open.fd_out = ft_check_n_redir_op(*i, final, STDOUT_FILENO);
		ft_null_redir(final, *i, 2);
		(*i) += 2;
		if ((f_name = ft_word_to_redir(i, final, FF)) != NULL)
			return (ft_num_or_word_out(&f_name, &fd_open, final));
		else
			return (final->flags |= ERR_REDIR << 16);
	}
	free(f_name);
	return (0);
}

/*
** Function needs to check access rights
*/

int		ft_access_check(char **f_name, t_ltree *final, int type)
{
	char	*path;
	int		st;

	path = (char*)ft_xmalloc(MAXDIR);
	getcwd(path, MAXDIR);
	if (path[0] == 0)
		free(path);
	ft_strcat(path, "/");
	ft_strcat(path, *f_name);
	final->err = *f_name;
	if ((st = access(path, F_OK)) == -1)
	{
		free(path);
		return (final->flags |= ERR_IN | ERR_R | ERR_NO_FILE << 16); // сделать одну ошибку в перенаправлении
	}
	if ((st = access(path, type)) == -1)
	{
		free(path);
		return (final->flags |= ERR_IN | ERR_R | ERR_NO_ACC << 16);
	}
	return (0);
}
