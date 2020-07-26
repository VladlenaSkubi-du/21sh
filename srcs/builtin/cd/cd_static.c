/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_static.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:31:41 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 17:07:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <cd.h>

static char		*g_oldpwd;
static char		*g_pwd;

char	*get_oldpwd_value(void)
{
	return (g_oldpwd);
}

int		change_oldpwd_value(char *str)
{
	free(g_oldpwd);
	g_oldpwd = ft_strdup(str);
	return (0);
}

int		cd_free_static(void)
{
	free(g_oldpwd);
	free(g_pwd);
	return (0);
}

char	*get_pwd_value(void)
{
	return (g_pwd);
}

int		change_pwd_value(char *str)
{
	free(g_pwd);
	g_pwd = ft_strdup(str);
	return (0);
}
