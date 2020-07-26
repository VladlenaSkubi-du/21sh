/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:03:36 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:03:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "readline.h"

int				sescape_init(void)
{
	char		*seq_base[SESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[D";
	return (sescape_check(seq_base));
}

int				ssequence_process(int sequence_num)
{
	int				(*seq_action[SESC_NUM])(void);

	seq_action[0] = sesc_right;
	seq_action[1] = sesc_left;
	return ((*seq_action[sequence_num])());
}

int				sescape_check(char **seq_base)
{
	int		i;
	char	buff[16];
	int		stage;

	i = 0;
	ft_bzero(buff, 16);
	while (read(STDIN_FILENO, buff + i, 1))
	{
		stage = 0;
		while (stage < SESC_NUM)
		{
			if (!ft_strncmp(buff, seq_base[stage], i + 1))
				break ;
			stage++;
		}
		if (stage == SESC_NUM)
			return (bell_sound());
		if (!ft_strncmp(buff, seq_base[stage], ft_strlen(seq_base[stage]) + 1))
			return (ssequence_process(stage));
		i++;
	}
	return (0);
}

int				sesc_left(void)
{
	if (g_rline.pos < 1)
		return (bell_sound());
	g_rline.pos--;
	write(STDOUT_FILENO, "\033[D", 3);
	return (0);
}

int				sesc_right(void)
{
	if (g_rline.pos >= g_rline.cmd_len ||
			g_rline.pos + g_prompt.prompt_len >= g_screen.ws_col)
		return (bell_sound());
	g_rline.pos++;
	write(STDOUT_FILENO, "\033[C", 3);
	return (0);
}
