/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfsdf <sfsdf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:08:55 by sfsdf             #+#    #+#             */
/*   Updated: 2020/07/26 17:12:10 by sfsdf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <builtin.h>

void		ft_del_prev(char **arr, int i)
{
	while (i > 0)
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			free(arr[i]);
			arr[i] = ft_strdup(".");
			break ;
		}
		i--;
	}
}

void		ft_del_dots(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], "..") == 0)
			ft_del_prev(arr, i);
		i++;
	}
}

char		*ft_new_from_arr(char **arr)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_memalloc(1);
	ft_del_dots(arr);
	while (arr[i])
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			if (i > 1)
				tmp = ft_strrejoin(tmp, "/");
			tmp = ft_strrejoin(tmp, arr[i]);
		}
		i++;
	}
	return (tmp);
}

char		*ft_del_slesh(char *path)
{
	int		i;
	int		j;
	char	*res;
	char	tmp[MAXDIR];
	int		count;

	i = -1;
	count = 0;
	j = 0;
	while (path[++i])
	{
		if (path[i] == '/' && count > 0)
			continue ;
		else if (path[i] == '/')
			count++;
		else
			count = 0;
		tmp[j++] = path[i];
	}
	tmp[j] = '\0';
	return ((res = ft_strdup(tmp)));
}

char		*ft_new_path(char *path, char *src_path)
{
	char	*new_path;
	char	*tmp;
	char	**arr;

	if (path[0] == '/' && path[1])
		return (tmp = ft_del_slesh(path));
	else if (path[0] == '/')
		return (ft_strdup("/"));
	tmp = ft_join(path, src_path);
	arr = ft_strsplit(tmp, '/');
	free(arr[0]);
	arr[0] = ft_strdup("/");
	free(tmp);
	new_path = ft_new_from_arr(arr);
	ft_arrdel(arr);
	return (new_path);
}
