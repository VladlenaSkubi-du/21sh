/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:59:06 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:59:08 by sschmele         ###   ########.fr       */
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
