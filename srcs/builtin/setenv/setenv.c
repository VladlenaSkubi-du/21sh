/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:49:07 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 18:12:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin.h"

int		change_or_add(char *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arg[i] != '=')
	    i++;
	tmp = ft_strndup(arg, i);
	if ((i = find_in_variable(&j, tmp)) >= 0)
	{
	    if (g_envi[i][0] && (g_envi[i][0] & READONLY))
	        return (setenv_error(&tmp, i));
	    change_env_value(arg, i);
	    g_envi[i][0] |= ENV_VIS;
	}
	else
	{
	    i = add_new_env(arg);
	    g_envi[i][0] |= ENV_VIS;
	}
	free(tmp);
	return (0);
}

int		do_vis(char *arg)
{
	int		i;
	int		j;

	if ((i = find_in_variable(&j, arg)) < 0)
	    return (1);
	g_envi[i][0] |= ENV_VIS;
	return (0);
}

int		setenv_add_vis(t_exec *exec)
{
	int		i;
	// char	*new_var;

	i = 0;
	while (exec->argv[++i])
	{
		if (exec->argv[i][0] == '-')
			continue ;
		if (ft_strrchr(exec->argv[i], '='))
		{
			change_or_add(exec->argv[i]);
			// new_var = ft_parsing_str(exec->argv[i]);
			// change_or_add(new_var);
			// free(new_var);
		}
		else
			do_vis(exec->argv[i]);
	}
	return (0);
}

int		setenv_p(void)
{
	int		i;
	char	*j;

	i = 0;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & ENV_VIS))
		{
			j = ft_strchr(g_envi[i] + 1, '=');
			ft_printf("setenv %.*s", j - (g_envi[i] + 1), g_envi[i] + 1);
			if (j && j + 1)
				ft_printf("=\"%s\"\n", j + 1);
			else
				ft_putchar('\n');
		}
		i++;
	}
	return (0);
}

int		btin_setenv(t_exec *exec)
{
	int		flags;

	flags = find_options(2, (char*[]){"p", "--help"}, exec->argv);
	if (flags == 0x10000)
		return (usage_btin("setenv"));
	else if (flags < 0)
		return (btin_return_exit_status());
	if (exec->argc == 1 || flags == 1)
		return (setenv_p());
	else
		return (setenv_add_vis(exec));
	return (0);
}
