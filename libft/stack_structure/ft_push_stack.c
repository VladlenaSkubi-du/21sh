/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:32:02 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 14:54:25 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_push_stack(t_stack **head, int data)
{
	t_stack			*tmp;

	tmp = (t_stack*)ft_xmalloc(sizeof(t_stack));
	tmp->next = *head;
	tmp->data = data;
	*head = tmp;
	return (0);
}
