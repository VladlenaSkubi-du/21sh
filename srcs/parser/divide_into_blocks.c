#include "shell21.h"
#include "parser.h"

/*
** Function add commands whith args and fd to list
*/

int		ft_block_add_to_list(t_ltree *block, t_list **list)
{
	// t_ltree	*final;

	// final = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	// while (ft_check_andor_pipes(block, final))
	// {
	// 	if (final->flags & ERR_OUT)
	// 	{
	// 		ft_one_ltree_clear(final);
	// 		ft_lst_ltree_clear(list);
	// 		return (OUT);
	// 	}
	// 	block->start = final->end + 1;
	// 	if (before_add(final, list) == OUT)
	// 		return (OUT);
	// 	// if (ft_check_null(final, list) == OUT)
	// 	// 	return (OUT);		
	// 	ft_add_list_to_end(list, ft_lstnew(final, sizeof(t_ltree)));
	// 	ltree_init(final);
	// }
	// free(final);
	return (0);
}

/*
** Function forwards list commands until GR_START
*/

int		ft_block_foward(t_ltree **sub, t_list **start)
{
	while (*start)
	{
		if ((*start = (*start)->next))
			*sub = (t_ltree *)((*start)->content);
		else
			break ;
	}
	return (0);
}

/*
** Function start list commands
*/

int		ft_block_start(t_list **list)
{
	// t_ltree	*sub;
	// t_list	*start;
	// int		out_flag;

	// start = *list;
	// out_flag = 0;
	// while (start)
	// {
	// 	sub = (t_ltree *)(start->content);
	// 	if (before_exec(sub) == OUT)
	// 		break ;
	// 	if (!(sub->flags & ERR_IN))
	// 		out_flag = exec_init(sub);
	// 	start = start->next;
	// }
	// ft_lst_ltree_clear(list);
	return (0);
}

/*
** Fucntion slice command string to blocks and send add it to start list
*/
