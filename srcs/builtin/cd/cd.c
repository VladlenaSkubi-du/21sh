/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:57:32 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/25 16:16:30 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "builtin42.h"

char		*ft_join(char *path, char *src_path)
{
	char	*tmp;

	tmp = ft_strdup("1");
	if (src_path == NULL)
		tmp = ft_strrejoin(tmp, get_pwd_value());
	else
		tmp = ft_strrejoin(tmp, src_path);
	tmp = ft_strrejoin(tmp, "/");
	tmp = ft_strrejoin(tmp, path);
	return (tmp);
}

int			ft_error(char *name, int en)
{
	char	*tmp;
	char	*new_name;

	new_name = NULL;
	tmp = ft_strdup("cd: ");
	if (name)
		tmp = ft_strrejoin(tmp, name);
	if (en == 1)
		tmp = ft_strrejoin(tmp, ": string not in pwd");
	else if (en == 2)
		tmp = ft_strrejoin(tmp, ": no such file or directory");
	else if (en == 3)
		tmp = ft_strrejoin(tmp, ": permission denied");
	else if (en == 4)
		tmp = ft_strrejoin(tmp, ": not a directory");
	else if (en == 5)
		tmp = ft_strrejoin(tmp, "too many arguments");
	else if (en == 6)
		tmp = ft_strrejoin(tmp, "OLDPWD not set");
	else if (en == 7)
		tmp = ft_strrejoin(tmp, "HOME not set");
	error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
	free(tmp);
	free(new_name);
	return (1);
}

int			ft_cd_helper(void)
{
	error_handler(OPTIONS_REQUIRED | (ERR_BTIN_INVALID << 9), "cd");
	usage_btin("cd");
}

int			btin_cd(t_ltree *pos)
{
	int		i;
	t_cd	*flags;
	int		flags_check;

	flags_check = find_options(2, (char*[]){"LP", "--help"}, pos->ar_v);
	if (flags_check == 0x10000)
		return (usage_btin("cd"));
	if (flags_check < 0)
		return (btin_return_exit_status());
	flags = ft_xmalloc(sizeof(t_cd *));
	i = ft_cd_flags(pos->ar_v, flags);
	if (pos->ar_v[i] && pos->ar_v[i][0] == '-' && pos->ar_v[i][1] &&
			i > 0 && ft_strcmp(pos->ar_v[i - 1], "--"))
	{
		free(flags);
		return (ft_cd_helper());
	}
	if (ft_valid_cd(pos->ar_v, i) ||
			ft_cd_pars(pos->ar_v[i], pos->envir, flags))
	{
		free(flags);
		return (1);
	}
	free(flags);
	return (0);
}
