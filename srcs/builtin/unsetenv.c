/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:07 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:30:16 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin.h"

void	error_unset(char *find)
{
	char	*error;

	error = ft_strjoin("unsetenv: ", find);
	error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
	free(error);
}

int		btin_unsetenv(t_exec *exec)
{
	int		i;
	int		tmp;
	int		j;
	char	*find;

	i = 0;
	while (++i < exec->argc)
	{
		if ((tmp = ft_strchri(exec->argv[i], '=')) >= 0)
			find = ft_strndup(exec->argv[i], tmp);
		else
			find = ft_strdup(exec->argv[i]);
		if ((j = find_in_variable(&tmp, find)) < 0)
		{
			free(find);
			continue ;
		}
		if (g_envi[j][0] && (g_envi[j][0] & READONLY))
			error_unset(find);
		else
			ft_arrshift(g_envi + j + 1, g_var_size - j, -1);
		free(find);
	}
	return (0);
}
