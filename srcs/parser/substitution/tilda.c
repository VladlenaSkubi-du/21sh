#include "shell21.h"
#include "parser.h"

int		ft_find_tilda(t_ltree *sub, int flag) //убрать флаг везде где есть
{
	size_t	i;

	i = -1;
	while (++i < sub->l_tline.len)
	{
		if ((i == 0 && sub->l_tline.line[i] == TILDA) ||
			(i > 0 && sub->l_tline.line[i - 1] == SPACE &&
			sub->l_tline.line[i] == TILDA))
		{
			if (i + 1 == sub->l_tline.len || sub->l_tline.line[i + 1] == ENTER ||
				sub->l_tline.line[i + 1] == SPACE ||
				sub->l_cmd[i + 1] == '/')
				ft_get_home(sub, &i);
			else
				ft_getdir_by_name(sub, &i, flag);
		}
	}
	return (0);
}

/*
** It works when no symbol after '~' or it's '/'
*/

int 	ft_get_home(t_ltree *sub, size_t *i)
{
	char    *home;

	if ((home = get_env("HOME")) != NULL)
		insert_str_in_loc_strs(sub, &home, i, TEXT);
	else
		sub->l_tline.line[*i] = TEXT;
	return (0);
}

/*
** It works when after symbol '~' is some WORD 
** until '/' or ':' (only if flag == ASSIGN)
*/

int	ft_getdir_by_name(t_ltree *sub, size_t *i, int flag)
{
	size_t	j;
	char	*user;

	j = 1;
	while (sub->l_cmd[*i + j] != '/' && sub->l_tline.line[*i + j] != SPACE &&
		sub->l_cmd[*i + j] != '\n' && sub->l_cmd[*i + j] != '\0')
		j++;
	user = ft_strndup(&sub->l_cmd[*i + 1], j - 1);
	ft_find_dir_info(sub, user, i);
	free(user);
	return (0);
}

/*
** Function open file /etc/passwd and try to find user in it
*/

int		ft_find_dir_info(t_ltree *sub, char *user, size_t *i)
{
	int		fd;
	char	*line;
	char	**info;
	
	line = NULL;
	if ((fd = open("/etc/passwd", O_RDONLY)) != -1)
		while (ft_gnl(fd, &line) > 0)
		{
			info = ft_strsplit(line, ':');
			free(line);
			if (!ft_strcmp(info[0], user))
			{
				ft_reglue(i, ft_strlen(user), sub);
				line = ft_strdup(info[5]);
				insert_str_in_loc_strs(sub, &line, i, TEXT);
				ft_arrdel(info);
				break ;
			}
			ft_arrdel(info);
		}
	close (fd);
	return (0);
}
