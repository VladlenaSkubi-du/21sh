#include "shell21.h"
#include "readline.h"

int				find_in_history(char *find)
{
	int			i;
	char		*found;

	i = g_hist.last;
	found = NULL;
	while (i >= 0)
	{
		found = ft_strstr(g_hist.hist[i], find);
		if (found != NULL)
			return (i);
		i--;
	}
	return (-1);
}

int				print_new_cmd_from_history(int coincidence)
{
	int			i;

	i = 0;
	clear_whole_line();
	while (g_hist.hist[coincidence][i])
	{
		char_add(g_hist.hist[coincidence][i], NULL);
		i++;
	}
	return (0);
}
