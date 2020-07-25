/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:36:28 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:36:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *subj, size_t len_subj,
				size_t len, size_t len_needed)
{
	void	*ptr;

	ptr = (void*)ft_xmalloc(len_needed);
	if (len_needed > len_subj)
	{
		ft_memcpy(ptr, subj, len);
		ft_bzero(ptr + len, len_needed - len);
	}
	else
		ft_memcpy(ptr, subj, len_needed);
	free(subj);
	return (ptr);
}
