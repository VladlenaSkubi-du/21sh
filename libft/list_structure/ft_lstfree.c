/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:35:07 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:35:11 by sschmele         ###   ########.fr       */
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
