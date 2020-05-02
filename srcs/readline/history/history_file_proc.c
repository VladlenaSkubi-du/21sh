#include "shell21.h"
#include "readline.h"

int                 read_hist_from_file(int fd)
{
    int			    i;
    char		    *tmp;
    
    i = 0;
    tmp = NULL;
	while (ft_gnl(fd, &tmp) > 0)
	{
		if (i >= g_hist.len)
		{
			g_hist.hist = ft_realloc_array(&g_hist.hist,
				g_hist.len, g_hist.len + MAX_HISTBUF);
			g_hist.len += MAX_HISTBUF;
		}
		g_hist.hist[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	free(tmp);
    return (i);
}

/*
** We chechk one more time the HISTORY path - if user wants to change
** the default path for the file and the HISTORYSIZE variable
** If it is invalid, the default configurations won't change.
*/

int					fill_hist_in_file(void)
{
	int				li;
	int				sy;
	int				fd;
	char			*path;
	int				user_len;

	sy = 0;
	li = find_in_variables(g_shvar, &sy, "HISTFILE=");
	path = ft_strdup(g_shvar[li] + sy);
	li = find_in_variables(g_shvar, &sy, "HISTFILESIZE=");
	if (!ft_isdigit(g_shvar[li][sy]))
		user_len = MAX_HISTFILE;
	else
	{
		user_len = ft_atoi(g_shvar[li] + sy);
		if (user_len < 0 || user_len > HISTORY_LIMIT)
			user_len = MAX_HISTFILE;
	}
	fd = open_hist_file(user_len, path);
	free(path);
	if (fd < 0)
		return (0);
	insert_hist_in_file(fd, user_len);
	close(fd);
	return (0);
}

int					insert_hist_in_file(int fd, int user_len)
{
	int				i;
	int				tmp;

	if (user_len < g_hist.len)
		g_hist.hist = make_hist_buffer_smaller(user_len);
	i = 0;
	while (g_hist.hist[i] && i < g_hist.len)
	{
		tmp = ft_strlen(g_hist.hist[i]);
		if (tmp > 0 && g_hist.hist[i][tmp - 1] == '\n')
			tmp -= 1;
		write(fd, g_hist.hist[i], tmp);
		write(fd, "\n", 1);
		i++;
	}
	return (0);
}

int					open_hist_file(int user_len, char *path)
{
	int				fd;
	char			*default_path;

	default_path = define_history_file();
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT | O_SYNC,
		S_IRUSR | S_IWUSR);
	if (user_len == 0)
		g_hist.len = 0;
	if (ft_strcmp(path, default_path) != 0 && fd < 0)
		open_hist_file(user_len, default_path);
	free(default_path);
	return (fd);
}