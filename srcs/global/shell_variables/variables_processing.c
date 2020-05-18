#include "shell21.h"

/*
** Is needed for finding a variable in an array
** Returns line on which the value is found or -1 if there is no
** value in the array
**
** @arr - is an array where the variable is being searched
** can be @g_env or @g_shvar
** @j is a pointer to the size_t that is being changed if the value
** is found. Shows the symble after '=' from which the variable value
** starts (example HISTSIZE=5, @j will be equal 9, and on arr[i][j] you
** will find the value 5)
** @name is a variable that we try to find (example, HISTSIZE=)
*/

int					find_in_variables(char **arr, int *j, char *name)
{
	int				i;
	int				tmp;

	i = 0;
	if (!arr)
		return (-1);
	while (arr[i])
	{
		tmp = ft_strchri(arr[i], '=');
		if (ft_strchrdiff(arr[i], name, '='))
		{
			*j = tmp + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
** @find is a name of the variable - in assignment it is malloced,
** so we free here. If there is no need to free, send NULL
** @insert is a full VARIABLE=VALUE to be inserted to the array,
** should be malloced!!
** @array is a pointer to the line with variable in the array
** (example: HISTSIZE=10 is in @g_shvar the 1st (starting from 0)
** so we put:
** insert_assign_to_arrays (NULL, ft_strdup("HISTSIZE=5"), &g_shvar[1]))
*/

int				insert_assign_to_arrays(char *find, char *insert,
					char **array)
{
	free(find);
	free(*array);
	*array = insert;
	return (0);
}

char			*find_var_in_arrays(char *find)
{
	char		*res;
	int			li;
	int			sy;

	li = -1;
	sy = -1;
	res = NULL;
	if ((li = find_in_variables(g_env, &sy, find)) != -1)
		res = ft_strdup(&g_env[li][sy]);
	else if ((li = find_in_variables(g_shvar, &sy, find)) != -1)
		res = ft_strdup(&g_shvar[li][sy]);
	return (res);
}

/*
** Adding new to @g_env (shell environment)
** Can be done only with builtin export (export FOO=bar)
*/

int				add_to_environment_variables(char *add)
{
	int			num;
	int			size;
	
	num = 0;
	size = save_env_size(0, 1);
	while (g_env[num])
		num++;
	if (num == size)
	{
		g_env = ft_realloc_array(&g_env, size, size * 2);
		size *= 2;
	}
	g_env[num] = ft_strdup(add);
	save_env_size(size, 0);
	return (0);
}