
#include "shell21.h"
#include "readline.h"

/*
** @flag = 'm' means main (main g_rline), @flag = 'c' means comment 
** When chars are inserted in the front part, position is changed
** by the terminal automatically - so I increase counters x and y
** after the changes are already done. @g_rline.pos is changed before
** the call of the function - can be also after, no influence
*/

int					front_insert_one_char(char c, int pos_x,
						char flag, char *color)
{
	if (flag == 'm')
	{
		if (c == '\n')
		{
			front_write_one_char(c, color);
			return (front_insert_if_newline(&g_rline.pos_x, &g_rline.pos_y,
				&g_rline.str_num, &g_rline.flag));
		}
		if (g_rline.pos_x == g_screen.ws_col - 1)
		{
			front_write_one_char(c, color);
			return (front_insert_if_terminal(&g_rline.pos_x, &g_rline.pos_y,
				&g_rline.flag));
		}
		front_write_one_char(c, color);
		return (front_insert_if_line(&g_rline.pos_x, &g_rline.str_num,
			&g_rline.flag));
	}
	if (flag == 'c')
	{
		front_write_one_char(c, color);
		if (pos_x == g_screen.ws_col - 1)
			tputs(g_cap.sf, 1, printc);
	}
	return (0);
}

int					front_insert_if_newline(int *pos_x, int *pos_y,
						int *str_num, int *flag)
{
	*pos_x = 0;
	(*pos_y)++;
	(*str_num)++;
	if (*flag & NEW_LINE_TE)
	{
		(*str_num)++;
		*flag &= ~(NEW_LINE_TE);
	}
	*flag |= NEW_LINE_SY;
	return (0);
}

int					front_insert_if_terminal(int *pos_x, int *pos_y, int *flag)
{
	tputs(g_cap.sf, 1, printc);
	*pos_x = 0;
	(*pos_y)++;
	*flag |= NEW_LINE_TE;
	return (0);
}

int					front_insert_if_line(int *pos_x, int *str_num, int *flag)
{
	if (*pos_x == 0 && !(*flag & NEW_LINE_SY))
		(*str_num)++;
	else if (*pos_x == 0 && (*flag & NEW_LINE_SY))
		*flag &= ~(NEW_LINE_SY);
	(*pos_x)++;
	return (0);
}

int					front_write_one_char(char c, char *color)
{
	if (color != NULL)
	{
		write(STDOUT_FILENO, color, ft_strlen(color));
		write(STDOUT_FILENO, &c, 1);
		write(STDOUT_FILENO, DEFAULT, ft_strlen(DEFAULT));
	}
	else
		write(STDOUT_FILENO, &c, 1);
	return (0);
}
