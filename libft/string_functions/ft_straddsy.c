/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddsy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:59:31 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:59:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_straddsy(char *dest, char sy)
{
	int		i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = sy;
	return (dest);
}
