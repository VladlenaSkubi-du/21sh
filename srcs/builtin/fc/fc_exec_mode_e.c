#include "shell21.h"
#include "builtin.h"

/*
** For the edit mode execution, we create a tmpfile, write all the
** commands to it, execute the editor command + the file to be
** open and edited, than open the file and execute each command
** from there. After we delete the file (it is created in the
** project directory)
*/

int					btin_fc_execute_edition(t_btin_fc *fc_arg,
						int flags, char **envir)
{
	char			*tmpfile;
	int				fd;
	t_ltree			*sub;
	int				tmp;

	fd = ft_tmpfile_fc("tmp42sh_fc_XXXXXX", &tmpfile);
	if (fd < 0)
	{
		error_handler(TMPFILE, NULL);
		return (HIST_ERROR);
	}
	btin_fc_write_to_tmpfile(fc_arg, flags, fd);
	close(fd);
	sub = btin_fc_before_exec(fc_arg, envir, tmpfile);
	btin_fc_save_parser_globals(1);
	tmp = exec_init(sub);
	ft_arrdel(sub->ar_v);
	free(sub);
	btin_fc_save_parser_globals(0);
	if (tmp == 0)
		btin_fc_read_from_tmpfile(tmpfile);
	unlink(tmpfile);
	free(tmpfile);
	return ((tmp == 0) ? 0 : HIST_ERROR);
}

/*
** For the editor + tmpfile execution we need structure
** to be prepared
*/

t_ltree				*btin_fc_before_exec(t_btin_fc *fc_arg,
						char **envir, char *tmpfile)
{
	t_ltree			*sub;

	sub = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	ltree_init(sub);
	sub->envir = envir;
	sub->ar_v = (char**)ft_xmalloc(sizeof(char*) * (2 + 1));
	sub->ar_v[0] = ft_strdup(fc_arg->editor);
	sub->ar_v[1] = ft_strdup(tmpfile);
	sub->ar_c = 2;
	return (sub);
}

/*
** From the biggest to the least
** @flag can be 'd' = direct order, 'r' - reverse order
*/

int					btin_fc_execute_edit_reverse(t_btin_fc *fc_arg,
						int fd, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;
	
	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	while (value - i >= to && value - i >= 0)
	{
		tmp = ft_strlen(g_hist.hist[value - i]);
		if (tmp > 0 && g_hist.hist[value - i][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnendl_fd(g_hist.hist[value - i], tmp, fd);
		i++;
	}
	return (0);
}

/*
** From the least to the biggest
** @flag can be 'd' = direct order, 'r' - reverse order
*/

int					btin_fc_execute_edit(t_btin_fc *fc_arg,
						int fd, int flag)
{
	int				i;
	int				tmp;
	int				value;
	int				to;

	i = 0;
	value = (flag == 'd') ? fc_arg->first_buf : fc_arg->last_buf;
	to = (flag == 'd') ? fc_arg->last_buf : fc_arg->first_buf;
	while (value + i <= to && value + i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[value + i]);
		if (tmp > 0 && g_hist.hist[value + i][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnendl_fd(g_hist.hist[value + i], tmp, fd);			
		i++;
	}
	return (0);
}