/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:50:53 by kfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 19:31:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "builtin.h"

int		btin_env(void)
{
	t_pathtree	*root;
	char		**list;
	int			i;
	int			len;

	root = NULL;
	list = NULL;
	len = 0;
	i = -1;
	while (g_envi[++i])
		if (g_envi[i][0] && (g_envi[i][0] & ENV_VIS))
			insert_to_path_tree(g_envi[i] + 1, &root, &len);
	list = form_result_array(&root, len, &i);
	free_path_tree(&root);
	i = -1;
	while (list[++i])
		ft_putendl_fd(list[i], STDOUT_FILENO);
	ft_arrdel(list);
	return (0);
}
