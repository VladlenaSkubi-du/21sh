#include "shell21.h"
#include "builtin.h"

#define BUILTINS_NUM	8

void				init_builtins(void)
{
	g_builtins = (char**)ft_xmalloc((BUILTINS_NUM + 1) * (sizeof(char*)));
	g_builtins[0] = ft_strdup("env");
	g_builtins[1] = ft_strdup("history");
	g_builtins[2] = ft_strdup("cd");
	g_builtins[3] = ft_strdup("exit");
	g_builtins[4] = ft_strdup("echo");
	g_builtins[5] = ft_strdup("unsetenv");
	g_builtins[6] = ft_strdup("setenv");
	g_builtins[7] = ft_strdup("pwd");
}

int					builtins_call_void(int call_num)
{
	int				(*builtins_func[BUILTINS_NUM])(void);

	builtins_func[0] = btin_env;
	builtins_func[1] = btin_history;
	return ((*builtins_func[call_num])());
}

int					builtins_call(int call_num, t_exec *exec)
{
	int				(*builtins_func[BUILTINS_NUM])(t_exec *exec);

	builtins_func[2] = btin_cd;
	builtins_func[3] = btin_exit;
	builtins_func[4] = btin_echo;
	builtins_func[5] = btin_unsetenv;
	builtins_func[6] = btin_setenv;
	builtins_func[7] = btin_pwd;
	return ((*builtins_func[call_num])(exec));
}

int					usage_btin(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": usage: ", STDOUT_FILENO);
	if (ft_strcmp(str, "setenv") == 0)
		ft_putendl_fd("setenv [name[=value] ...]",
			STDOUT_FILENO);
	else if (ft_strcmp(str, "cd") == 0)
		ft_putendl_fd("cd [-L|-P] [dir]", STDOUT_FILENO);
	else if (ft_strcmp(str, "echo") == 0)
		ft_putendl_fd("echo [-neE] [arg ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_putendl_fd("pwd [-LP]", STDOUT_FILENO);
	else if (ft_strcmp(str, "env") == 0)
		ft_putendl_fd("env [no_args]", STDOUT_FILENO);
	else if (ft_strcmp(str, "unsetenv") == 0)
		ft_putendl_fd("unsetenv [name ...]", STDOUT_FILENO);
	else if (ft_strcmp(str, "history") == 0)
		ft_putendl_fd("history [-c]", STDOUT_FILENO);
	else if (ft_strcmp(str, "exit") == 0)
		ft_putendl_fd("exit [numeric arg]", STDOUT_FILENO);
	return (0);
}

int					btin_return_exit_status(void)
{
	int             li;
	int             sy;

	li = find_in_variable(&sy, "?");
	return (ft_atoi(&g_envi[li][sy]));
}