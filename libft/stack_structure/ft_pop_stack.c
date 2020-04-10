/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:19:52 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 14:54:18 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_pop_stack(t_stack **head)
{
	int			res;
	t_stack		*tmp;

	tmp = *head;
	if ((*head)->next)
		*head = (*head)->next;
	else
		return (0);
	res = tmp->data;
	free(tmp);
	return (res);
}
