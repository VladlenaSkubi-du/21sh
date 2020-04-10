/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:26:27 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/12 13:55:38 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = f(lst);
	first = new;
	lst = lst->next;
	while (lst)
	{
		new->next = f(lst);
		if (!(new->next = f(lst)))
		{
			free(new->content);
			free(new->next);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
