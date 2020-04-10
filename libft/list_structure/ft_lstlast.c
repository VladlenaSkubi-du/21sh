/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@sdudent.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:09:42 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/01 14:53:10 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list **begin_list)
{
	t_list	*tmp;

	tmp = *begin_list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
