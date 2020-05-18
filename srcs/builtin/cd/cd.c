#include "shell21.h"
#include "builtin.h"

void	ft_change_curpath(char *path, t_cd *flags)
{
	free(flags->curpath);
	if (!path)
		flags->curpath = NULL;
	else
		flags->curpath = ft_strdup(path);
}

char	*ft_cut_name(char *name)
{
	char    *tmp;
	int		i;

	i = ft_strlen(name) - 1;
	// printf("name = %s\n", name);
	while (name[i] && name[i] != '/')
		i--;
	i++;
	tmp = ft_strdup(name + i);
	// printf("tmp = %s\n", tmp);
	return (tmp);
}

int		ft_error(char *name, int en)
{
    char	*tmp;
    char	*new_name;

	new_name = NULL;
	tmp = ft_strdup("cd: ");
	if (name) 
		tmp = ft_strrejoin(tmp, name);
	//ft_putstr_fd("cd", 2);
	if (en == 1)
		tmp = ft_strrejoin(tmp, ": string not in pwd");
	else if (en == 2)
		tmp = ft_strrejoin(tmp, ": no such file or directory");
	else if (en == 3)
		tmp = ft_strrejoin(tmp, ": permission denied");
	else if (en == 4)
		tmp = ft_strrejoin(tmp, ": not a directory");
	else if (en == 5)
		tmp = ft_strrejoin(tmp, "too many arguments");
	else if (en == 6)
		tmp = ft_strrejoin(tmp, "OLDPWD not set");
	error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
	free(tmp);
	free(new_name);
    return (1);
}

int         btin_cd(t_exec *exec)
{
	int     i;
	t_cd    *flags;

	flags = ft_xmalloc(sizeof(t_cd *));
	i = ft_cd_flags(exec->argv, flags);
	if (ft_valid_cd(exec->argv, i))
	{
		free(flags->curpath);
		free(flags);
		return (1);
	}
	if (ft_cd_pars(exec->argv[i], g_env, flags)) //можно убрать g_env в принципе
	{
		free(flags->curpath);
		free(flags);
		return (1);
	}
	free(flags->curpath);
	free(flags);
	return (0);
}
