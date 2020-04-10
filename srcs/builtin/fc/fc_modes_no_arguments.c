#include "shell21.h"
#include "builtin.h"

/*
** For the list mode without arguments we print the last 16 commands
** from the history list. If there are less than 16 - as much
** as we have
*/

int					btin_fc_list_mode_no_args(t_btin_fc **fc_arg, int *flags)
{
	int				temp;

	temp = 0;
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->flag |= ARG_SECOND;
	(*fc_arg)->last = -1;
	(*fc_arg)->first = -17;
	return (btin_fc_two_ints__list(fc_arg, temp) == HIST_ERROR ? 
		HIST_ERROR : btin_fc_list_mode_flags_off(flags));
}

/*
** Without arguments we invoke the last command from the history
** list
*/

int					btin_fc_exec_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	return (btin_fc_exec_mode_flags_off(flags));
}

/*
** Without arguments we invoke the last command from the history
** list
*/

int					btin_fc_edit_no_args(t_btin_fc **fc_arg, int *flags)
{
	(*fc_arg)->flag |= ARG_FIRST;
	(*fc_arg)->first_buf = g_hist.last;
	return (btin_fc_edit_mode_flags_off(flags));
}
