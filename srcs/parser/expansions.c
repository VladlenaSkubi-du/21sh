/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:48:27 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/06 18:06:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

int			tilda_expansion(t_cmd **cmd_part)
{
	int		i;
	char	*find;
	char	*env_home;

	i = -1;
	while (++i < (*cmd_part)->len_tech - 1)
	{
		if ((*cmd_part)->tech[i] == TILDA &&
				((*cmd_part)->tech[i + 1] == SPACE ||
				(*cmd_part)->cmd[i + 1] == '/' ||
				(*cmd_part)->tech[i + 1] == ENTER ||
				(*cmd_part)->tech[i + 1] == END_T))
		{
			if ((env_home = find_env_value("HOME")) == NULL)
				find = home_from_etcpasswd();
			else
				find = ft_strdup(env_home);
			if (find == NULL)
				return (0);
			delete_or_insert_to_pline(cmd_part, i + 1, -1);
			expansion_pline_processing(cmd_part, &i, i + 1, find);
		}
	}
	return (0);
}

char		*home_from_etcpasswd(void)
{
	int		li;
	int		sy;
	int		fd;
	char	*line;
	char	**info;

	if ((li = find_in_variable(&sy, "UID")) < 0)
		return (NULL);
	fd = open("/etc/passwd", O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (ft_gnl(fd, &line) > 0)
	{
		info = ft_strsplit(line, ':');
		free(line);
		if (ft_strcmp(info[2], &g_envi[li][sy]) == 0)
		{
			line = ft_strdup(info[5]);
			ft_arrdel(info);
			return (line);
		}
	}
	ft_arrdel(info);
	close(fd);
	return (NULL);
}

int			dollar_expansion(t_cmd **cmd_part, char **str)
{
	t_cmd	*str_cmd;

	if (cmd_part == NULL && str)
	{
		str_cmd = init_parser_line(*str);
		dollar_expansion_loop(&str_cmd);
		*str = ft_strdup(str_cmd->cmd);
		free_parser_line(&str_cmd);
	}
	else
		dollar_expansion_loop(cmd_part);
	return (0);
}

int			dollar_expansion_loop(t_cmd **lcmd)
{
	int		i;
	int		start;
	char	*find;

	i = -1;
	while (++i < (*lcmd)->len_tech - 1)
	{
		if ((*lcmd)->tech[i] == DOLLAR && (*lcmd)->tech[i + 1] == DOLLAR)
		{
			start = i + 1;
			find = ft_strdup("$");
			delete_or_insert_to_pline(lcmd, start + 1, -2);
			dollar_expansion_processing(lcmd, &i, start, find);
		}
		else if ((*lcmd)->tech[i] == DOLLAR && (*lcmd)->tech[i + 1] == WORD_P)
		{
			start = i + 1;
			while (++i < (*lcmd)->len_tech && ft_isalnum((*lcmd)->cmd[i]))
				;
			find = ft_strndup((*lcmd)->cmd + start, i - start);
			delete_or_insert_to_pline(lcmd, i, start - i - 1);
			dollar_expansion_processing(lcmd, &i, start, find);
		}
	}
	return (0);
}

int			dollar_expansion_processing(t_cmd **lcmd, int *i,
				int start, char *find)
{
	char	*value;

	value = ft_strdup(find_env_value(find));
	free(find);
	if (value == NULL)
	{
		*i = start - 1;
		return (0);
	}
	expansion_pline_processing(lcmd, i, start, value);
	return (0);
}
