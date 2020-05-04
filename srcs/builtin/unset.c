#include "shell21.h"
#include "builtin.h"

int			btin_unset(t_exec *pos)
{
	int		unused;
	int		j;
	int		i;

	i = 1;
	while (i < pos->argc)
	{
		if ((j = find_in_variables(g_env, &unused, pos->argv[i])) != -1)
			unset_from_array(&g_env, j);
		if ((j = find_in_variables(g_lovar, &unused, pos->argv[i])) != -1)	
			unset_from_array(&g_lovar, j);
		i++;
	}
	return (0);	
}