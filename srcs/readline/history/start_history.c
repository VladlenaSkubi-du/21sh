#include "shell21.h"
#include "readline.h"

int				start_history(void)
{
	int			fd;
	int			sy;
	int			li;
	int			i;

	li = find_in_variables(g_shvar, &sy, "HISTSIZE");
	init_history_buffer(ft_atoi(&g_shvar[li][sy]) + 1);
	li = find_in_variables(g_shvar, &sy, "HISTFILE");
	fd = open(g_shvar[li] + sy, O_RDONLY);
	if (fd < 0)
		return (0);
	i = read_hist_from_file(fd);
	g_hist.last = i - 1;
	g_hist.counter = i;
	g_hist.start = i;
	g_hist.last_fc = (g_hist.last > 0) ? g_hist.last + 1 : 1;
	if (g_hist.len > MAX_HISTBUF)
		g_hist.hist = make_hist_buffer_smaller((MAX_HISTBUF > HISTORY_LIMIT) ?
		HISTORY_LIMIT : MAX_HISTBUF);
	if (g_hist.last_fc > HISTORY_LIMIT)
		g_hist.last_fc = HISTORY_LIMIT;
	close(fd);
	return (0);
}

/*
** The buffer size for history len is num + 1 for the current line
** to save and + 1 for the end of the array
*/

void			init_history_buffer(int size)
{
	g_hist.len = size;
	g_hist.hist = (char**)ft_xmalloc(sizeof(char*) * (g_hist.len + 1));
	g_hist.last = -1;
	g_hist.start = 0;
	g_hist.counter = 0;
	g_hist.last_fc = 0;
}

/*
** We find the directory we are in a try to find a history file. If we find -
** send it back to the start_history function and save everything from file to
** the buffer. If we can not open it - the buffer will start with the first
** command in the session
*/

char			*define_history_file(void) //TODO delete
{
	int			li;
	int			sy;

	li = find_in_variables(g_shvar, &sy, "21SH");
	return (ft_strjoin(&g_env[li][sy], "/.42sh_history"));
}

/*
** Numeration in the file starts with 1 but in the history buffer - from 0.
** We should make one line - the last in the buffer empty, because after
** the buffer is scrolled, a new cmd will lie there
** In the end of each command there is '\n' lying - if there was ctrl-d
** exit from readline when the prompt was not main-prompt - there is a EOF
** symbol in the line only
*/

int				add_to_history(char *cmd)
{
	int			flag;

	flag = 0;
	if (g_hist.last + 1 >= g_hist.len - 1 &&
		g_prompt.prompt_func == main_prompt && g_hist.len > 0)
		scroll_hist_buffer(1);
	if (g_prompt.prompt_func == main_prompt && g_hist.len > 0)
	{
		g_hist.last++;
		g_hist.hist[g_hist.last] = ft_strdup(cmd);
		g_hist.last_fc++;
		if (g_hist.last_fc > HISTORY_LIMIT)
			g_hist.last_fc = 1;
	}
	else if (g_prompt.prompt_func != main_prompt &&
		g_prompt.prompt_func != heredoc_prompt && g_hist.len > 0)
	{
		flag = (cmd[0] == EOF) ? EOF : 0;
		add_other_prompts_history(cmd, flag);
	}
	g_hist.counter = g_hist.last + 1;
	return (0);
}

int				add_other_prompts_history(char *cmd, int flag)
{
	int			len;

	if (g_hist.hist[g_hist.last][0] != 0 && flag == 0)
		g_hist.hist[g_hist.last] =
			ft_strrejoin(g_hist.hist[g_hist.last], cmd);
	g_pline = (t_cmd*)ft_xmalloc(sizeof(t_cmd));
	g_pline->cmd = ft_strdup(g_hist.hist[g_hist.last]);
	g_pline->cmd = (flag == EOF) ? ft_straddsy(g_pline->cmd, EOF) : g_pline->cmd;
	len = ft_strlen(g_pline->cmd);
	g_pline->tech = ft_make_techline(g_pline->cmd, len);
	g_pline->len_tech = len + 1;
	return (0);
}
