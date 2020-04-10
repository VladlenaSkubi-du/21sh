
#include "shell21.h"
#include "parser.h"

/*
** Do we include pos_end? This should be discussed
*/

/*
** This function replaces any symbols which are considered to be spaces to
** actual spaces. Probably should be called before techline form.
*/

int		spaceizer(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str == '\t')
			*str = ' ';
		str++;
	}
	return (0);
}

char	**get_argv(char *exec_cmd)
{
	char	**ret;

	if (spaceizer(exec_cmd))
		return (0);
	ret = ft_strsplit(exec_cmd, ' ');
	return (ret);
}

/*
** This function returns positive integer, which is argc, or -1 in case of any
** illegal symbols discovered
*/

int		get_argc(size_t pos_start, size_t pos_end)
{
	size_t	iter;
	int		ret;

	iter = pos_start;
	ret = 0;
	while (iter < pos_end)
	{
		if (g_techline.line[iter] == 1)
			iter++;
		else if (!g_techline.line[iter])
		{
			ret++;
			while (!g_techline.line[iter])
				iter++;
		}
		else
			return (-1);
	}
	return (ret);
}

/*
** It is assumed, that we receive starting and ending position with only space
** specchars. By the way, we also have to process "raw" tabs (maybe as spaces --
** there is no difference). In "pos" structure there is also flag var, which sto
** res information about pipes, redirections, subshell, etc...
*/

int		exec_init(t_ltree *pos)
{
	// char	*exec_cmd;
	// char	**exec_av;
	// int		exec_ac;

	// exec_cmd = (char *)ft_xmalloc(pos->end - pos->start + 2);
	// ft_memcpy(exec_cmd, g_cmd + pos->start, pos->end - pos->start);
	// if ((exec_ac = get_argc(pos_start, pos_end)) == -1)
	// 	return (-1);
	// free(exec_cmd);
	// ft_lstclear(&pos->fd); // временно для проверки!!!
	return (exec_core(pos));
}
