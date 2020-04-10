#include "shell21.h"
#include "builtin.h"

/*
** Checking arguments and options in one argument, for
** example, "-srn" and so on
*/

int					btin_fc_exec_check_line_args(char **argv, int j,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = 0;
	if (argv[i][0] != '-' && (tmp = ft_strchri(argv[i], '=')) >= 0)
		return (btin_fc_exec_mode_comp(&argv[i], fc_arg, flags));
	(argv[i][0] != '-') ? (*fc_arg)->s_cmd = argv[i] : 0;
	if (argv[i][0] != '-')
		return (btin_fc_exec_mode_flags_off(flags));
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC || tmp != i)
			return (i = (tmp == HIST_EXEC) ? i : tmp);
		i = btin_fc_exec_other_flags(argv[i][j]);
		if (i == HIST_ERROR)
			return (i);
	}
	return (i);
}

/*
** Checking arguments and options in the arguments array,
** for example, "-s" "-rn" and so on
*/

int					btin_fc_exec_check_other_args(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = -1;
	while (argv[++i])
	{
		if ((ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
			ft_isdigit(argv[i][1]))) && ((tmp = ft_strchri(argv[i], '=')) == -1))
		{
			(*fc_arg)->flag |= ARG_FIRST;
			(*fc_arg)->first = ft_atoi(argv[i]);
			return ((btin_fc_one_int__exec(fc_arg) == HIST_ERROR) ?
				HIST_ERROR : btin_fc_exec_mode_flags_off(flags));
		}
		tmp = btin_fc_exec_check_invalid(&argv[i], fc_arg, flags);
		if (tmp == HIST_ERROR || tmp == HIST_EXEC)
			return (tmp);
		tmp = btin_fc_exec_check_line_args(&argv[i], 0, fc_arg, flags);
		if (tmp == HIST_ERROR || tmp == HIST_EXEC)
			return (tmp);
		i = (tmp > i) ? tmp : i;
	}
	return (btin_fc_exec_no_args(fc_arg, flags));
}

/*
** If the argument included a sign '=' - the argument
** is regarded as assignment and added to the
** @fc_arg->s_comp array
** if it is a numeric value - @fc_arg->first_buf
** If it is a test - @fc_arg->s_cmd
** In exec mode the are two options to get a command for
** execution: number of the command in the history list
** or name of the command. Assignment is launched if
** there is what to correct in the cmd
*/

int					btin_fc_exec_mode_comp(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = -1;
	while (argv[++i])
	{
		if ((tmp = ft_strchri(argv[i], '=')) >= 0)
		{
			(!(*fc_arg)->s_comp) ? (*fc_arg)->s_comp =
				(char**)ft_xmalloc(sizeof(char*) * FC_COMP_ARRAY) : 0;
			btin_fc_exec_mode_add_comp(fc_arg, argv[i]);
			continue;
		}
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-'
			&& ft_isdigit(argv[i][1])))
		{
			(*fc_arg)->flag |= ARG_FIRST;
			(*fc_arg)->first = ft_atoi(argv[i]);
			btin_fc_one_int__exec(fc_arg);
			return (btin_fc_exec_mode_flags_off(flags));
		}
		(*fc_arg)->s_cmd = argv[i];
		return (btin_fc_exec_mode_flags_off(flags));
	}
	return (btin_fc_exec_no_args(fc_arg, flags));
}

/*
** Options at the places of the arguments for exec mode
** are regarded as invalid arguments
** After exec mode is launched, options become arguments
*/

int					btin_fc_exec_check_invalid(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;

	i = 0;
	if (argv[i][0] == '-' && !argv[i][1])
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
		return (btin_fc_exec_mode_comp(&argv[i], fc_arg, flags));
	return (i);
}

/*
** We count according to fc_number. From POSIX standard:
** The command history list shall reference commands by number.
** The first number in the list is selected arbitrarily.
** The relationship of a number to its command shall not change
** except when the user logs in and no other process is accessing
** the list, at which time the system may reset the numbering to
** start the oldest retained command at another number (usually 1).
** When the number reaches an implementation-defined upper limit,
** which shall be no smaller than the value in HISTSIZE or 32767
** (whichever is greater), the shell may wrap the numbers,
** starting the next command with a lower number (usually 1).
** However, despite this optional wrapping of numbers,
** fc shall maintain the time-ordering sequence of the commands.
** For example, if four commands in sequence are given the numbers
** 32766, 32767, 1 (wrapped), and 2 as they are executed,
** command 32767 is considered the command previous to 1,
** even though its number is higher.
*/

int				btin_fc_one_int__exec(t_btin_fc **fc_arg)
{
	int			temp;

	temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	if ((*fc_arg)->first > 0)
	{
		if (((*fc_arg)->first_buf = btin_fc_positive_int__exec
			((*fc_arg)->first, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else
		(*fc_arg)->first_buf = btin_fc_negative_int__exec((*fc_arg)->first);
	return (0);
}