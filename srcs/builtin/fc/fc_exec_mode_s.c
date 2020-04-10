#include "shell21.h"
#include "builtin.h"

/*
** Here we choose the cmd according to the number or the word
** and change it according to the assignments if exists
*/

char				*btin_fc_execute_form_cmd(t_btin_fc *fc_arg)
{
	char			*cmd;
	int				tmp;
	
	cmd = NULL;
	if (fc_arg->s_cmd)
	{
		if ((tmp = find_in_history(fc_arg->s_cmd)) == -1)
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_EXEC << 9), fc_arg->s_cmd);
			return ("error");
		}
		cmd = ft_strdup(g_hist.hist[tmp]);
	}
	else if (fc_arg->flag & ARG_FIRST)
	{
		cmd = ft_strdup((fc_arg->first_buf > g_hist.last) ?
			g_hist.hist[g_hist.last] : g_hist.hist[fc_arg->first_buf]);
	}
	if (fc_arg->s_comp)
		cmd = make_history_assignments(fc_arg, cmd);
	return (cmd);
}

/*
** Because of norm it is here
** Refers to fc_mode_s processing
** Processing of the @fc_arg->s_comp value
*/

int					btin_fc_exec_mode_add_comp(t_btin_fc **fc_arg, char *comp)
{
	static int		i;

	if (comp != NULL)
	{
		(*fc_arg)->s_comp[i] = comp;
		i++;
	}
	else
	{
		free((*fc_arg)->s_comp);
		i = 0;
	}
	return (0);
}

/*
** If we have assignments, we start to change the cmd-line from
** the first assignment to the last found:
** For example, echo $HISTFILE aa is the command
** The command line is: fc -s HISTFILE=HISTFILESIZE
** HI=BB FILESIZE=FILE FILE=DD echo
** And assignments are:
** HISTFILE=HISTFILESIZE
** HI=BB
** FILESIZE=FILE
** FILE=DD
**
** There will be changes: echo $HISTFILESIZE aa
** Than: echo $BBSTFILESIZE aa
** Than: echo $BBSTFILE aa
** Than: echo $BBSTDD aa
** Finally: echo $BBSTDD aa will be launched
*/

char				*make_history_assignments(t_btin_fc *fc_arg, char *cmd)
{
	int				i;
	int				buf_len;
	char			*buf;
	int				eq;
	char			*what;

	buf_len = CMD_SIZE;
	buf = (char*)ft_xmalloc(buf_len + 1);
	eq = ft_strlen(cmd) - 1;
	(cmd[eq] == '\n') ? ft_strncpy(buf, cmd, eq) : ft_strcpy(buf, cmd);
	i = -1;
	while (fc_arg->s_comp[++i])
	{
		eq = ft_strchri(fc_arg->s_comp[i], '=');
		what = ft_strndup(fc_arg->s_comp[i], eq);
		if (ft_strstr(buf, what) != NULL)
			buf = insert_history_assignment(buf, &buf_len,
				fc_arg->s_comp[i] + eq + 1, what);
		free(what);
	}
	free(cmd);
	btin_fc_exec_mode_add_comp(&fc_arg, NULL);
	cmd = ft_strdup(buf);
	free(buf);
	return (cmd);
}

/*
** Inserting assignment to the command line for the launch
*/

char				*insert_history_assignment(char *buf, int *buf_len,
						char *change, char *what)
{
	int				ptr;
	int				len_what;
	int				len_change;
	int				len_cmd;
	char			*tmp;

	tmp = ft_strstr(buf, what);
	ptr = tmp - buf;
	len_cmd = ft_strlen(buf);
	len_change = ft_strlen(change);
	len_what = ft_strlen(what);
	if (len_what == 0)
		return (insert_history_assignment_whole_line
			(buf, buf_len, change, len_change));
	tmp = ft_strdup(buf + ptr + len_what);
	if (len_cmd - len_what + len_change >= *buf_len)
	{
		buf = ft_realloc(buf, len_cmd, *buf_len, *buf_len * 2);
		*buf_len *= 2;
	}
	ft_strcpy(buf + ptr, change);
	ft_strcpy(buf + ptr + len_change, tmp);
	free(tmp);
	return (buf);
}

/*
** If the assignment is "=foo", the assignment is applied to
** each symbol of the command
** For example: echo $BBSTDD aa is the command
** The command line is fc -s =foo
** The output is: foofoofoofoofoofoofoofoofoofoofoofoofoofoofoofoofoo
*/

char				*insert_history_assignment_whole_line(char *buf,
						int *buf_len, char *change, int len_change)
{
	int				i;
	int				len_cmd;
	int				len_full;
	int				ptr;

	i = -1;
	ptr = 0;
	len_cmd = ft_strlen(buf);
	len_full = len_cmd;
	while (++i < len_cmd)
	{
		if (len_full + len_change >= *buf_len)
		{
			buf = ft_realloc(buf, len_cmd, *buf_len, *buf_len * 2);
			*buf_len *= 2;
		}
		ft_strcpy(buf + ptr, change);
		ptr += len_change;
		len_full += len_change;
	}
	return (buf);
}
