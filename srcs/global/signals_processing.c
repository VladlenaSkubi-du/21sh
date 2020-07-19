#include "shell21.h"
#include "readline.h"

int					signals_reroute(int from)
{
	if (from == 1)
	{
		signal(SIGINT, signal_ctrl_c_readline);
		signal(SIGWINCH, signal_screen_readline);
		signal(SIGCONT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (from == 2)
	{
		signal(SIGINT, signal_ctrl_c_parser);
		signal(SIGWINCH, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGCONT, SIG_IGN);
	}
	return (0);
}

void				signal_ctrl_c_readline(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_rline.flag & AFTER_LINE_HIST)
	{
		position_cursor("ch", 0, 0);
		tputs(g_cap.cd, 1, printc);
		g_rline.flag &= ~AFTER_LINE_HIST;
	}
	else
	{
		check_after_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_prompt.prompt_func = main_prompt;
	g_prompt.prompt_func();
	bzero_readline();
}

void				signal_screen_readline(int sig)
{
	int				i;

	if (sig != SIGWINCH)
		return ;
	check_after_line();
	position_cursor("ch", 0, 0);
	tputs(g_cap.cd, 1, printc);
	init_terminal_screen();
	g_rline.pos = 0;
	g_rline.pos_x = prompt_len();
	g_rline.pos_y = 0;
	g_rline.str_num = 1;
	g_prompt.prompt_func();
	i = -1;
	while (g_rline.cmd[++i])
	{
		g_rline.pos++;
		front_insert_one_char(g_rline.cmd[i],
			g_rline.pos_x, 'm', NULL);
	}
}

void				signal_ctrl_c_parser(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putendl_fd("\nstopped by signal SIGINT", STDOUT_FILENO);
}