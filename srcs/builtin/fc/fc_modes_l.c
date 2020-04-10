#include "shell21.h"
#include "builtin.h"

/*
** Checking arguments and options in one argument, for
** example, "-lrn" and so on
*/

int					btin_fc_list_check_line_args(char **argv, int j,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = 0;
	while (argv[i][++j])
	{
		if ((tmp = btin_fc_save_editor(argv, i, j, fc_arg)) == HIST_ERROR)
			return (HIST_ERROR);
		else if (tmp == HIST_EXEC || tmp != i)
			return (i = (tmp == HIST_EXEC) ? i : tmp);
		if (argv[i][j] == 's')
			return (btin_fc_exec_mode(&argv[i], j, fc_arg, flags));
		if (btin_fc_list_other_flags(argv[i][j], flags) == HIST_ERROR)
			return (HIST_ERROR);
	}
	return (i);
}

/*
** Checking arguments and options in the arguments array,
** for example, "-l" "-rn" and so on
*/

int					btin_fc_list_check_other_args(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	int				i;
	int				tmp;

	i = -1;
	while (argv[++i])
	{
		if (!(argv[i][0] == '-' || ft_isdigit(argv[i][0])
			|| (argv[i][0] == '-' && argv[i][1])))
		{
			error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
			return (HIST_ERROR);
		}
		if (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
			return (btin_fc_list_nums_no_error(&argv[i + 1], fc_arg, flags));
		if (ft_isdigit(argv[i][0]) || (argv[i][0] == '-' && ft_isdigit(argv[i][1])))
		{
			return (btin_fc_list_mode_num_args(argv, i, fc_arg) == HIST_ERROR ?
				HIST_ERROR : btin_fc_list_mode_flags_off(flags));
		}
		tmp = btin_fc_list_check_line_args(&argv[i], 0, fc_arg, flags);
		if (tmp == HIST_ERROR || tmp == HIST_EXEC)
			return (tmp);
		i = (tmp > i) ? tmp : i;
	}
	return (btin_fc_list_mode_no_args(fc_arg, flags));
}

/*
** List mode - numeric arguments processing (routing to functions)
** for calculations
*/

int					btin_fc_list_nums_no_error(char **argv,
						t_btin_fc **fc_arg, int *flags)
{
	if (!argv[0])
		return (btin_fc_list_mode_no_args(fc_arg, flags));
	if (ft_isdigit(argv[0][0]) || (argv[0][0] == '-' && ft_isdigit(argv[0][1])))
	{
		return (btin_fc_list_mode_num_args(argv, 0, fc_arg) == HIST_ERROR ?
			HIST_ERROR : btin_fc_list_mode_flags_off(flags));
	}
	error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
	return (HIST_ERROR);
}

/*
** List mode - arguments processing - calculations
*/

int					btin_fc_list_mode_num_args(char **argv, int i,
						t_btin_fc **fc_arg)
{
	int				temp;
	
	temp = 0;
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first = ft_atoi(argv[i]);
	i++;
	if (!argv[i])
	{
		(*fc_arg)->flag |= ARG_SECOND;
		(*fc_arg)->last = -1;
		return ((btin_fc_two_ints__list(fc_arg, temp) == HIST_ERROR) ?
			HIST_ERROR : 0);
	}
	else if (!(ft_isdigit(argv[i][0]) || (argv[i][0] == '-' &&
		ft_isdigit(argv[i][1]))))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = ft_atoi(argv[i]);
	return ((btin_fc_two_ints__list(fc_arg, temp) == HIST_ERROR) ?
		HIST_ERROR : 0);
}

/*
** List mode - calculation of fc-numeric values
*/

int				btin_fc_calculate_nums__list(int buffer, int from)
{
	int			value;
	int			tmp;

	from += (from < 1) ? HISTORY_LIMIT : 0;
	tmp = buffer + from;
	if (tmp > HISTORY_LIMIT)
		value = tmp - HISTORY_LIMIT;
	else
		value = tmp;
	return (value);
}