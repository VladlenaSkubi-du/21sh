/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:04:40 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:04:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "readline.h"

/*
** If buffer is not enough for the new char to insert,
** the g_rline.cmd will be realloced and if there is
** overfill of int (@g_rline.cmd_len or g_rline.cmd_buff_len)
** g_rline.cmd will be sent to parser as it is
*/

int					char_add(char c, char *color)
{
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
		realloc_readline_cmd();
	g_rline.cmd_len++;
	if (g_rline.cmd_len + 1 < 0 || g_rline.cmd_buff_len + 1 < 0)
		return (OUT);
	insert_char(c, color);
	return (0);
}

/*
** putcap("cd") - clearing till the end of the screen
** putcap("sf") - if cmd-line finishes on the most right position in terminal,
** the cursor should jump to the next line
** 'm' is a flag for main part (there are also comments or 'c' flag possible)
*/

int					insert_char(char c, char *color)
{
	if (g_rline.cmd[g_rline.pos] != '\0')
	{
		ft_strshift(g_rline.cmd + g_rline.pos, 1);
		g_rline.cmd[g_rline.pos] = c;
		tputs(g_cap.cd, 1, printc);
		front_insert_one_char(g_rline.cmd[g_rline.pos],
			g_rline.pos_x, 'm', color);
		g_rline.pos++;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
	{
		g_rline.cmd[g_rline.pos] = c;
		g_rline.pos++;
		front_insert_one_char(c, g_rline.pos_y, 'm', color);
	}
	return (0);
}

/*
** All the "interactive" questions to user from shell are orange
** and inserted through this function. in order to use readline
** "engine" - the length of comments, position for each letter in
** terminal (x and y) are also counted
*/

int					front_insert_by_letters(char *str, int *pos_x)
{
	int				i;

	i = 0;
	while (str[i])
	{
		front_insert_one_char(str[i], *pos_x, 'c', ORANGE);
		(*pos_x)++;
		if (*pos_x == g_screen.ws_col)
			*pos_x = 0;
		i++;
	}
	return (0);
}

int					front_insert_cmd_till_the_end(int str_num_print)
{
	int				pos_back;
	int				pos_x_back;
	int				pos_y_back;

	if (g_rline.pos > 0 && g_rline.pos_x == 0 &&
			g_rline.cmd[g_rline.pos - 1] != '\n')
		g_rline.str_num = str_num_print - 1;
	else
		g_rline.str_num = str_num_print;
	while (g_rline.pos < g_rline.cmd_len)
	{
		front_insert_one_char(g_rline.cmd[g_rline.pos],
			g_rline.pos_x, 'm', NULL);
		g_rline.pos++;
	}
	front_set_cursor_jmp(&pos_back, &pos_x_back, &pos_y_back, 0);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}

/*
** @Flag == 1 means "save position"
** @flag == 0 means "return position"
*/

int					front_set_cursor_jmp(int *pos, int *pos_x,
						int *pos_y, int flag)
{
	static int		pos_save;
	static int		pos_x_save;
	static int		pos_y_save;

	if (flag == 1)
	{
		pos_save = *pos;
		pos_x_save = *pos_x;
		pos_y_save = *pos_y;
	}
	if (flag == 0)
	{
		*pos = pos_save;
		*pos_x = pos_x_save;
		*pos_y = pos_y_save;
	}
	return (0);
}
