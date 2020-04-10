#include "shell21.h"
#include "builtin.h"

/*
** Activation and disactivation of flags according to the mode
*/

int					btin_fc_edit_mode_flags_off(int *flags)
{
	if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	if (!(*flags & FLAG_E))
		*flags |= FLAG_E;
	if (*flags & FLAG_N)
		*flags &= ~FLAG_N;
	return (HIST_EXEC);
}

int					btin_fc_exec_mode_flags_off(int *flags)
{
	if (!(*flags & FLAG_S))
		*flags |= FLAG_S;
	if (*flags & FLAG_E)
		*flags &= ~FLAG_E;
	if (*flags & FLAG_L)
		*flags &= ~FLAG_L;
	if (*flags & FLAG_R)
		*flags &= ~FLAG_R;
	if (*flags & FLAG_N)
		*flags &= ~FLAG_N;
	return (HIST_EXEC);
}

int					btin_fc_list_mode_flags_off(int *flags)
{
	if (!(*flags & FLAG_L))
		*flags |= FLAG_L;
	if (*flags & FLAG_E)
		*flags &= ~FLAG_E;
	if (*flags & FLAG_S)
		*flags &= ~FLAG_S;
	return (HIST_EXEC);
}

/*
** Checking options in the arguments line - list mode
*/

int					btin_fc_list_other_flags(char argvij, int *flags)
{
	if (!(argvij == 'r' || argvij == 'n' || argvij == 'l'))
	{
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "fc");
		usage_btin("fc");
		return (HIST_ERROR);
	}
	else if (argvij == 'r')
		*flags |= FLAG_R;
	else if (argvij == 'n')
		*flags |= FLAG_N;
	return (0);
}

/*
** Checking options in the arguments line - exec mode
*/

int					btin_fc_exec_other_flags(char argvij)
{
	if (argvij == 'r' || argvij == 'n' ||
		argvij == 'l' || argvij == 's')
		return (0);
	else if (!(argvij == 'r' || argvij == 'n' ||
		argvij == 'l' || argvij == 's'))
	{
		error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "fc");
		usage_btin("fc");
		return (HIST_ERROR);
	}
	return (0);
}