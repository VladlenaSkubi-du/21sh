#include "shell21.h"

int					main(void)
{
	g_var_size = ENV_BUFFER;
	save_environment_variables();
	save_readonly_variables();
	save_shell_variables();
	save_local_variables(); //TODO remove local
	start_history();
	g_prompt.prompt_func = main_prompt;
	readline_start();
	return (0);
}

int					readline_start(void)
{
	char			*termtype;
	char			room_termtype[100];
	int				tmp;

	while (1)
	{
		init_readline();
		signals_reroute(1);
		check_terminal();
		g_prompt.prompt_func();
		termtype = getenv("TERM");
		termtype = (termtype == NULL) ? "xterm-256color" : termtype;
		tmp = tgetent(room_termtype, termtype);
		start_readline21(tmp);
		ft_bzero(room_termtype, 100);
	}
	return (0);
}

int					check_terminal(void)
{
	if (!isatty(STDIN_FILENO))
	{
		error_handler(TERMINAL_EXISTS, NULL);
		clean_readline21();
		clean_everything();
		exit(TERMINAL_EXISTS);
	}
	if (set_noncanonical_input() == -1)
	{
		error_handler(TERMINAL_TO_NON, NULL);
		clean_readline21();
		clean_everything();
		exit(TERMINAL_TO_NON);
	}
	return (0);
}

int					set_noncanonical_input(void)
{
	struct termios	tty;

	if (tcgetattr(STDIN_FILENO, &tty) < 0)
		return (-1);
	g_backup_tty = tty;
	tty.c_lflag &= ~(ICANON | ECHO);
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty) < 0)
		return (-1);
	if (tcgetattr(STDIN_FILENO, &tty) < 0 ||
		((tty.c_lflag & (ICANON | ECHO) ||
		tty.c_cc[VMIN] != 1 || tty.c_cc[VTIME] != 1)))
		reset_canonical_input();
	return (0);
}

int					reset_canonical_input(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_backup_tty) != 0)
	{
		error_handler(TERMINAL_TO_CAN, NULL);
		exit(TERMINAL_TO_CAN);
	}
	return (0);
}