#include "shell21.h"
#include "builtin.h"

/*
** Here we find the numeric positions of the commands in the
** history list according to the agruments sent by the user:
** we interprete "-1" or "10" arguments for the positions
** in the buffer and also find numeric fc-values for the
** list mode
*/

int				btin_fc_two_ints__list(t_btin_fc **fc_arg, int temp)
{
	temp = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	temp += (temp < 1) ? HISTORY_LIMIT : 0;
	if (((*fc_arg)->flag & ARG_SECOND) && (*fc_arg)->last > 0)
	{
		if (((*fc_arg)->last_buf = btin_fc_positive_int__list
			((*fc_arg)->last, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else if ((*fc_arg)->flag & ARG_SECOND)
		(*fc_arg)->last_buf = btin_fc_negative_int__list((*fc_arg)->last);
	if (((*fc_arg)->flag & ARG_FIRST) && (*fc_arg)->first > 0)
	{
		if (((*fc_arg)->first_buf = btin_fc_positive_int__list
			((*fc_arg)->first, temp, g_hist.last_fc)) == HIST_ERROR)
			return (HIST_ERROR);
	}
	else if ((*fc_arg)->flag & ARG_FIRST)
		(*fc_arg)->first_buf = btin_fc_negative_int__list((*fc_arg)->first);
	(*fc_arg)->last = ((*fc_arg)->flag & ARG_SECOND) ?
		btin_fc_calculate_nums__list((*fc_arg)->last_buf, temp) : 0;
	(*fc_arg)->first = ((*fc_arg)->flag & ARG_FIRST) ?
		btin_fc_calculate_nums__list((*fc_arg)->first_buf, temp) : 0;
	return (0);
}

/*
** If positive numeric argument is lower than the first in the
** history buffer according to the fc-number, there will be an
** "out of range" error
** If bigger than the last in teh history buffer - last command
** will be taken
*/

int				btin_fc_positive_int__list(int value, int from,
					int to)
{
	int			final;

	if (value > HISTORY_LIMIT)
		return (g_hist.last - 1);
	if ((from > to && !((value >= 1 && value < to) ||
		(value >= from && value <= HISTORY_LIMIT))) ||
		(from < to && !(value >= from)) || (from == to))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	final = value;
	if (from > to)
		final = value + HISTORY_LIMIT - from;
	else if (from < to && value < to)
		final = value - from;
	else if (from < to)
		final = g_hist.last - 1;
	return (final);
}

/*
** If negative numeric argument is for the command that
** is lower according to the number than the first in the history
** buffer - the first will be taken
** If "0" is given as the argument - the prevuious command (not the
** last that in the list mode is fc "-l") is printed
*/

int				btin_fc_negative_int__list(int value)
{
	int			final_buf;

	final_buf = g_hist.last;
	if (value <= 0)
	{
		value = (value == 0) ? -1 : value;
		final_buf += value;
		if (final_buf < 0)
			final_buf = 0;
	}
	return (final_buf);
}

/*
** The difference with the list mode is only for the
** last command: though for edit and exec mode the fc-command
** is not saved in the history list, we take the last command
** from the buffer. List mode fc-command is saved, so we need to take
** the last - 1
*/

int				btin_fc_positive_int__exec(int value, int from,
					int to)
{
	int			final;

	if (value > HISTORY_LIMIT)
		return (g_hist.last);
	if ((from > to && !((value >= 1 && value < to) ||
		(value >= from && value <= HISTORY_LIMIT))) ||
		(from < to && !(value >= from)) || (from == to))
	{
		error_handler(VARIABLE_ERROR | (ERR_HISTORY_NUM << 9), "fc");
		return (HIST_ERROR);
	}
	final = value;
	if (from > to)
		final = value + HISTORY_LIMIT - from;
	else if (from < to && value < to)
		final = value - from;
	else if (from < to)
		final = g_hist.last;
	return (final);
}

/*
** The difference with the list mode is only for the
** last command: though for edit and exec mode the fc-command
** is not saved in the history list, we take the last command
** from the buffer. List mode fc-command is saved, so we need to take
** the last - 1
*/

int				btin_fc_negative_int__exec(int value)
{
	int			final;

	final = g_hist.last;
	value = (value == 0) ? -1 : value;
	final += value + 1;
	if (final < 0)
		final = 0;
	return (final);
}