#include <shell21.h>
#include <builtin.h>

int		ft_to_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_error(path, 3);
		return (1);
	}
	return (0);
}

void		ft_change_pwd(char *path, char **env)
{
    int		i;
    int		j;
    int		k;
    
	i = find_in_variables(env, &j, "OLDPWD");
	free(g_rdovar[5]);
	free(g_rdovar[6]);
	k = find_in_variables(env, &j, "PWD");
	free(env[i]);
	env[i] = ft_strjoin("OLDPWD=", env[k] + j);
	free(env[k]);
	env[k] = ft_strjoin("PWD=", path);
	g_rdovar[5] = ft_strdup(env[k]);
	g_rdovar[6] = ft_strdup(env[i]);
}

int		ft_change_path(char *path, char **env, t_cd *flags)
{
    char	*name;

	if (ft_to_dir(path))
	{
		free(path);
		return (1);
	}
	if (flags->p)
		name = getcwd(NULL, 999);
	else
		name = path;
	ft_change_pwd(name, env);
	free(path);
	return (0);
}
