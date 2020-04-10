#include "shell21.h"
#include "builtin.h"

/*
** In the edit mode @fc_arg->editor, @fc_arg->flag, @fc_arg->first_buf
** and @fc_arg->second_buf (if exists) are necessary and @flags FLAG_R can
** also influence the output
**
** In the list mode @fc_arg->flag, @fc_arg->first_buf
** and @fc_arg->second_buf, @fc_arg->first and @fc_arg->second
** are necessary and @flags FLAG_N and FLAG_R can influence the
** output
**
** In the exec mode @fc_arg->flag, @fc_arg->first_buf or @fc_arg->s_cmd
** and @fc_arg->s_comp are necessary, @flags do not influence the
** output
*/

int					btin_fc_route_execution(t_btin_fc *fc_arg, int flags,
						char **envir)
{

	if (flags & FLAG_E)
		return (btin_fc_execute_edition(fc_arg, flags, envir));
	else if (flags & FLAG_L)
	{
		if (flags & FLAG_R)
		{
			if (fc_arg->first_buf > fc_arg->last_buf)
				btin_fc_execute_list(fc_arg, flags, 'r');
			else
				btin_fc_execute_list_reverse(fc_arg, flags, 'r');
		}
		else
			if (fc_arg->first_buf > fc_arg->last_buf)
				btin_fc_execute_list_reverse(fc_arg, flags, 'd');
			else
				btin_fc_execute_list(fc_arg, flags, 'd');	
	}
	else if (flags & FLAG_S)
		return (btin_fc_execute_execution(fc_arg));
	return (0);
}

/*
** For the exec mode we find the command to launch and
** launch it through parser, saving all the globals
*/

int					btin_fc_execute_execution(t_btin_fc *fc_arg)
{
	char			*cmd;
	int				tmp;

	cmd = btin_fc_execute_form_cmd(fc_arg);
	if (ft_strcmp(cmd, "error") == 0)
		return (HIST_ERROR);
	if (cmd == NULL || cmd[0] == 0)
		cmd = ft_strdup(g_hist.hist[g_hist.last]);
	tmp = ft_strlen(cmd);
	cmd = (tmp > 0 && cmd[tmp - 1] == '\n') ? cmd : ft_strrejoin(cmd, "\n");
	btin_fc_save_parser_globals(1);
	ft_putstr_fd(cmd, STDOUT_FILENO);
	parser(cmd);
	btin_fc_save_parser_globals(0);
	return (0);
}

/*
** From the biggest num to the least
** @flag can be 'd' = direct order, 'r' - reverse order
** Output according to the POSIX standard:
** When the -l option is used to list commands,
** the format of each command in the list shall be as follows:
** "%d\t%s\n", <line number>, <command>
** If both the -l and -n options are specified,
** the format of each command shall be:
** "\t%s\n", <command>
*/

int					btin_fc_execute_list_reverse(t_btin_fc *fc_arg, int flags, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;
	int				num;
	
	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	num = (flag == 'd') ? fc_arg->first : fc_arg->last;
	while (value - i >= to && value - i >= 0)
	{
		tmp = ft_strlen(g_hist.hist[value - i]);
		if (tmp > 0 && g_hist.hist[value - i][tmp - 1] == '\n')
			tmp -= 1;
		if (!(flags & FLAG_N))
			ft_printf("%d\t%.*s\n", num - i, tmp,
				g_hist.hist[value - i]);
		else
			ft_printf("\t%.*s\n", tmp, g_hist.hist[value - i]);
		i++;
	}
	return (0);
}

/*
** From the least num to the biggest
** @flag can be 'd' = direct order, 'r' - reverse order
** Output according to the POSIX standard:
** When the -l option is used to list commands,
** the format of each command in the list shall be as follows:
** "%d\t%s\n", <line number>, <command>
** If both the -l and -n options are specified,
** the format of each command shall be:
** "\t%s\n", <command>
*/

int					btin_fc_execute_list(t_btin_fc *fc_arg, int flags, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;
	int				num;

	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	num = (flag == 'd') ? fc_arg->first : fc_arg->last;
	while (value + i <= to && value + i < g_hist.len)
	{
		if (num + i > HISTORY_LIMIT)
			num = num - HISTORY_LIMIT;
		tmp = ft_strlen(g_hist.hist[value + i]);
		if (tmp > 0 && g_hist.hist[value + i][tmp - 1] == '\n')
			tmp -= 1;
		if (!(flags & FLAG_N))
			ft_printf("%d\t%.*s\n", num + i, tmp,
				g_hist.hist[value + i]);
		else
			ft_printf("\t%.*s\n", tmp, g_hist.hist[value + i]);
		i++;
	}
	return (0);
}

/*
** Saving global values is necessary because through launching
** without fork we change the values
*/

int					btin_fc_save_parser_globals(int flag)
{
	static char		*save_g_cmd;
	static char		*save_techline_cmd;
	static t_list	*save_g_start_list;

	if (flag == 1)
	{
		save_g_cmd = g_cmd;
		save_techline_cmd = g_techline.line;
		save_g_start_list = g_start_list;
	}
	else
	{
		g_cmd = save_g_cmd;
		g_techline.line = save_techline_cmd;
		g_start_list = save_g_start_list;
		save_g_cmd = NULL;
		save_techline_cmd = NULL;
		save_g_start_list = NULL;
	}
	return (0);
}