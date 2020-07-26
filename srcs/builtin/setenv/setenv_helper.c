/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:57:11 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 16:57:21 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <builtin21.h>

int		export_error(char **tmp, int i)
{
	char *error;

	error = ft_strjoin("export: ", *tmp);
	error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
	free(error);
	g_envi[i][0] |= ENV_VIS;
	free(*tmp);
	return (0);
}
