#include "shell21.h"
#include "builtin.h"

/*
** The process is the following:
** 1) we find if we in general have options - some options are regarded as
** invalid within find_options function
** 2) we have 3 modes of launch: edit (invoking the editor), list, exec:
** if one options has all the prerequisites to be launched - everything after
** is ignored
** 3) we start to parse arguments for each option and check the other options
** that influence differently depending on the place
*/

int                 btin_fc(t_ltree *pos)
{
	int				flags;
	t_btin_fc		*fc_arg;
	int				li;
	int				sy;

	li = find_in_variables(g_rdovar, &sy, "42SH_NONINTERACTIVE");
	if (g_rdovar[li][sy] == '1')
	{
		error_handler(NONINERACTIVE, pos->ar_v[0]);
		return (NONINERACTIVE);
	}
	fc_arg = init_btin_fc();
	flags = find_options(1, (char*[]){"elsrn"}, pos->ar_v);
	if (flags < 0)
		return (btin_return_exit_status());
	flags = 0;
	if (btin_fc_find_mode(pos->ar_v, &fc_arg, &flags) == HIST_ERROR)
	{
		free(fc_arg);
		return (btin_return_exit_status());
	}
	btin_fc_route_execution(fc_arg, flags, pos->envir);
	free(fc_arg);
	return (btin_return_exit_status());
}

/*
** "-" is an invalid option
** "--" is the stop for options and launch of edit-mode
** if we do not meet other options - launch the edit mode
*/

int					btin_fc_find_mode(char **argv, t_btin_fc **fc_arg,
						int *flags)
{
	int				i;

	i = 0;
	while (argv[++i])
	{
		if (!(argv[i][0] == '-') || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
			return (btin_fc_edit_mode(&argv[i], fc_arg, flags));
		if (argv[i][0] == '-' && !argv[i][1])
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
			return (HIST_ERROR);
		}
		else if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			i++;
			break ;
		}
		i = btin_fc_other_args(argv, i, fc_arg, flags);
		if (i == HIST_ERROR || i == HIST_EXEC)
			return (i);
		if (*flags & FLAG_L)
			return (btin_fc_list_mode(&argv[i], 0, fc_arg, flags));
	}
	return (btin_fc_edit_mode(&argv[i], fc_arg, flags));
}

/*
** If we meet "-e" - does not matter, what mode we will have for launch
** editor is saved: either "-evim" or "-e vim"
** "-s" option launches exec mode immediately
** "-l" option is weaker than "-s" so check till the end of the argument needed
*/

int					btin_fc_other_args(char **argv, int i, t_btin_fc **fc_arg, int *flags)
{
	int				j;
	int				tmp;

	j = 0;
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC || tmp != i)
			return (i = (tmp == HIST_EXEC) ? i : tmp);
		if (argv[i][j] == 's')
			return (btin_fc_exec_mode(&argv[i], j, fc_arg, flags));
		else if (argv[i][j] == 'l')
			*flags |= FLAG_L;
		else if (btin_fc_list_other_flags(argv[i][j], flags) == HIST_ERROR)
			return (HIST_ERROR);
	}
	if (*flags & FLAG_L)
		return (btin_fc_list_mode(&argv[i], j, fc_arg, flags));
	return (i);
}

/*
** List mode is added to history
** First we check options or argument till the end of the argument where
** "-l" option was found
** After if there are arguments - we analyse them and choose
** the no-args mode or with args
*/

int					btin_fc_list_mode(char **argv, int j, t_btin_fc **fc_arg,
						int *flags)
{
	int				i;

	if (g_hist.len < 1 || g_hist.last < 0)
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	i = btin_fc_list_check_line_args(argv, j, fc_arg, flags);
	if (i == HIST_ERROR)
		return (HIST_ERROR);
	if (argv[++i])
		return (btin_fc_list_check_other_args(&argv[i], fc_arg, flags));
	return (btin_fc_list_mode_no_args(fc_arg, flags));
}

/*
** Exec mode or "-s" flag is not insert to the history
** (it can make loop with insertions)
** First we check options or argument till the end of the argument where
** "-s" option was found
** After if there are arguments - we analyse them and choose
** the no-args mode or with args
*/

int					btin_fc_exec_mode(char **argv, int j, t_btin_fc **fc_arg,
						int *flags)
{
	int				i;

	if (g_hist.len > 0)
		delete_last_history_element();
	if (g_hist.len < 1 || g_hist.last < 0)
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_EXEC << 9), "fc");
		return (HIST_ERROR);
	}
	i = btin_fc_exec_check_line_args(argv, j, fc_arg, flags);
	if (i == HIST_ERROR)
		return (HIST_ERROR);
	if (argv[++i])
		return (btin_fc_exec_check_other_args(&argv[i], fc_arg, flags));
	return (btin_fc_exec_no_args(fc_arg, flags));
}
