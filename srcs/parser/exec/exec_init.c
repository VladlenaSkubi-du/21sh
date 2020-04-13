
#include "shell21.h"
#include "parser.h"

/*
** It is assumed, that we receive starting and ending position with only space
** specchars. By the way, we also have to process "raw" tabs (maybe as spaces --
** there is no difference). In "pos" structure there is also flag var, which sto
** res information about pipes, redirections, subshell, etc...
*/

int		exec_init(t_ltree *pos)
{

	return (exec_core(pos));
}
