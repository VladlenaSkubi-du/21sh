#include "shell21.h"
#include "readline.h"

int				printc(int c)
{
	return (write(1, &c, 1));
}

/*
** @g_cap.sf - code for scroll down one line in terminal
** @g_cap.le - code for left one column from the current cursor position
** @g_cap.nd - code for right one column from the current cursor position
** @g_cap.up - code for up one line from the current cursor position
** @g_cap.dow - code for down one line from the current cursor position
** @g_cap.cd - code for clearing everything from the current cursor position
** till the end of the terminal
** @g_cap.cr - code for jumping to the end of the current line
*/

int				init_termcap(void)
{
	char		*ptr;

	ptr = g_cap.sf;
	tgetstr("sf", &ptr);
	ptr = g_cap.le;
	tgetstr("le", &ptr);
	ptr = g_cap.nd;
	tgetstr("nd", &ptr);
	ptr = g_cap.up;
	tgetstr("up", &ptr);
	ptr = g_cap.dow;
	tgetstr("do", &ptr);
	ptr = g_cap.cd;
	tgetstr("cd", &ptr);
	ptr = g_cap.cr;
	tgetstr("cr", &ptr);
	return (0);
}

int				putcap(char *cap)
{
	char		buff[TERMCAP_SIZE];
	char		*ptr;

	ptr = buff;
	tputs(tgetstr(cap, &ptr), 1, printc);
	ptr = buff;
	ft_bzero(ptr, 20);
	return (0);
}

int				position_cursor(char *cap, int x, int y)
{
	char		buff[TERMCAP_SIZE];
	char		*ptr;

	ptr = buff;
	tputs(tgoto(tgetstr(cap, &ptr), x, y), 1, printc);
	ptr = buff;
	ft_bzero(ptr, 20);
	return (0);
}
