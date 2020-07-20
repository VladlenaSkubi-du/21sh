#include "shell21.h"
#include "readline.h"

int					bell_sound(void)
{
	write(STDOUT_FILENO, "\a", 1);
	return (1);
}

int					sreadline_choice(char sy)
{
	if (sy == '\033')
		sescape_init();
	else if (ft_isprint(sy))
	{
		if (schar_add(sy) == OUT)
			return (OUT);
	}
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
	else if (sy == '\004')
		make_sexit();
	return (0);
}

int 				readline_simple(void)
{
	char			c;

	while (read(STDIN_FILENO, &c, 1) && c != '\n')
	{
		if (sreadline_choice(c) == OUT)
			break ;
	}
	ft_putendl_fd(0, STDOUT_FILENO);
	return (0);
}
