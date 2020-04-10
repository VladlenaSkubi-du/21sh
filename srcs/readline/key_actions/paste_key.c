#include "shell21.h"
#include "readline.h"

/*
** Comes to the function after pushing ctrl + p
** Exists within the session - the buffer to paste
*/

int			make_ctrl_p(int mode, char *yank)
{
	static char		*yank_str;

	check_menu();
	if (mode == 0)
	{
		(yank_str) ? free(yank_str) : 0;
		if (yank)
			yank_str = yank;
		else
			yank_str = NULL;
	}
	else if (mode == 1)
	{
		if (yank_str == NULL)
			return (incorrect_sequence());
		paste_insert(yank_str);
	}
	else if (mode == 2)
		(yank_str) ? free(yank_str) : 0;
	return (0);
}

int			paste_insert(char *yank_str)
{
	char			*save;
	int				i;

	if (g_rline.pos < g_rline.cmd_len && g_rline.cmd[g_rline.pos])
	{
		save = ft_strdup(g_rline.cmd + g_rline.pos);
		ft_bzero(g_rline.cmd + g_rline.pos, g_rline.cmd_buff_len - g_rline.pos);
	}
	else
		save = NULL;
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	i = -1;
	while (yank_str[++i])
		char_add(yank_str[i], NULL);
	if (save)
		ft_strcpy(g_rline.cmd + g_rline.pos, save);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	free(save);
	return (0);
}
