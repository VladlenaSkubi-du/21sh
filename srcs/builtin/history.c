#include "shell21.h"
#include "builtin.h"

/*
** The list of the whole history buffer
** If HISTORY_LIMIT or 32767 is reached, numeration continues with 1
*/

int					btin_history(void)
{
	int				i;
	int				num;
	int				tmp;

	i = 0;
	num = g_hist.last_fc - ((g_hist.last + 1 == g_hist.len) ?
		g_hist.len - 1 : g_hist.last) + 1;
	num += (num < 1) ? HISTORY_LIMIT : 0;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		if (num > HISTORY_LIMIT)
			num = 1;
		tmp = ft_strlen(g_hist.hist[i]);
		if (tmp > 0 && g_hist.hist[i][tmp - 1] == '\n')
			tmp -= 1;
		ft_printf("%5d  %.*s\n", num, tmp, g_hist.hist[i]);
		num++;
		i++;
	}
	return (0);
}
