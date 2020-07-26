/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:36:11 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:36:12 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <builtin.h>

int				find_in_any_variable(char **env, int *j, char *name)
{
	int			i;
	int			tmp;
	int			len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (env[i])
	{
		tmp = ft_strchri(env[i], '=');
		if (ft_strncmp(env[i], name, len_name) == 0 &&
				(tmp == len_name))
		{
			*j = tmp + 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

int				exit_status_variables(int status)
{
	char		*tmp;
	char		*final;
	int			i;
	int			j;

	tmp = ft_itoa(status);
	i = find_in_variable(&j, "?");
	final = ft_strjoin("?=", tmp);
	change_env_value(final, i);
	free(final);
	free(tmp);
	return (0);
}
