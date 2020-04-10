#include "shell21.h"
#include "builtin.h"

#define BUILTINS_NUM	8

void				init_builtins(void)
{
	g_builtins = (char**)ft_xmalloc((BUILTINS_NUM + 1) * (sizeof(char*)));
	g_builtins[0] = ft_strdup("env");
	g_builtins[1] = ft_strdup("setenv");
	g_builtins[2] = ft_strdup("history");
	g_builtins[3] = ft_strdup("cd");
	g_builtins[4] = ft_strdup("exit");
	g_builtins[5] = ft_strdup("echo");
	g_builtins[6] = ft_strdup("unsetenv");
	g_builtins[7] = ft_strdup("pwd");
}

int					builtins_call_void(int call_num)
{
	int				(*builtins_func[BUILTINS_NUM])(void);

	builtins_func[0] = btin_env;
	builtins_func[1] = btin_set;
	builtins_func[2] = btin_history;
	return ((*builtins_func[call_num])());
}

int					builtins_call(int call_num, t_ltree *pos)
{
	int				(*builtins_func[BUILTINS_NUM])(t_ltree *pos);

	builtins_func[3] = btin_cd;
	builtins_func[4] = btin_exit;
	builtins_func[5] = btin_echo;
	builtins_func[6] = btin_unset;
	builtins_func[7] = btin_pwd;
	return ((*builtins_func[call_num])(pos));
}

t_btin_fc			*init_btin_fc(void)
{
	t_btin_fc		*fc;

	fc = (t_btin_fc*)ft_xmalloc(sizeof(t_btin_fc));
	fc->flag = 0;
	fc->editor = NULL;
    fc->first = 0;
	fc->last = 0;
	fc->s_comp = NULL;
	fc->s_cmd = NULL;
	return (fc);
}

int					btin_return_exit_status(void)
{
	int				li;
	int				sy;
	
	li = find_in_variables(g_rdovar, &sy, "?");
	return (ft_atoi(&g_rdovar[li][sy]));
}
