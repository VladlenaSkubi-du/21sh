#include "shell21.h"
#include "builtin.h"

int				btin_exit(t_exec *exec)
{
	int			status;
	int			i;
	char		*str;

	ft_putendl_fd("exit", STDOUT_FILENO);
	i = 0;
	if (exec->argc > 1)
	{
		while (exec->argv[1][i])
		{
			if (!(exec->argv[1][i] >= '0' && exec->argv[1][i] <= '9'))
			{
				str = ft_strjoin(exec->argv[0], ": ");
				str = ft_strrejoin(str, exec->argv[1]);
				error_handler(SYNTAX_ERROR | (ERR_NUMERIC << 9), str);
				free(str);
				break ;
			}
			i++;
		}
		status = ft_atoi(exec->argv[1]);
	}
	else
		status = 0;
	// ft_one_ltree_clear(pos); //почистить все листы
	fill_hist_in_file();
	clean_everything();
	exit(status);
}
