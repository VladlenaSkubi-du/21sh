/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:57:48 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 16:57:57 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin21.h"

int			parse_echo_flags(char **argv, t_ec *echo_flags, int i)
{
	int		j;

	echo_flags->n = 0;
	echo_flags->e = 0;
	echo_flags->up_e = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == '-')
				return (i + 1);
			else if (argv[i][j] == 'e')
				echo_flags->e = 1;
			else if (argv[i][j] == 'n')
				echo_flags->n = 1;
			else if (argv[i][j] == 'E')
				echo_flags->up_e = 1;
			else
				return (i);
		}
		i++;
	}
	return (i);
}

void		write_back_sl(char c)
{
	if (c == 'a')
		write(STDOUT_FILENO, "\a", 1);
	else if (c == 'b')
		write(STDOUT_FILENO, "\b", 1);
	else if (c == 'f')
		write(STDOUT_FILENO, "\f", 1);
	else if (c == 'n')
		write(STDOUT_FILENO, "\n", 1);
	else if (c == 'r')
		write(STDOUT_FILENO, "\r", 1);
	else if (c == 't')
		write(STDOUT_FILENO, "\t", 1);
	else if (c == 'v')
		write(STDOUT_FILENO, "\v", 1);
	else if (c == 'e')
		write(STDOUT_FILENO, "\033", 1);
}

void		write_e_echo(char **argv, int i)
{
	int		j;

	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] != '\\')
				write(1, &(argv[i][j]), 1);
			else
			{
				j++;
				write_back_sl(argv[i][j]);
			}
			j++;
		}
		i++;
		if (argv[i])
			write(1, " ", 1);
	}
}

void		write_text(char **argv, int i, t_ec *echo_flags)
{
	if (echo_flags->e && !echo_flags->up_e)
		write_e_echo(argv, i);
	else
	{
		while (argv[i])
		{
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
			if (argv[i])
				write(1, " ", 1);
		}
	}
	if (!echo_flags->n)
		write(1, "\n", 1);
}

int			btin_echo(t_ltree *pos)
{
	t_ec	*echo_flags;
	int		i;
	int		flags_check;

	flags_check = find_options(3, (char*[]){"enE", "--help"}, pos->ar_v);
	if (flags_check == 0x10000)
		return (usage_btin("echo"));
	else if (flags_check < 0)
		return (btin_return_exit_status());
	echo_flags = ft_xmalloc(sizeof(t_ec));
	i = parse_echo_flags(pos->ar_v, echo_flags, 1);
	write_text(pos->ar_v, i, echo_flags);
	free(echo_flags);
	return (0);
}
