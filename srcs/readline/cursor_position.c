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
		return (g_prompt.prompt_len);
	while (nl_pos)
	{
		len++;
		if (g_rline.cmd[nl_pos] == '\n')
			break ;
		nl_pos--;
	}
	if (nl_pos > 0)
		len -= 1;
	else if (nl_pos == 0 && g_rline.cmd[nl_pos] != '\n')
		len += g_prompt.prompt_len + 1;
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
