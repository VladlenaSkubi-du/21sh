/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:34:19 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:37:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static char		*ft_find_token_sep_one(char *str)
{
	if (ft_strlen(str) > 0)
	{
		if (!ft_strncmp(str, ";", 1))
			return (ft_strndup(";", 1));
		if (!ft_strncmp(str, "&", 1))
			return (ft_strndup("&", 1));
		if (!ft_strncmp(str, ";", 1))
			return (ft_strndup(";", 1));
		if (!ft_strncmp(str, "|", 1))
			return (ft_strndup("|", 1));
		if (!ft_strncmp(str, "(", 1))
			return (ft_strndup("(", 1));
		if (!ft_strncmp(str, ")", 1))
			return (ft_strndup(")", 1));
		if (!ft_strncmp(str, ">", 1))
			return (ft_strndup(">", 1));
		if (!ft_strncmp(str, "<", 1))
			return (ft_strndup("<", 1));
	}
	return (NULL);
}

char			*ft_find_token_sep(char *str)
{
	if (ft_strlen(str) > 1)
	{
		if (!ft_strncmp(str, "&&", 2))
			return (ft_strndup("&&", 2));
		else if (!ft_strncmp(str, "||", 2))
			return (ft_strndup("||", 2));
		else if (!ft_strncmp(str, ";;", 2))
			return (ft_strndup(";;", 2));
		else if (!ft_strncmp(str, "<<", 2))
			return (ft_strndup("<<", 2));
		else if (!ft_strncmp(str, ">>", 2))
			return (ft_strndup(">>", 2));
		else if (!ft_strncmp(str, "<&", 2))
			return (ft_strndup("<&", 2));
		else if (!ft_strncmp(str, ">&", 2))
			return (ft_strndup(">&", 2));
		else if (ft_strlen(str) > 2)
			if (!ft_strncmp(str, "<<-", 3))
				return (ft_strndup("<<-", 3));
	}
	return (ft_find_token_sep_one(str));
}
