#include "shell21.h"
#include "readline.h"

void	init_readline(void)
{
	if (ioctl(1, TIOCGWINSZ, &g_screen))
	{
		ft_putendl_fd("Can't get terminal dimensions", 2);
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	g_rline.prompt_len = prompt_len();
	g_rline.cmd = (char *)ft_xmalloc(CMD_SIZE + 1);
	g_rline.cmd_len = 0;
	g_rline.pos = 0;
	g_rline.pos_x = g_rline.prompt_len;
	if (g_rline.prompt_len >= g_screen.ws_col)
		g_rline.pos_x = g_rline.prompt_len % g_screen.ws_col;
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_rline.cmd_buff_len = CMD_SIZE + 1;
	g_rline.flag = 0;
}

int		start_readline21(int tmp)
{
	char		*final;

	if (tmp != 1)
		readline_simple();
	else
		readline();
	reset_canonical_input();
	check_menu();
	final = finalize_cmd(g_rline.cmd);
	clean_readline21();
	signals_reroute(2);
	parser(final);
	return (0);
}

char	*readline(void)
{
	char			temp;

	init_termcap();
	while (read(1, &temp, 1) > 0 && temp != '\n')
	{
		if (readline_choice(temp) == OUT)
			break ;
	}
	if (g_rline.cmd_len > 0)
	{
		check_menu();
		position_cursor_for_menu(g_rline.cmd_len);
		putcap("cd");
	}
	else
		ft_putendl_fd(0, STDOUT_FILENO);
	save_current_grline(2);
	return (g_rline.cmd);
}

int		readline_choice(char sy)
{
	if (ctrl_key(sy) == OUT)
		return (OUT);
	if (sy == '\033')
	{
		check_menu();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_menu();
		if (char_add(sy, NULL) == OUT)
			return (OUT);
	}
	return (0);
}

char	*finalize_cmd(char *cmd)
{
	char		*out;
	char		*tmp;

	tmp = ft_strtrim(cmd);
	if (ft_strlen(tmp) == 0)
	{
		out = ft_xmalloc(1);
		free(tmp);
		return (out);
	}
	if (g_rline.cmd_len == 0)
		out = ft_strdup(cmd);
	else
		out = ft_strjoin(cmd, "\n");
	free(tmp);
	return (out);
}
