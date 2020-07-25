#include "shell21.h"
#include "readline.h"

int		start_readline21(int tmp)
{
	char		*final;

	bzero_readline();
	(tmp != 1) ? readline_simple() : readline();
	reset_canonical_input();
	signals_reroute(2);
	final = finalize_cmd(g_rline.cmd);
	free(g_hist.hist[g_hist.last + 1]);
	parser(final);
	return (0);
}

int		readline(void)
{
	char			temp;

	init_termcap();
	while (read(STDIN_FILENO, &temp, 1) > 0 && temp != '\n')
	{
		if (readline_choice(temp) == OUT)
			break ;
	}
	if (g_rline.cmd_len > 0)
	{
		check_after_line();
		position_cursor_after_line(g_rline.cmd_len);
		putcap("cd");
	}
	else
		ft_putendl_fd(0, STDOUT_FILENO);
	clean_termcap();
	return (0);
}

int		readline_choice(char sy)
{
	if (ctrl_key(sy) == OUT)
		return (OUT);
	if (sy == '\033')
	{
		check_after_line();
		escape_init();
	}
	else if (ft_isprint(sy))
	{
		check_after_line();
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
	else
		out = ft_strjoin(cmd, "\n");
	free(tmp);
	return (out);
}

/*
** After any key except of TAB is pushed, the menu under
** the line is cleared
** The same happends with the comments under the line
*/

int		check_after_line(void)
{
	if (g_rline.flag & TAB)
	{
		clean_after_line();
		g_rline.flag &= ~TAB;
		clear_completion(0);
	}
	else if ((g_rline.flag & AFTER_LINE) ||
			(g_rline.flag & AFTER_LINE_HIST))
	{
		clean_after_line();
		g_rline.flag &= ~AFTER_LINE;
		g_rline.flag &= ~AFTER_LINE_HIST;
	}
	return (0);
}
