/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:49:56 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/04/17 21:51:20 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstfree(t_list **head)
{
	t_list		*runner;

	runner = *head;
	while (runner)
	{
		free(runner->content);
		runner->content = NULL;
		runner = runner->next;
	}
	*head = NULL;
}