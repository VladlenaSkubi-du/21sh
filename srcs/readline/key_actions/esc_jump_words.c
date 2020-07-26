/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_jump_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:03:01 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:03:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "readline.h"

/*
** Comes to these functions after pushing esc + b
** Jumps to the token from with the word (alpha-numeric sequence)
** starts and then to the first char in the word
*/

int			word_left_proc(void)
{
	int				i;
	int				pos_old;

	if (g_rline.pos == 1 || g_rline.pos == 2)
		return (word_left_onetwo_chars());
	else if (g_rline.pos <= 0)
		return (incorrect_sequence());
	i = g_rline.pos - 1;
	while (i > 0 && g_rline.cmd[i - 1] && g_rline.cmd[i])
	{
		if (ft_isalnum(g_rline.cmd[i]) && !ft_isalnum(g_rline.cmd[i - 1]))
			break ;
		i--;
	}
	pos_old = i;
	return (move_cursor_from_old_position(pos_old, 'l'));
}

/*
** If cursor stays on the first or the second symbol in the line
** that is exception from the main principle used
*/

int			word_left_onetwo_chars(void)
{
	int				pos_old;

	pos_old = g_rline.pos;
	if (front_move_one_char_left(g_rline.pos_x))
		return (incorrect_sequence());
	g_rline.pos--;
	if (pos_old == 2)
	{
		if (front_move_one_char_left(g_rline.pos_x))
			return (incorrect_sequence());
		g_rline.pos--;
	}
	return (0);
}

/*
** Comes to these functions after pushing esc + f
** Jumps to the token after the word (alpha-numeric sequence)
*/

int			word_right_proc(void)
{
	int				i;
	int				pos_old;

	if (g_rline.pos == g_rline.cmd_len || g_rline.pos < 0)
		return (incorrect_sequence());
	else if (g_rline.pos == g_rline.cmd_len - 1)
	{
		if (front_move_one_char_right(g_rline.pos))
			return (incorrect_sequence());
		g_rline.pos++;
		return (0);
	}
	i = g_rline.pos + 1;
	while (g_rline.cmd[i] && g_rline.cmd[i - 1])
	{
		if (!ft_isalnum(g_rline.cmd[i]) && ft_isalnum(g_rline.cmd[i - 1]))
			break ;
		i++;
	}
	pos_old = i;
	return (move_cursor_from_old_position(pos_old, 'r'));
}

/*
** Is used in other keys dealing with words
*/

char		*save_word(int *i, char *cmd, int pos)
{
	char			*word;

	word = NULL;
	*i = 0;
	while (ft_isalnum(cmd[pos + *i]))
		(*i)++;
	word = ft_strndup(cmd + pos, *i);
	return (word);
}

/*
** Is used in other keys dealing with words
*/

char		*save_end(int pos_back)
{
	char			*end;
	int				pos_now;

	end = NULL;
	pos_now = g_rline.pos;
	move_cursor_from_old_position(pos_back, 'r');
	if (word_right_proc())
		return (end);
	end = ft_strdup(g_rline.cmd + g_rline.pos);
	move_cursor_from_old_position(pos_now, 'l');
	return (end);
}
