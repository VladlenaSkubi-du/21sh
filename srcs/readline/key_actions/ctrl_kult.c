#include "shell21.h"
#include "readline.h"

/*
** Comes to the function after pushing ctrl + k
** Cuts the cmd-line starting from the cursor till the end
** By ctrl-p can insert the line part cut
*/

int			make_ctrl_k(void)
{
	char			*save_yank;

	check_after_line();
	if (g_rline.pos < 0 || g_rline.pos == g_rline.cmd_len)
		return (incorrect_sequence());
	save_yank = ft_strdup(g_rline.cmd + g_rline.pos);
	g_rline.cmd_len -= ft_strlen(g_rline.cmd + g_rline.pos);
	make_ctrl_p(0, save_yank);
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd + g_rline.pos,
		ft_strlen(g_rline.cmd + g_rline.pos));
	return (0);
}

/*
** Comes to the function after pushing ctrl + u
** Cuts the cmd-line starting from the cursor till the beginning
** By ctrl-p can insert the line part cut
*/

int			make_ctrl_u(void)
{
	int				pos_old;
	char			*swap;
	int				len_swap;
	char			*save_yank;

	check_after_line();
	if (g_rline.pos <= 0)
		return (incorrect_sequence());
	pos_old = g_rline.pos;
	while (g_rline.pos)
		key_left_proc();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	save_yank = (pos_old == g_rline.cmd_len) ?
		ft_strdup(g_rline.cmd + g_rline.pos) :
		ft_strndup(g_rline.cmd + g_rline.pos, pos_old - g_rline.pos);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + pos_old;
	len_swap = ft_strlen(swap);
	ft_strcpy(g_rline.cmd, swap);
	ft_bzero(g_rline.cmd + len_swap, g_rline.cmd_buff_len - len_swap);
	g_rline.cmd_len = 0 + len_swap;
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

/*
** Comes to the function after pushing ctrl + l
** Clears the terminal-screen and inserts the cmd-line
*/

int			make_ctrl_l(void)
{
	check_after_line();
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	putcap("cl");
	g_prompt.prompt_func();
	g_rline.pos = 0;
	g_rline.pos_x = prompt_len();
	g_rline.pos_y = 0;
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

/*
** Comes to the function after pushing ctrl + t
** Swaps 2 chars within the line, depending of the cursor position
** If cursor is on the first char in the line - swaps chars the cursor
** is on and the next
** If cursor is after the cmd-line end - swaps two previous chars
** In other cases swaps chars the cursor is on and the previous
** After swapping moves cursor after the last char swapped
*/

int			make_ctrl_t(void)
{
	check_after_line();
	if (g_rline.cmd_len == 1 || g_rline.cmd_len < 0)
		return (incorrect_sequence());
	if (g_rline.pos == 0 || g_rline.pos == g_rline.cmd_len)
		return (make_ctrl_t_begend(g_rline.cmd_len));
	else
	{
		swap_chars(g_rline.cmd, g_rline.pos, g_rline.pos - 1);
		if (front_move_one_char_left(g_rline.pos_x))
			return (incorrect_sequence());
		g_rline.pos--;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	return (0);
}

/*
** Dealing with two exceptions: when cursor is in the beginning
** and after the end - on the last position in the line
*/

int			make_ctrl_t_begend(int len)
{
	int				pos_old;

	if (g_rline.pos == 0)
	{
		swap_chars(g_rline.cmd, g_rline.pos + 1, g_rline.pos);
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else if (g_rline.pos == len)
	{
		swap_chars(g_rline.cmd, g_rline.pos - 1, g_rline.pos - 2);
		pos_old = g_rline.pos - 2;
		move_cursor_from_old_position(pos_old, 'l');
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	return (0);
}