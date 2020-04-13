#include "shell21.h"
#include "parser.h"

/*
** Func to find another subblocks
*/

t_ltree		*ft_find_logic(t_ltree *block, t_ltree *final)
{
	size_t		i;

	i = block->start;
	final->flags = block->flags;
	final->start = block->start;
	while (i <= block->end)
	{
		if (ft_find_pipe(block, final, &i))
			return (final);
		i++;
	}
	return (NULL);
}

t_ltree		*ft_find_pipe(t_ltree *block, t_ltree *final, size_t *i)
{
	if (g_techline.line[*i] == PIPE && g_techline.line[*i + 1] != PIPE)
	{
		//final->start = block->start;
		final->end = *i;
		(block->flags & PIPED_OUT) && (block->flags |= PIPED_IN);
		(block->flags & PIPED_IN) && (final->flags |= PIPED_IN);
		final->flags |= PIPED_OUT;
		block->flags |= PIPED_OUT;
		return (final);
	}
	if (*i == block->end)
	{
		//final->start = block->start;
		final->end = *i;
		if (block->flags & PIPED_OUT)
		{
			final->flags &= ~PIPED_OUT;
			block->flags &= ~PIPED_OUT;
			final->flags |= PIPED_IN;
			block->flags &= ~PIPED_IN;
		}
		return (final);
	}
	return (NULL);
}

t_ltree		*ft_check_andor_pipes(t_ltree *block, t_ltree *final)
{
	size_t	i;

	if (!ft_find_logic(block, final))
		return (NULL);
	if (final->flags & PIPED_IN)
	{
		i = final->start - 1;
		while (++i < block->end)
			if (ft_correct_after_andor_pipe(&i))
				break ;
		erroring_andor_pipe(final, &i, block->end);
	}
	return (final);			
}

/*
** Function clear list of t_ltree type. It uses ft_one_ltree_clear
*/

void	ft_lst_ltree_clear(t_list **begin_list)
{
	t_list 	*tmp;
	t_ltree	*buf;

	if (!(begin_list) || !(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		if ((*begin_list)->content)
		{
			buf = (t_ltree *)(*begin_list)->content;
			ft_one_ltree_clear(buf);
		}
		free((*begin_list));
		*begin_list = tmp;
	}
	*begin_list = NULL;
}

int		ft_correct_after_andor_pipe(size_t *i)
{
	if (g_techline.line[*i] == WORD_P ||
		g_techline.line[*i] == PIPE ||
		g_techline.line[*i] == AND ||
		g_techline.line[*i] == BSLASH ||
		g_techline.line[*i] == DQUOTE ||
		g_techline.line[*i] == SQUOTE ||
		g_techline.line[*i] == OPAREN ||
		g_techline.line[*i] == CPAREN ||
		g_techline.line[*i] == OBRACE ||
		g_techline.line[*i] == CBRACE ||
		g_techline.line[*i] == OBRACKET ||
		g_techline.line[*i] == CBRACKET ||
		g_techline.line[*i] == DOLLAR ||
		g_techline.line[*i] == TILDA ||
		g_techline.line[*i] == AST ||
		g_techline.line[*i] == EQUAL ||
		g_techline.line[*i] == COMENT ||
		g_techline.line[*i] == TEXT)
		return (1);
	return (0);
}
