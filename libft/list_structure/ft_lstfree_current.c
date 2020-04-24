/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:20:50 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/04/24 18:28:41 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstfree_current(t_list **head)
{
	t_list	*delete;
	t_list	*save_next;
	
	if ((*head)->next)
	{
		delete = *head;
		save_next = (*head)->next;
		*head = save_next;
		free(delete);
		delete = NULL;
	}
	else
	{
		free(*head);
		*head = NULL;
	}
	return (0);
}