/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:49:07 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 16:56:12 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin.h"

int		change_or_add(char *arg)
{
	int		i;
	int		j;
	char	*tmp;
	char	*error;

	i = 0;
	while (arg[i] != '=')
	    i++;
	tmp = ft_strndup(arg, i);
	if ((i = find_in_variable(&j, tmp)) >= 0)
	{
	    if (g_envi[i][0] && (g_envi[i][0] & READONLY))
	        return (export_error(&tmp, i));
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
	g_envi[i][0] |= SET_VIS;
	return (0);
}

int		export_add_vis(t_ltree *pos)
{
	int		i;
	char	*new_var;

	i = 0;
	while (pos->ar_v[++i])
	{
		if (pos->ar_v[i][0] == '-')
			continue ;
		if (ft_strrchr(pos->ar_v[i], '='))
		{
			new_var = ft_parsing_str(pos->ar_v[i]);
			change_or_add(new_var);
			free(new_var);
		}
		else
			do_vis(pos->ar_v[i]);
	}
	return (0);
}

int		export_p(void)
{
	int		i;
	char	*j;

	i = 0;
	while (g_envi[i])
	{
		if (g_envi[i][0] && (g_envi[i][0] & ENV_VIS))
		{
			j = ft_strchr(g_envi[i] + 1, '=');
			ft_printf("export %.*s", j - (g_envi[i] + 1), g_envi[i] + 1);
			if (j && j + 1)
				ft_printf("=\"%s\"\n", j + 1);
			else
				ft_putchar('\n');
		}
		i++;
	}
	return (0);
}

int		btin_export(t_ltree *pos)
{
	int		flags;

	flags = find_options(2, (char*[]){"p", "--help"}, pos->ar_v);
	if (flags == 0x10000)
		return (usage_btin("export"));
	else if (flags < 0)
		return (btin_return_exit_status());
	if (pos->ar_c == 1 || flags == 1)
		return (export_p());
	else
		return (export_add_vis(pos));
	return (0);
}
