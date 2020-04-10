#include "shell21.h"
#include "readline.h"

/*
** When we move the cursor right, it can stay in the first
** column of the terminal and if the previous symbol in
** the g_rline.cmd (back) is '\n', we need to count
** its x-coordinate in the terminal line
** @nl_pos is the position of the symbol BEFORE the \n
** in g_rline.cmd. If \n is the first (zero) symbol in the
** g_rline.cmd, @nl_pos will be < 0, because the function
** calling count_x_position_new_line sends "g_rline.pos - 2" is
** "g_rline.pos - 1 == '\n", so we return the prompt_len
** understanding that \n is the first symbol in the line
**
** If nl_pos >= 0, we move right according to the position
** untill we meet another \n - then we just send the @len - 1
** meaning the number of symbols between \ns
** If we do not meet another \n, we will move right untill
** we come to the beginning of the line. If @len or in other
** words number of symbols between the beginning of g_rline.cmd
** and the \n is less than the terminal width, we return just
** @len + 1 (+ \n itself) and + prompt_len (because is @len is
** lower than he terminal width, we are on the first @g_rline.str_num)
** Otherwise, we return mod of @len and terminal width
*/

int					count_x_position_new_line(int nl_pos)
{
	int				len;
	
	len = 0;
	if (nl_pos < 0)
		return (g_rline.prompt_len);
	while (nl_pos)
	{
		len++;
		if (g_rline.cmd[nl_pos] == '\n')
			break ;
		nl_pos--;
	}
	if (nl_pos > 0)
		len -= 1;
	else
		len += g_rline.prompt_len + 1;
	if (len >= g_screen.ws_col)
		len = len % g_screen.ws_col;
	return (len);
}

/*
** @direction can be left = 'l' or right = 'r'
** This function is used if we changed the line by
** some cut-paste functions and need to return the
** cursor to the old position
*/

int					move_cursor_from_old_position(int pos_old,
						char direction)
{
	if (direction == 'l')
	{
		while (g_rline.pos != pos_old)
		{
			if (front_move_one_char_left(g_rline.pos_x))
				return (incorrect_sequence());
			g_rline.pos--;
		}
	}
	if (direction == 'r')
	{
		while (g_rline.pos != pos_old)
		{
			if (front_move_one_char_right(g_rline.pos_x))
				return (incorrect_sequence());
			g_rline.pos++;
		}
	}
	return (0);
}

/*
** @pos_x is absolute calculation of position you have NOW,
** because changes will be visible in global structure @g_rline
** g_rline.pos should be changed after the call of these functions
*/

int					front_move_one_char_right(int pos_x)
{
	if (pos_x > 0 && pos_x < g_screen.ws_col - 1 &&
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