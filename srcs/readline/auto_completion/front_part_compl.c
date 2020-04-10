#include "shell21.h"
#include "readline.h"

t_completion		g_menu_buf;

/*
** The front-part: we put cursor to the end of the line -
** only within the line we can use functions from cursor_position.c file
** because they use g_rline.pos - after that we print the menu-buffer
** and put the cursor back to the end of the cmd-line
** and back to the old position
**
** @menu_lines_num we need to understand how high we need to jump
** to the end of the cmd-line after the menu-printing
*/

int					print_menu(int pos_back, char **menu,
						int total, int max_len)
{
	int				len_x;
	int				len_y;
	int				i;

	i = -1;
	len_x = g_rline.pos_x;
	len_y = g_rline.pos_y;
	position_cursor_for_menu(g_rline.cmd_len);
	g_menu_buf = menu_buf_init(total, max_len);
	if (g_screen.ws_row - g_rline.str_num >= g_menu_buf.buf_lines)
	{
		while (++i < g_menu_buf.word_nb)
			if (menu[i] && menu[i][0])
				buffer_col_print(menu[i], &g_menu_buf);
		position_cursor_after_menu_back(len_x, len_y, g_menu_buf.buf_lines, pos_back);
		g_rline.flag |= TAB;
		return (0);
	}
	if (ask_output(total, g_menu_buf.buf_lines, pos_back, len_x) == 1)
		return (1);
	while (++i < g_menu_buf.word_nb)
		if (menu[i] && menu[i][0])
			buffer_col_print(menu[i], &g_menu_buf);
	after_big_menu(pos_back, len_x, len_y);
	return (0);
}

int					print_menu_buf_after_insert(int pos_back)
{
	int				len_back;
	int				len_x_back;
	int				len_y_back;

	position_cursor_for_menu(g_rline.cmd_len);
	buffer_col_finish(&g_menu_buf);
	front_set_cursor_jmp(&len_back, &len_x_back, &len_y_back, 0);
	position_cursor_after_menu_back(len_x_back, len_y_back,
		g_menu_buf.buf_lines, pos_back);
	return (0);
}

/*
** After any key except of TAB is pushed, the menu under the line
** is cleared
*/

int					clean_menu(void)
{
	int				pos_back;
	int				len_back;
	int				len_x_back;
	int				len_y_back;

	pos_back = g_rline.pos;
	position_cursor_for_menu(g_rline.cmd_len);
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
		&g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_set_cursor_jmp(&len_back, &len_x_back, &len_y_back, 0);
	position_cursor("ch", 0, len_x_back);
	tputs(g_cap.up, 1, printc);
	move_cursor_from_old_position(pos_back, 'l');
	clean_menu_buf();
	return (0);
}

/*
** Cleaning the output buffer after we chose the option
** or do not chose anything
*/

int					clean_menu_buf(void)
{
	int				i;

	i = -1;
	while (++i < g_menu_buf.buf_lines)
		free(g_menu_buf.buffer[i]);
	free(g_menu_buf.buffer);
	g_menu_buf.buffer = NULL;
	return (0);
}
