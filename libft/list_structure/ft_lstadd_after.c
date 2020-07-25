/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:33:42 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:33:47 by sschmele         ###   ########.fr       */
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
