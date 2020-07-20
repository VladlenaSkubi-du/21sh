
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
	front_write_one_char(c, color);
	if (flag == 'm')
	{
		if (c == '\n')
			return (front_insert_if_newline(&g_rline.pos_x, &g_rline.pos_y,
				&g_rline.str_num, &g_rline.flag));
		if (g_rline.pos_x == g_screen.ws_col - 1)
			return (front_insert_if_terminal(&g_rline.pos_x, &g_rline.pos_y,
				&g_rline.flag));
		return (front_insert_if_line(&g_rline.pos_x, &g_rline.str_num,
			&g_rline.flag));
	}
	if (flag == 'c')
		if (pos_x == g_screen.ws_col - 1)
			tputs(g_cap.sf, 1, printc);
	return (0);
}

/*
** When we enter a "\n", cursor pos, pos_x and pos_y changes
** immediately and the new line starts (we can increase by 1
** the str_num)
** If "\n" is inserted in the beginning of the line (pos_x == 0)
** a "\n" should become the only symbol in the line
*/

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

/*
** When we input a char to the last column in the terminal -
** the cursor changes its pos_x and pos_y position but in fact
** the position and the number of lines is not changing
*/

int					front_insert_if_terminal(int *pos_x,
						int *pos_y, int *flag)
{
	tputs(g_cap.sf, 1, printc);
	*pos_x = 0;
	(*pos_y)++;
	*flag |= NEW_LINE_TE;
	return (0);
}

/*
** If the terminal is the same width as the prompt len -
** the line will start form pos_x position - that is why there
** is a PROMPTLEN_ZERO flag for the first insertion
*/

int					front_insert_if_line(int *pos_x,
						int *str_num, int *flag)
{
	if (*pos_x == 0 && !(*flag & NEW_LINE_SY))
		(*str_num)++;
	else if (*pos_x == 0 && (*flag & NEW_LINE_SY))
		*flag &= ~(NEW_LINE_SY);
	if (*flag & PROMPTLEN_ZERO)
		*flag &= ~(PROMPTLEN_ZERO);
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
