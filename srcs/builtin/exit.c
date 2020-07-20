#include "shell21.h"
#include "builtin.h"

int				btin_exit(t_exec *exec)
{
	int			status;
	
	status = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (exec->argc > 1)
		status = btin_exit_arguments(exec->argv);
	else
		status = 0;
	fill_hist_in_file();
	clean_everything();
	exit(status);
}

int				btin_exit_arguments(char **ar_v)
{
	int			status;
	int			i;
	char		*str;

	status = 0;
	i = (ar_v[1][0] && ar_v[1][0] == '-') ? 0 : -1;
	while (ar_v[1][++i])
		if (!(ar_v[1][i] >= '0' && ar_v[1][i] <= '9'))
		{
			str = ft_strjoin(ar_v[0], ": ");
			str = ft_strrejoin(str, ar_v[1]);
			error_handler(SYNTAX_ERROR | (ERR_NUMERIC << 9), str);
			free(str);
			status = SYNTAX_ERROR;
			break ;
		}
	(status != SYNTAX_ERROR) ? status = ft_atoi(ar_v[1]) : 0;
	(status < 0) ? status &= 0xFF : 0;
	return (status);
}
