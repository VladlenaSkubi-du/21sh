#include "shell21.h"
#include "readline.h"

/*
** Comes to the function after pushing esc + d
** Cuts the part of the word from the cursor to the beginning
*/

int			esc_d(void)
{
	int				pos_old;
	char			*swap;
	int				len_swap;
	char			*save_yank;

	pos_old = g_rline.pos;
	if (word_right_proc())
		return (0);
	save_yank = (g_rline.pos == g_rline.cmd_len) ?
		ft_strdup(g_rline.cmd + pos_old) :
		ft_strndup(g_rline.cmd + pos_old, g_rline.pos - pos_old);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	g_rline.cmd_len = pos_old + len_swap;
	ft_strcpy(g_rline.cmd + pos_old, swap);
	ft_bzero(g_rline.cmd + pos_old + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	move_cursor_from_old_position(pos_old, 'l');
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

/*
** Comes to the function after pushing ctrl + w
** Cuts the part of the word from the cursor to the end
*/

int			make_ctrl_w(void)
{
	int				pos_old;
	char			*swap;
	int				len_swap;
	char			*save_yank;

	check_after_line();
	pos_old = g_rline.pos;
	if (word_left_proc())
		return (0);
	save_yank = (pos_old >= g_rline.cmd_len) ?
		ft_strdup(g_rline.cmd + g_rline.pos) :
		ft_strndup(g_rline.cmd + g_rline.pos, pos_old - g_rline.pos);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + pos_old;
	len_swap = ft_strlen(swap);
	g_rline.cmd_len = g_rline.pos + len_swap;
	ft_strcpy(g_rline.cmd + g_rline.pos, swap);
	ft_bzero(g_rline.cmd + g_rline.pos + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	front_set_cursor_jmp(&g_rline.pos,
		&g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

/*
** Comes to the function after pushing esc + r
** Cuts the whole cmd-line
*/

int			esc_r(void)
{
	char			*save_yank;

	check_after_line();
	save_yank = ft_strdup(g_rline.cmd);
	make_ctrl_p(0, save_yank);
	while (g_rline.pos)
		key_left_proc();
	tputs(g_cap.cd, 1, printc);
	ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	return (0);
}
