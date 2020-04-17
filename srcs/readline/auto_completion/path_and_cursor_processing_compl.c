#include "shell21.h"
#include "readline.h"

/*
** For the 3rd pool of arguments - we go left untill we find
** the full path in which we read the entry
*/

char				*find_path_compl(char *compl, int tmp)
{
	char			*path;
	int				i;
	int				j;

	if (g_rline.pos < 1)
		return (NULL);
	if (compl && compl[0] && tmp != -1)
	{
		i = g_rline.pos - 1;
		while (i > 0 && (ft_isalnum(g_rline.cmd[i]) || g_rline.cmd[i] == '.' ||
				g_rline.cmd[i] == '/' || g_rline.cmd[i] == '_'))
			i--;
		j = g_rline.pos - 1;
		while (j > 0 && (ft_isalnum(g_rline.cmd[j])
			|| g_rline.cmd[j] == '.' || g_rline.cmd[i] == '_'))
		{
			if (g_rline.cmd[j] == '/')
				break ;
			j--;
		}
		path = ft_strndup(g_rline.cmd + i + 1, j - i);
	}
	else
		path = ft_strdup("./");
	return (path);
}

/*
** Sending the PATH value to be parsed for the tree
*/

char				*path_parse_compl(void)
{
	int				i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
			return (g_env[i] + 5);
		i++;
	}
	return (NULL);
}

/*
** Here we put cursor to the end of the line after ENTER is
** pushed
*/

int					position_cursor_for_menu(int len)
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