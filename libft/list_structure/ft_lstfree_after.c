/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:35:20 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:35:25 by sschmele         ###   ########.fr       */
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
