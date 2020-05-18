#include <shell21.h>
#include <builtin.h>

int		ft_cd_env(char *path, char **env, t_cd *flags)
{
	char	*name;
	int	i;
	int	j;

	name = path ? ft_strdup("OLDPWD") : ft_strdup("HOME");
	i = find_in_variables(env, &j, name);
	if (path && i < 0)
	{
		free(name);
		return ((ft_error(NULL, 6)));
	}
	free(name);
	if (path)
		ft_putendl(env[i] + j);
	name = ft_strdup(env[i] + j);
	return ((ft_change_path(name, flags)));
}

int		ft_cd_pars(char *path, char **env, t_cd *flags)
{
	struct stat buff;

	if (ft_strcmp(path, "-") == 0 || !path)
		return ((ft_cd_env(path, env, flags)));
	//if (stat(path, &buff) < 0)
	//{
	//    if (ft_check_cdpath(ft_strjoin("/", path), env))
	//        return (ft_error(path, 4));
	//}
	if (stat(path, &buff) < 0)
		return (ft_error(path, 2));
	else if (!S_ISDIR(buff.st_mode))
		return (ft_error(path, 4));
	else
		return (ft_change_path(ft_new_path(path, env), flags));
	return (0);
}
