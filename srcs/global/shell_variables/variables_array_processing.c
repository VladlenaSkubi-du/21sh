#include "shell21.h"

/*
** Adding new to @g_env (shell environment)
** Can be done only with builtin export (export FOO=bar)
*/

int				add_to_environment_variables(char *add)
{
	int			num;
	
	num = 0;
	while (g_env[num])
		num++;
	(num == g_var_size) ? realloc_all_gvariables_array() : 0;
	g_env[num] = ft_strdup(add);
	return (0);
}

/*
** Adding new to @g_lovar (shell local variables)
** Can be done only by assignment (foo=bar)
** @add is already malloced - can come only from find_assignment_in_vars
*/

int				add_to_local_variables(char *add)
{
	int			num;
	
	num = 0;
	while (g_lovar[num])
		num++;
	if (num == g_var_size)
		realloc_all_gvariables_array();
	g_lovar[num] = add;
	return (0);
}

/*
** Adding new variable to the environ of the command to be executed
** First we try to find if it already exists and insert if it is found
** Then we add if the @add is a new variable
*/

int				add_new_to_exec_env(char ***array, char **add)
{
	int			i;
	int			li;
	int			sy;
	char		*find;

	i = 0;
	find = ft_strndup(*add, ft_strrchri(*add, '='));
	if ((li = find_in_variables(g_env, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, *add,	&g_env[li]));
	else
	{
		while (array[0][i])
			i++;
		if (i == g_var_size)
		{
			ft_realloc_array(array, g_var_size, g_var_size * 2);
			realloc_all_gvariables_array();
		}
		free(find);
		array[0][i] = *add;
	}	
	return (0);
}

int				unset_from_array(char ***arr, int i)
{
	char		**tmp;

	tmp = *arr;
	if (i == 0)
	{
		free(tmp[i]);
		tmp[0] = NULL;
		return (0);
	}
	free(tmp[i]);
	tmp[i] = tmp[i + 1];
	i++;
	while (tmp[i])
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	return (0);
}