#include "shell21.h"
#include "readline.h"

/*
** After any key except of TAB is pushed, the menu under the line
** is cleared
*/

int		clean_after_line(void)
{
	int 			pos_back;
	int 			len_back;
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

int		position_cursor_after_line(int len)
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