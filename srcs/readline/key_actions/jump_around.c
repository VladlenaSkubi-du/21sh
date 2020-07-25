#include "shell21.h"
#include "readline.h"

int			jump_up(void)
{
	int			pos_x_goal;

	if (g_rline.str_num < 2 || g_rline.pos_y == 0)
		return (incorrect_sequence());
	pos_x_goal = g_rline.pos_x;
	while (g_rline.pos_x != 0 && g_rline.pos)
		key_left_proc();
	if (g_rline.pos_x == 0)
	{
		key_left_proc();
		if (g_rline.pos_y == 0 && g_rline.pos_x >
			pos_x_goal + g_prompt.prompt_len)
		{
			while (g_rline.pos_x != pos_x_goal + g_prompt.prompt_len
				&& g_rline.pos)
				key_left_proc();
		}
		else if (g_rline.pos_y > 0 && g_rline.pos_x > pos_x_goal)
		{
			while (g_rline.pos_x != pos_x_goal && g_rline.pos)
				key_left_proc();
		}
	}
	return (0);
}

int			jump_down(void)
{
	int			pos_x_goal;
	int			flag;

	if (g_rline.str_num < 2 || g_rline.pos_y == g_rline.str_num - 1)
		return (incorrect_sequence());
	pos_x_goal = (g_rline.pos_y == 0) ? g_rline.pos_x - g_prompt.prompt_len :
		g_rline.pos_x;
	flag = (pos_x_goal == 0) ? 1 : 0;
	if (pos_x_goal == 0)
		key_right_proc();
	while (g_rline.pos_x != 0)
		key_right_proc();
	if (g_rline.pos_x == 0 && (pos_x_goal > 0 || flag == 1))
	{
		key_right_proc();
		if (flag == 1)
			return (key_left_proc());
		while (g_rline.pos_x < pos_x_goal && g_rline.pos_x != 0 &&
			g_rline.pos < g_rline.cmd_len)
			key_right_proc();
		(g_rline.pos_x == 0) ? key_left_proc() : 0;
	}
	return (0);
}

int			make_ctrl_a(void)
{
	int				pos_old;

	check_after_line();
	pos_old = 0;
	move_cursor_from_old_position(pos_old, 'l');
	return (0);
}

int			make_ctrl_e(void)
{
	int				pos_old;

	check_after_line();
	pos_old = g_rline.cmd_len - 1;
	move_cursor_from_old_position(pos_old, 'r');
	return (0);
}
