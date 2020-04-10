#include "shell21.h"
#include "builtin.h"

/*
** For edit mode (without "-l" or "-s" option) we need to get
** information about the editor to use - if no "-e" option with
** the argument is stated, we look for the editor name in the variables:
** FCEDIT, if there is nothing - use the default vim-editor
** POSIX standard: Use the editor named by editor to edit the commands.
** The editor string is a utility name, subject to search via the
** PATH variable (see XBD Environment Variables). The value in the
** FCEDIT variable shall be used as a default when -e is not specified.
** If FCEDIT is null or unset, ed (we have absolute path to vim-editor)
** shall be used as the editor.
*/

int					btin_fc_edit_mode(char **argv, t_btin_fc **fc_arg,
						int *flags)
{
	int				li;
	int				sy;

	if (g_hist.len > 0)
		delete_last_history_element();
	if (g_hist.len < 1 || g_hist.last < 0)
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	if ((*fc_arg)->editor == NULL)
	{
		li = find_in_variables(g_shvar, &sy, "FCEDIT=");
		if (g_shvar[li][sy])
			(*fc_arg)->editor = &g_shvar[li][sy];
		else
			(*fc_arg)->editor = "/usr/bin/vim"; //исправить после того как будет type
	}
	return (btin_fc_edit_other_args(argv, fc_arg, flags));
}

/*
** Checking arguments and options in the arguments array,
** for example, "-rn" and so on
*/

int					btin_fc_edit_other_args(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	
	i = 0;
	if (!argv[i])
		return (btin_fc_edit_no_args(fc_arg, flags));
	if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
	{
		return ((btin_fc_edit_mode_num_args(argv, i, fc_arg) == HIST_ERROR) ?
			HIST_ERROR : btin_fc_edit_mode_flags_off(flags));
	}
	else
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	return (0);
}

/*
** Edit mode - arguments processing - calculations
*/

int					btin_fc_edit_mode_num_args(char **argv, int i,
						t_btin_fc **fc_arg)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first = ft_atoi(argv[i]);
	i++;
	if (!argv[i])
		return ((btin_fc_one_int__exec(fc_arg) == HIST_ERROR) ?
			HIST_ERROR : 0);
	else if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
		ft_isdigit(argv[i][1]))))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = ft_atoi(argv[i]);
	return ((btin_fc_two_ints__edit(fc_arg) == HIST_ERROR) ?
		HIST_ERROR : 0);
}

/*
** Here we find the numeric positions of the commands in the
** history list according to the agruments sent by the user:
** we interprete "-1" or "10" arguments for the positions
** in the buffer
*/

int					btin_fc_two_ints__edit(t_btin_fc **fc_arg)
{
	int				temp;

	if (!(((*fc_arg)->flag & ARG_FIRST) && ((*fc_arg)->flag & ARG_SECOND)))
		return (HIST_ERROR);
	temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	temp += (temp < 1) ? HISTORY_LIMIT : 0;
	if ((*fc_arg)->last > 0 && ((*fc_arg)->last_buf =
		btin_fc_positive_int__exec((*fc_arg)->last, temp,
		g_hist.last_fc)) == HIST_ERROR)
		return (HIST_ERROR);
	else if ((*fc_arg)->last <= 0)
		(*fc_arg)->last_buf = btin_fc_negative_int__list((*fc_arg)->last);
	if ((*fc_arg)->first > 0 && ((*fc_arg)->first_buf =
		btin_fc_positive_int__exec((*fc_arg)->first, temp,
		g_hist.last_fc)) == HIST_ERROR)
		return (HIST_ERROR);
	else if ((*fc_arg)->first <= 0)
		(*fc_arg)->first_buf = btin_fc_negative_int__list((*fc_arg)->first);
	return (0);
}

/*
** The editor with the "-e" option can be in the same argument
** as the option and in the next argument: "-evim" of "-e" "vim"
*/

int					btin_fc_save_editor(char **argv, int i,
						int j, t_btin_fc **fc_arg)
{
	if (argv[i][j] == 'e' && !(argv[i + 1] || argv[i][j + 1]))
	{
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_ARG << 9), "fc: -e");
		usage_btin("fc");
		return (HIST_ERROR);
	}
	else if (argv[i][j] == 'e' && (argv[i + 1] || argv[i][j + 1]))
	{
		if (argv[i][j + 1])
		{
			(*fc_arg)->editor = &argv[i][j + 1];
			return (HIST_EXEC);
		}
		else
		{
			i++;
			(*fc_arg)->editor = argv[i];
		}
	}
	return (i);
}
