/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:50:53 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 16:50:56 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin.h"

int		btin_env(void)
{
	t_path	*root;
	char	**list;
	int		i;
	size_t	len;

	root = NULL;
	list = NULL;
	len = 0;
	i = -1;
	while (g_envi[++i])
		if (g_envi[i][0] && (g_envi[i][0] & SET_VIS))
			insert_in_bintree(g_envi[i] + 1, &root, &len);
	list = ft_add_block(&root, len, &i);
	ft_path_free(&root);
	i = -1;
	while (list[++i])
	   	ft_putendl_fd(list[i], STDOUT_FILENO);
	ft_arrdel(list);
	return (0);
}
