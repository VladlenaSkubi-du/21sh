#include "shell21.h"
#include "parser.h"

int			prepare_and_exec(void)
{
	if (check_hard_errors() == OUT)
		return (0);
	return (0);
}

int			dollar_expansion(char **cmd_part)
{
	int		len;

	len = ft_strlen(*cmd_part);
	return (0);
}