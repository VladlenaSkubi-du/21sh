/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:14:07 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 17:14:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <builtin.h>

int		pwd_error(char c, int en)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strdup("pwd: -");
	if (en == 1)
	{
		tmp = ft_strrejoin(tmp, str);
		tmp = ft_strrejoin(tmp, " :invalid parameter\npwd: usage: pwd [-LP]");
	}
	error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
	free(tmp);
	return (1);
}

int		btin_pwd_valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 1;
		if (argv[i][0] == '-')
			while (argv[i][j])
			{
				if (argv[i][j] != 'L' && argv[i][j] != 'P')
					return (pwd_error(argv[i][j], 1));
				j++;
			}
		i++;
	}
	return (0);
}

int		btin_pwd(t_exec *exec)
{
	t_cd	*flags;
	int		i;
	int		j;
	char	dir[MAXDIR];

	if (btin_pwd_valid(exec->argv))
		return (1);
	flags = ft_xmalloc(sizeof(t_cd *));
	i = ft_cd_flags(exec->argv, flags);
	if (flags->l)
	{
		i = find_in_variable(&j, "PWD");
		ft_putstr(g_envi[i] + j);
	}
	else
	{
		getcwd(dir, MAXDIR);
		ft_putstr(dir);
	}
	ft_putchar('\n');
	free(flags);
	return (0);
}
