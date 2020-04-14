#include "shell21.h"
#include "parser.h"

/*
** Function add commands whith args and fd to list
*/

int		ft_block_add_to_list(t_ltree *block, t_list **list)
{
	t_ltree	*final;

	final = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	while (ft_check_andor_pipes(block, final)) //pipes
	{
		if (final->flags & ERR_OUT)
		{
			ft_one_ltree_clear(final);
			ft_lst_ltree_clear(list);
			return (OUT);
		}
		block->start = final->end + 1;
		if (before_add(final, list) == OUT)
			return (OUT);		
		ft_add_list_to_end(list, ft_lstnew(final, sizeof(t_ltree)));
		ltree_init(final);
	}
	free(final);
	return (0);
}


/*
** Function start list commands
*/

int		ft_block_start(t_list **list)
{
	t_ltree	*sub;
	t_list	*start;

	start = *list;
	while (start)
	{
		sub = (t_ltree *)(start->content);
		if (before_exec(sub) == OUT)
			break ;
		if (!(sub->flags & ERR_IN))
			exec_init(sub);
		start = start->next;
	}
	ft_lst_ltree_clear(list);
	return (0);
}

/*
** Fucntion slice command string to blocks and send add it to start list
*/

int		ft_slice_fg(void)
{
	t_ltree		block;
	size_t		i;

	i = -1;
	ltree_init(&block);
	if (g_prompt.prompt_func != heredoc_prompt)
	{
		g_heredoc.list = NULL;
		g_start_list = NULL;
		while (++i <= g_techline.len)
		{
			if (g_techline.line[i] == SCOLON || g_cmd[i] == '\0') //конец блока только по этим символам
			{
				block.end = i;
				if (ft_block_add_to_list(&block, &g_start_list) == OUT)
					return (OUT);
			}
		}
	}
	return (ft_check_is_heredoc(0));
}
