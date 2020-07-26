/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:57:11 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 17:32:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <builtin.h>

int		setenv_error(char **tmp, int i)
{
	char *error;

	error = ft_strjoin("setenv: ", *tmp);
	error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
	free(error);
	g_envi[i][0] |= ENV_VIS;
	free(*tmp);
	return (0);
}
