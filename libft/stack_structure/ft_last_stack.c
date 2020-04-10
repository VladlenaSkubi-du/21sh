/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:00:43 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 14:54:11 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_last_stack(t_stack **head)
{
	t_stack		*tmp;

	tmp = *head;
	while (tmp && tmp->next && tmp->next->next)
		tmp = tmp->next;
	return (tmp->data);
}
