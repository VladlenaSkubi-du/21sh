/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:36:51 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:36:53 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*
** Changing shell (global) environment variable by its index
** @new_val should be a NAME=VALUE string
** In the function we copy the first flag-bit, free the old
** NAME=VALUE string, allocate memory for the new string + the first
** bit and copy the string
*/

int		change_env_value(char *new_val, int i)
{
	char	bit;

	if (g_envi[i] == NULL)
		return (-1);
	bit = g_envi[i][0];
	free(g_envi[i]);
	g_envi[i] = (char *)ft_xmalloc(ft_strlen(new_val) + 2);
	g_envi[i][0] = bit;
	ft_strcpy(g_envi[i] + 1, new_val);
	if (ft_strncmp(new_val, "HISTSIZE=", 9) == 0)
		check_if_histsize_changed(g_envi[i] + 1);
	return (0);
}

/*
** Adding a variable to a shell (global) environment
** @name should be a NAME=VALUE string
** In the function we go through all the environment list counting
** its size and add a string after the last variable
** All the new variables become visible by builtin "set"
** If the variable needs other flags, the function returns its
** index, so the function-customer can add bit-flags by the index
*/

int		add_new_env(char *name)
{
	int		i;

	i = 0;
	while (g_envi[i])
		i++;
	if (i >= g_var_size)
	{
		g_envi = ft_realloc_array(&g_envi, g_var_size, g_var_size * 2);
		g_var_size *= 2;
	}
	g_envi[i] = (char *)ft_xmalloc(ft_strlen(name) + 2);
	ft_strcpy(g_envi[i] + 1, name);
	g_envi[i][0] |= ENV_VIS;
	if (ft_strncmp(name, "HISTSIZE=", 9) == 0)
		check_if_histsize_changed(g_envi[i] + 1);
	return (i);
}

/*
** Function needed only for parser to add visible in "env" command
** variables to the local envaronment for each command in the shell
** The @arr coming should be a pointer to an allocated memory
** If there is nothing in the array coming, @size should be 0 and
** in the *arr should be a NULL-string
** Otherwise size should be as the number of
** printable (not empty) lines
*/

int		form_local_envir(char ***arr, int size)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = *arr;
	while (g_envi[++i])
		if (g_envi[i][0] & ENV_VIS)
			j++;
	tmp = ft_realloc_array(arr, size, size + j + 1);
	i = 0;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & ENV_VIS))
		{
			tmp[size] = ft_strdup(g_envi[i] + 1);
			size++;
		}
		i++;
	}
	*arr = tmp;
	return (0);
}

/*
** Goes through the array of shell environment variables and
** changes the @j-index coming (points to the beginning of VALUE)
** and returns an index of the NAME=VALUE variable
** If the @name is not found, program returns -1
*/

int		find_in_variable(int *j, char *name)
{
	int			i;
	int			tmp;
	int			len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (g_envi[i])
	{
		tmp = ft_strchri(g_envi[i] + 1, '=');
		if (ft_strncmp(g_envi[i] + 1, name, len_name) == 0 &&
				(tmp == len_name))
		{
			*j = tmp + 2;
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
** The function-shell for the find_in_variable function
** Returns a pointer to the beginning of the VALUE
** @str is a name that is searched in the shell
** global environment
*/

char	*find_env_value(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = find_in_variable(&j, str);
	if (i == -1)
		return (NULL);
	return (&g_envi[i][j]);
}
