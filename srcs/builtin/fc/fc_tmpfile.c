#include "shell21.h"
#include "parser.h"

static const char	g_letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

static int  ft_init_tmp(int *len, int *fd, int *buf, char *tmpl)
{
    *len = ft_strlen(tmpl);
	*fd = -1;
	*buf = 0;
	if (*len < 6 || ft_strcmp(&tmpl[*len - 6], "XXXXXX"))
		return (-1);
    return (0);
}

/*
** Generate a temporary file name based on TMPL.  TMPL must match the
** rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
** does not exist at the time of the call to mkstemp.  TMPL is
** overwritten with the result. Implementation of mkstemp by POSIX,
** but it removes tmp file after usage like tmpfile()
*/

/*
** use "tmp42sh_fc_XXXXXX" like 'tmpl'
*/

int			ft_tmpfile_fc(char *tmpl, char **tmp_nameto_vim)
{
	int		len;
	char	*tmp;
	char	*xxx;
	int		fd;
	int		buf;

	if (ft_init_tmp(&len, &fd, &buf, tmpl) == -1)
        return (-1);
	(tmp = ft_strdup(tmpl)) != NULL ? xxx = &tmp[len - 6] : 0;
	while (fd < 0) //make timeout
	{
		len = -1;
		fd = open("/dev/random", O_RDONLY);
		while (++len < 6)
		{
			read(fd, &buf, 1);
			xxx[len] = g_letters[(buf + 300) % 62];
		}
		close(fd);
		fd = open(tmp, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666); //to check CLOEXEC
	}
    *tmp_nameto_vim = tmp;
	return (fd);
}

/*
** For the edit mode invoking the editor: here we prepare the tmpfile
** for the editor to open
** FLAG_R or "-r" option changes the order of commands written
*/

int					btin_fc_write_to_tmpfile(t_btin_fc *fc_arg,
						int flags, int fd)
{
	int				tmp;

	if ((fc_arg->flag & ARG_FIRST) && !(fc_arg->flag & ARG_SECOND))
	{
		tmp = ft_strlen(g_hist.hist[fc_arg->first_buf]);
		if (tmp > 0 && g_hist.hist[fc_arg->first_buf][tmp - 1] == '\n')
			tmp -= 1;
		ft_putnendl_fd(g_hist.hist[fc_arg->first_buf], tmp, fd);
		return (0);
	}
	if (flags & FLAG_R)
	{
		if (fc_arg->first_buf > fc_arg->last_buf)
			btin_fc_execute_edit(fc_arg, fd, 'r');
		else
			btin_fc_execute_edit_reverse(fc_arg, fd, 'r');
	}
	else
	{
		if (fc_arg->first_buf > fc_arg->last_buf)
			btin_fc_execute_edit_reverse(fc_arg, fd, 'd');
		else
			btin_fc_execute_edit(fc_arg, fd, 'd');
	}
	return (0);
}

/*
** After tmpfile is closed by the editor, we read commands and
** start to launch them
** Saving global values is necessary because through launching
** without fork we change the values
*/

int					btin_fc_read_from_tmpfile(char *tmpfile)
{
	char			*cmd;
	int				fd;
	
	fd = open(tmpfile, O_RDONLY);
	if (fd < 0)
	{
		error_handler(TMPFILE, NULL);
		return (HIST_ERROR);
	}
	btin_fc_save_parser_globals(1);
	while (ft_gnl(fd, &cmd))
	{
		ft_putendl_fd(cmd, STDOUT_FILENO);
		parser(cmd);
	}
	btin_fc_save_parser_globals(0);
	close(fd);
	return (0);
}