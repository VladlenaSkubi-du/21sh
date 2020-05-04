#include "shell21.h"
#include "parser.h"

void	у(char **vec)
{
	size_t	i;

	i = 0;
	while (vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}

char	*get_env(char *var)
{
	char	*val;
	size_t	i;
	size_t	len;

	val = 0;
	i = 0;
	if (!g_env)
		return (NULL);
	len = ft_strlen(var);
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], var, len))
			break;
		i++;
	}
	if (g_env[i])
		val = ft_strdup(g_env[i] + len + 1);
	return (val);
}

/*
** So, let's talk about pipes:
** 1) If only PIPED_OUT -- create pipe
** 2) If only PIPED_IN -- delete pipe
*/



/*
** Check if programm to start is buildin and if it is - start builtin
*/

int		ft_builtins_check(t_ltree *pos, int flag)
{
	int		i;
	int		tmp;

	i = 0;
	while (g_builtins[i])
	{
		if (!ft_strcmp(pos->ar_v[0], g_builtins[i]))
		{
			if (flag && i < 3)
			{
				tmp = builtins_call_void(i);
				exit_status_variable(tmp);
			}
			else if (flag && i >= 3)
			{
				tmp = builtins_call(i, pos);
				exit_status_variable(tmp);
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int		fd_list_process(t_ltree *pos)
{
	t_list		*fd_list;
	t_fd_redir	*redir;

	fd_list = pos->fd;
	while (fd_list)
	{
		redir = (t_fd_redir *)fd_list->content;
		if (redir->fd_in != CLOSE)
			dup2(redir->fd_in, redir->fd_out);
		else
		{
			dup2(redir->fd_out, redir->fd_out);
			close (redir->fd_out);
		}
		fd_list = fd_list->next;
	}
	return (0);
}
