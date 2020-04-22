/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladlenaskubis <vladlenaskubis@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:49:56 by vladlenasku       #+#    #+#             */
/*   Updated: 2020/04/23 01:38:42 by vladlenasku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstfree(t_list **head)
{
	t_list		*runner;
	t_list		*tmp;

	runner = *head;
	while (runner)
	{
		tmp = runner;
		runner = runner->next;
		free(tmp->content);
		tmp->content = NULL;
	}
	*head = NULL;
}