#include "shell21.h"
#include "readline.h"

/*
** The front-part: we put cursor to the end of the line -
** only within the line we can use functions from cursor_position.c file
** because they use g_rline.pos - after that we print the menu-buffer
** and put the cursor back to the end of the cmd-line
** and back to the old position
** we also route here if all the lines can
** be printed within the terminal
**
** @g_compl.menu_buffer.buf_lines we need to understand
** how high we need to jump to the end of the cmd-line
** after the menu-printing
*/

int					print_menu(int max_len)
{
	int				len_x;
	int				len_y;
	int				pos_back;

	len_x = g_rline.pos_x;
	len_y = g_rline.pos_y;
	pos_back = g_rline.pos;
	g_compl.menu_buffer = menu_buf_init(g_compl.total, max_len);
	position_cursor_after_line(g_rline.cmd_len);
	if (g_screen.ws_row - g_rline.str_num >= g_compl.menu_buffer.buf_lines)
		return (print_menu_within_terminal(pos_back, len_x, len_y));
	return (print_menu_more_than_terminal(pos_back, len_x, len_y));
}

int					print_menu_within_terminal(int pos_back,
						int len_x, int len_y)
{
	int				i;

	i = -1;
	while (++i < g_compl.menu_buffer.word_nb)
		if (g_compl.menu[i] && g_compl.menu[i][0])
			buffer_col_print(g_compl.menu[i], &g_compl.menu_buffer);
	position_cursor_after_menu_back(len_x, len_y,
		g_compl.menu_buffer.buf_lines, pos_back);
	g_rline.flag |= TAB;
	return (0);
}

int					print_menu_more_than_terminal(int pos_back,
						int len_x, int len_y)
{
	int				i;

	i = -1;
	if (ask_output(g_compl.total, g_compl.menu_buffer.buf_lines,
			pos_back, len_x) == 1)
		return (1);
	while (++i < g_compl.menu_buffer.word_nb)
		if (g_compl.menu[i] && g_compl.menu[i][0])
			buffer_col_print(g_compl.menu[i], &g_compl.menu_buffer);
	after_big_menu(pos_back, len_x, len_y);
	return (1);
}

int					print_menu_buf_after_insert(int pos_back)
{
	int				len_back;
	int				len_x_back;
	int				len_y_back;

	position_cursor_after_line(g_rline.cmd_len);
	buffer_col_finish(&g_compl.menu_buffer);
	front_set_cursor_jmp(&len_back, &len_x_back, &len_y_back, 0);
	position_cursor_after_menu_back(len_x_back, len_y_back,
		g_compl.menu_buffer.buf_lines, pos_back);
	return (0);
}

/*
** After we printed any kind of comment and message, we need
** to turn back to the cmd-line and come back to the position
** from which a key-sequence was pushed
*/

int					position_cursor_after_menu_back(int len_x, int len_y,
						int buf_lines, int pos_back)
{
	int				i;
	int				jump;

	i = -1;
	position_cursor("ch", 0, len_x);
	while (++i < buf_lines)
		putcap("sr");
	if (g_rline.pos_x == 0 && g_rline.pos_y == g_rline.str_num &&
			pos_back != g_rline.cmd_len)
		tputs(g_cap.up, 1, printc);
	if (g_rline.str_num > 1)
	{
		jump = g_rline.str_num - 1 - len_y;
		if (jump > 1)
			position_cursor("UP", 0, jump);
		else if (jump == 1)
			tputs(g_cap.up, 1, printc);
	}
	g_rline.pos = pos_back;
	g_rline.pos_x = len_x;
	g_rline.pos_y = len_y;
	return (0);
}
