#include "libft.h"

void		ft_lstadd_to_end(t_list **start, t_list *new)
{
	t_list	*tmp;

	tmp = *start;
	if (*start && new)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (*start == NULL)
		*start = new;
}
