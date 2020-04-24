/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:12:35 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/04/24 18:31:20 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstfree_after(t_list **current)
{
	t_list	*delete;
	t_list	*after;

	if (!(*current)->next)
		return (1);
	if ((*current) && (*current)->next)
	{
		delete = (*current)->next;
		after = (*current)->next->next;
		(*current)->next = after;
		free(delete);
		delete = NULL;
	}
	return (0);
}