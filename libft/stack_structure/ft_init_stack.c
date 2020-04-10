/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:31:19 by sschmele          #+#    #+#             */
/*   Updated: 2020/04/07 14:54:02 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack				*ft_init_stack(void)
{
	t_stack			*stack;

	stack = ft_xmalloc(sizeof(t_stack));
	stack->data = 0;
	stack->next = NULL;
	return (stack);
}
