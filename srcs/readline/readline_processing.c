#include "shell21.h"
#include "readline.h"

#define COLOR_NUM 6

/*
** Buffer for the inserted cmd-line is of CMD_SIZE in the
** beginning and grows by the usage of shell - it is freed
** only after the session is over
*/

void				init_readline(void)
{
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = 0;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}

void				bzero_readline(void)
{
	init_terminal_screen();
	if (g_rline.cmd && g_rline.cmd[0])
		ft_bzero(g_rline.cmd, g_rline.cmd_buff_len);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = prompt_len();
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	if (!(g_rline.flag & PROMPTLEN_ZERO))
		g_rline.flag = 0;
}

void				realloc_readline_cmd(void)
{
	g_rline.cmd = (char *)ft_realloc(g_rline.cmd,
		g_rline.cmd_len, g_rline.cmd_buff_len,
		g_rline.cmd_buff_len + CMD_SIZE);
	g_rline.cmd_buff_len += CMD_SIZE;
}

int					init_terminal_screen(void)
{
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		error_handler(TERMINAL_EXISTS, NULL);
		free(g_rline.cmd);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	if (g_screen.ws_col == 0)
		g_screen.ws_col = DEFAULT_SCREEN_SIZE;
	return (0);
}

char				*colors_process(int sequence_num)
{
	char			*seq_action[COLOR_NUM];

	seq_action[0] = RED;
	seq_action[1] = ORANGE;
	seq_action[2] = YELLOW;
	seq_action[3] = GREEN;
	seq_action[4] = BLUE;
	seq_action[5] = PURPLE;
	return (seq_action[sequence_num]);
}
