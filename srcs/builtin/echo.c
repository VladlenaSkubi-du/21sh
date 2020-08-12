/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:57:48 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/08/12 21:39:54 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin.h"

int			parse_echo_flags(char **argv, t_ec *echo_flags, int i)
{
	int		j;

	echo_flags->n = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == '-')
				return (i + 1);
			else if (argv[i][j] == 'n')
				echo_flags->n = 1;
			else
				return (i);
		}
		i++;
	}
	return (i);
}

void		write_text(char **argv, int i, t_ec *echo_flags)
{
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!echo_flags->n)
		write(STDOUT_FILENO, "\n", 1);
}

int			btin_echo(t_exec *exec)
{
	t_ec	*echo_flags;
	int		i;
	int		flags_check;

	flags_check = find_options(1, (char*[]){"n", "--help"}, exec->argv);
	if (flags_check == 0x10000)
		return (usage_btin("echo"));
	else if (flags_check < 0)
		return (btin_return_exit_status());
	echo_flags = ft_xmalloc(sizeof(t_ec));
	i = parse_echo_flags(exec->argv, echo_flags, 1);
	write_text(exec->argv, i, echo_flags);
	free(echo_flags);
	return (0);
}
