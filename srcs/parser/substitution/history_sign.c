#include "shell21.h"
#include "parser.h"

int				ft_find_history(t_ltree *sub)
{
	size_t	i;

	i = -1;
	while (++i < sub->l_tline.len)
	{
		// if (sub->l_tline.line[i] == EXMARK)
		// {
		// 	if (g_hist.len > 0)
		// 		delete_last_history_element();
		// 	if (g_hist.len < 1 || g_hist.last < 0)
		// 	{
		// 		error_handler(VARIABLE_ERROR | (ERR_EXSIGN << 9), "!"); //заменить, когда пойму, откуда отсчет
		// 		return (HIST_ERROR); //заменить, когда пойму, как делать ошибку
		// 	}
		// 	if (!sub->l_tline.line[i + 1])
		// 		return (0);
		// 	// else if (sub->l_tline.line[i + 1] == EXMARK)
		// 	// 	insert_last_cmd(i);
		// 	// else if (sub->l_tline.line[i + 1] == WORD_P)
		// 	// 	insert_cmd_found(i);
		// }
	}
	return (0);
}