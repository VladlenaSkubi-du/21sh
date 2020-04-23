/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:50:11 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/04/23 21:52:39 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_after(t_list **current, t_list *new)
{
	t_list	*after;

	if ((*current))
	{
		after = (*current)->next;
		(*current)->next = new;
		new->next = after;
	}
	else
		*current = new;
}