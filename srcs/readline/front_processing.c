/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:04:23 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:04:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "readline.h"

/*
** In order to clean something after the cmd-line,
** history or auto-completion, we need to jump to the end
** of the cmd-line and to the next line, clear everything
** by the temcap code and move cursor to the position
** it had before clearing
*/

int					clean_after_line(void)
{
	int				pos_back;
	int				len_back;
	int				len_x_back;
	int				len_y_back;

	pos_back = g_rline.pos;
	position_cursor_after_line(g_rline.cmd_len);
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
		&g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_set_cursor_jmp(&len_back, &len_x_back, &len_y_back, 0);
	position_cursor("ch", 0, len_x_back);
	tputs(g_cap.up, 1, printc);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}

/*
** Here we put cursor to the end of the line after ENTER is
** pushed
*/

int					position_cursor_after_line(int len)
{
	if (g_rline.pos == 0 && len == 0)
		tputs(g_cap.sf, 1, printc);
	else
	{
		move_cursor_from_old_position(len, 'r');
		tputs(g_cap.sf, 1, printc);
	}
	return (0);
}

/*
** Does the same as esc-r key sequence but only
** clears in the back and front
** Is used internally, for user there is esc-r
*/

int					clear_whole_line(void)
{
	while (g_rline.pos)
		key_left_proc();
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	return (0);
}

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_right(int pos_x)
{
	if (pos_x >= 0 && pos_x < g_screen.ws_col - 1 &&
		g_rline.cmd[g_rline.pos] != '\n')
	{
		tputs(g_cap.nd, 1, printc);
		g_rline.pos_x++;
	}
	else if (pos_x == g_screen.ws_col - 1 ||
		g_rline.cmd[g_rline.pos] == '\n')
	{
		tputs(g_cap.cr, 1, printc);
		tputs(g_cap.dow, 1, printc);
		g_rline.pos_x = 0;
		g_rline.pos_y++;
	}
	else
		return (1);
	return (0);
}

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_left(int pos_x)
{
	int				prev_x;

	prev_x = 0;
	if (pos_x > 0)
	{
		tputs(g_cap.le, 1, printc);
		g_rline.pos_x--;
	}
	else if (pos_x == 0)
	{
		if (g_rline.pos > 0 &&
				g_rline.cmd[g_rline.pos - 1] == '\n')
			prev_x = count_x_position_new_line(g_rline.pos - 2);
		else
			prev_x = g_screen.ws_col - 1;
		position_cursor("ch", 0, prev_x);
		tputs(g_cap.up, 1, printc);
		g_rline.pos_x = prev_x;
		g_rline.pos_y--;
	}
	else
		return (1);
	return (0);
}
