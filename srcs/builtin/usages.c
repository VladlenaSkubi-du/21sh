#include "shell21.h"
#include "builtin.h"

int				usage_btin(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": usage: ", STDOUT_FILENO);
	if (ft_strcmp(str, "fc") == 0)  
		usage_btin_fc();
	return (0);
}

int				usage_btin_fc(void)
{
	ft_putstr_fd("fc [-e editor] [-nlr] [first] [last]", STDOUT_FILENO);
	ft_putendl_fd(" or fc -s [pat=rep] [cmd]", STDOUT_FILENO);
	return (0);
}
