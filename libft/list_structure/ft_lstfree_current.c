/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_current.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:34:46 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:34:55 by sschmele         ###   ########.fr       */
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
