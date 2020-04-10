#include "shell21.h"
#include "readline.h"

int					bell_sound(void)
{
	write(STDOUT_FILENO, "\a", 1);
	return (1);
}

int					sescape_init(void)
{
	char			*seq_base[SESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[A";
	seq_base[2] = "[D";
	seq_base[3] = "[B";
	seq_base[4] = "r";
	return (sescape_check(seq_base));
}

int					sreadline_choice(char sy)
{
	if (sy == '\033')
		sescape_init();
	else if (ft_isprint(sy))
		schar_add(sy);
	else if (sy == 127 || sy == '\010')
		sbackspace_proc();
	else if (sy == '\002')
		sesc_left();
	else if (sy == '\006')
		sesc_right();
	else if (sy == '\001')
		make_sctrl_a();
	else if (sy == '\005')
		make_sctrl_e();
	else if (sy == '\013')
		make_sctrl_k();
	else if (sy == '\025')
		make_sctrl_u();
	return (0);
}

char				*readline_simple(void)
{
	char			c;

	while (read(STDIN_FILENO, &c, 1) && c != '\n')
	{
		if (ioctl(1, TIOCGWINSZ, &g_screen))
		{
			ft_putendl_fd("Can't get terminal dimensions", 2);
			return (NULL);
		}
		sreadline_choice(c);
	}
	reset_canonical_input();
	return (g_rline.cmd);
}
