#include "shell21.h"
#include "builtin.h"

int		ft_check_cdpath(char *path, char **env)  ///ПЕРЕПИСАТЬ, удалить env и в коде env->g_env
{
	int	i;
	int	j;
	char	**cdpath;
	char	*tmp;

	if ((i = find_in_variables(env, &j, "CDPATH")) == -1) //исправить на g_env
		return (1);
	cdpath = ft_strsplit(env[i] + j, ';');
	i = 0;
	while (cdpath[i])
	{
		if ((chdir(tmp = ft_strjoin(cdpath[i], path))) != -1)
			break ;
		free(tmp);
		i++;
	}
	if (tmp)
		free(tmp);
	ft_strdel(&path);
	if (cdpath[i])
	{
		ft_arrdel(cdpath);
		return (0);
	}
	ft_arrdel(cdpath);
	return (1);
}

int		ft_check_cd_args(char **argv, int i)
{
	if (argv[i] && argv[i + 1])
	{
		ft_error(NULL, 5);
		return (1);
	}
	return (0);
}

int		ft_valid_cd(char **argv, int i)
{
	if (ft_check_cd_args(argv, i))
		return (1);
	return (0);
}
