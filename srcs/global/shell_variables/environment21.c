#include "shell21.h"

/*
** Environmental shell variables - are dinamic, exist within the session,
** the function save_environment_variables saves the parent process
** environ to 21sh @g_env.
**
** Can be changed by assignment (HOME=aaa)
** or export (export HOME=aaa)
** and a new line added by export-builtin (export FOO=bar)
*/

int					save_environment_variables(void)
{
	extern char		**environ;
	int				num;

	num = 0;
	g_env = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
	while (environ[num])
	{
		if (num == g_var_size)
		{
			g_env = ft_realloc_array(&g_env, g_var_size, g_var_size * 2);
			g_var_size *= 2;
		}
		g_env[num] = ft_strdup(environ[num]);
		num++;
	};
	return (0);
}

/*
** Shell readonly variables - always static, array @g_rdovar
**
** Can be only read by the user and corrected only within 21sh program
*/

int					save_readonly_variables(void)
{
	int				num;
	char			*tmp;

	num = 6;
	g_rdovar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	g_rdovar[0] = (char*)ft_xmalloc(sizeof(char) * MAX_EXIT_STATUS);
	g_rdovar[0] = ft_strcpy(g_rdovar[0], "?=0");
	g_rdovar[1] = ft_strdup("0=21sh");
	tmp = ft_itoa(getpid());
	g_rdovar[2] = ft_strjoin("$=", tmp);
	free(tmp);
	tmp = getcwd(NULL, MAXDIR);
	g_rdovar[3] = ft_strjoin("PWD=", tmp);
	g_rdovar[4] = ft_strjoin("OLDPWD=", tmp);
	g_rdovar[5] = ft_strjoin("21SH=", tmp);
	free(tmp);
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

	num = 3
	;
	g_shvar = (char**)ft_xmalloc((num + 1) * (sizeof(char*)));
	li = find_in_variables(g_env, &sy, "HOME=");
	tmp = (li < 0) ? define_history_file() :
		ft_strjoin(&g_env[li][sy], "/.42sh_history");
	g_shvar[0] = ft_strjoin("HISTFILE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTBUF);
	g_shvar[1] = ft_strjoin("HISTSIZE=", tmp);
	free(tmp);
	tmp = ft_itoa(MAX_HISTFILE);
	g_shvar[2] = ft_strjoin("HISTFILESIZE=", tmp);
	free(tmp);
	return (0);
}

/*
** Shell local variables - dinamic, exist within the session
** @g_lovar in 21sh
** 
** Can be added and changed by assignment (fuu=bar)
** And if already exists in @g_lovar and
** is used in export (export fuu=bbb),
** the variable starts to be visible in @g_env (by env command)
*/

int					save_local_variables(void)
{

	g_lovar = (char**)ft_xmalloc((g_var_size + 1) * (sizeof(char*)));
	return (0);
}

int                 exit_status_variable(int status)
{
    char            *num_status;
	int				len;
	char			*final;

    num_status = ft_itoa(status);
    ft_bzero(&g_rdovar[0][2], MAX_EXIT_STATUS - 2);
	if ((len = ft_strlen(num_status)) > MAX_EXIT_STATUS - 2)
	{
		final = ft_strjoin("?=", num_status);
		free(g_rdovar[0]);
		g_rdovar[0] = final;
	}
	else
		ft_strcpy(&g_rdovar[0][2], num_status);
    free(num_status);
    return (0);
}
