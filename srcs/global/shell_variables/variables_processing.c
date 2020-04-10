#include "shell21.h"

/*
** The principle is that @g_env, @g_lovar and environ of the command
** are always equal and their size is @g_var_size
** If one of the arrays changes size, all are reallocated
*/

int					realloc_all_gvariables_array(void)
{
	g_env = ft_realloc_array(&g_env, g_var_size, g_var_size * 2);
	g_lovar = ft_realloc_array(&g_lovar, g_var_size, g_var_size * 2);
	g_var_size *= 2;
	return (0);
}

/*
** Is needed for finding a variable in an array
** Returns line on which the value is found or -1 if there is no
** value in the array
**
** @arr - is an array where the variable is being searched
** can be @g_env, @g_rdovar, @g_shvar or g_lovar (or env of the command)
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
	int				len_name; 

	i = 0;
	if (!arr)
		return (-1);
	len_name = ft_strlen(name);
	while (arr[i])
	{
		tmp = ft_strchri(arr[i], '=');
		if (ft_strncmp(arr[i], name, len_name) == 0)
		{
			*j = tmp + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
** Here we initiate environ for the command to be executed.
** Is done in substitution.c
*/

char				**init_exec_environ(void)
{
	char			**envir;
	int				i;

	envir = (char**)ft_xmalloc(sizeof(char*) * (g_var_size + 1));
	i = 0;
	while(g_env[i])
	{
		envir[i] = ft_strdup(g_env[i]);
		i++;
	}
	return (envir);
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