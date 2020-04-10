#include "shell21.h"
#include "builtin.h"

int				btin_exit(t_ltree *pos)
{
	int			status;
	//TODO чистка парсер
	status = ft_atoi(pos->ar_v[1]);
	free(pos);
	ft_putendl_fd("exit", STDOUT_FILENO);
	fill_hist_in_file();
	clean_everything();
	//TODO функция, по типу atexit баша, с каким статусом завершилась программа
	exit(status);
}
