#include "shell21.h"

/*
** Environmental shell variables - are dinamic, exist within the session,
** the function save_environment_variables saves the parent process
** environ to 21sh @g_env.
*/

int					save_environment_variables(void)
{
	extern char		**environ;
	int				num;
	int				size;

	num = 0;
	size = ENV_BUFFER;
	g_env = (char**)ft_xmalloc((size + 1) * (sizeof(char*)));
	while (environ[num])
	{
		if (num == size)
		{
			g_env = ft_realloc_array(&g_env, size, size * 2);
			size *= 2;
		}
		g_env[num] = ft_strdup(environ[num]);
		num++;
	}
	save_env_size(size, 0);
	return (0);
}

/*
** Shell working variables - always static, array @g_shvar
**
** Can be changed by assignment (HISTFILE=5), can NOT be added
** If there is an export variable (export HISTFILE=5)
** the variable starts to be visible in @g_env (by env command)
*/

int					save_shell_variables(void)
{
	int				num;
	char			*tmp;
	int				li;
	int				sy;

	num = 10;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_shvar[0] = (char*)ft_xmalloc(sizeof(char) * MAX_EXIT_STATUS);
	g_shvar[0] = ft_strcpy(g_shvar[0], "?=0");
	g_shvar[1] = ft_strdup("0=21sh");
	tmp = ft_itoa(getpid());
	g_shvar[2] = ft_strjoin("$=", tmp);
	free(tmp);
	tmp = getcwd(NULL, MAXDIR);
	g_shvar[3] = ft_strjoin("PWD=", tmp);
	g_shvar[4] = ft_strjoin("OLDPWD=", tmp);
	g_shvar[5] = ft_strjoin("21SH=", tmp);
	free(tmp);
	li = find_in_variables(g_env, &sy, "HOME");
	tmp = (li < 0) ? define_history_file() :
		ft_strjoin(&g_env[li][sy], "/.42sh_history");
	g_shvar[6] = ft_strjoin("HISTFILE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTBUF);
	g_shvar[7] = ft_strjoin("HISTSIZE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTFILE);
	g_shvar[8] = ft_strjoin("HISTFILESIZE=", tmp);
	free(tmp);
	return (0);
}

int                 exit_status_variable(int status)
{
    char            *num_status;
	int				len;
	char			*final;

    num_status = ft_itoa(status);
    ft_bzero(&g_shvar[0][2], MAX_EXIT_STATUS - 2);
	if ((len = ft_strlen(num_status)) > MAX_EXIT_STATUS - 2)
	{
		final = ft_strjoin("?=", num_status);
		insert_assign_to_arrays(NULL, final, &g_shvar[0]);
	}
	else
		ft_strcpy(&g_shvar[0][2], num_status);
    free(num_status);
    return (0);
}

int					save_env_size(int size, int mode)
{
	static int		save_size;

	if (mode == 0)
		save_size = size;
	else
		return (save_size);
	return (0);
}