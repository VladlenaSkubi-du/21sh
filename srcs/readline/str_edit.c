#include "shell21.h"
#include "readline.h"

/*
** Is the preparation of the g_rline.cmd (back) to insert
** a char if shift is < 0 to delete one char
*/

int					str_shift(char *str, int shift)
{
	char			*buff;

	buff = (char *)ft_xmalloc(ft_strlen(str) + 1);
	ft_strcpy(buff, str);
	ft_strcpy(str + shift, buff);
	free(buff);
	return (0);
}

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
		front_insert_one_char(g_rline.cmd[g_rline.pos], g_rline.pos_x, 'm', color);
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
** Is used only for comments in auto-completion and history block
** Therefore, front_insert_one_char receives 'c' flag where
** 'c' = comment
** All the comments will be colored
*/

int					front_insert_by_letters(char *str, int *pos_x) //либа, поменяй
{
	int				i;

	i = 0;
	while (str[i])
	{
		front_insert_one_char(str[i], *pos_x, 'c', BLUE);
		(*pos_x) = i;
		if (*pos_x == g_screen.ws_col - 1)
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

	if (g_rline.pos_x == 0 && g_rline.cmd[g_rline.pos != '\n'])
		g_rline.str_num = str_num_print - 1;
	else
		g_rline.str_num = str_num_print;
	while (g_rline.pos < g_rline.cmd_len)
	{
		front_insert_one_char(g_rline.cmd[g_rline.pos], g_rline.pos_x, 'm', NULL);
		g_rline.pos++;
	}
	front_set_cursor_jmp(&pos_back, &pos_x_back, &pos_y_back, 0);
	move_cursor_from_old_position(pos_back, 'l');
	return (0);
}