/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:34:27 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:07:29 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

static char	*get_path(void)
{
	char	*path;

	path = getcwd(NULL, MAXDIR);
	path = ft_strrejoin(path, "/");
	path = ft_strrejoin(path, "tmp_file");
	return (path);
}

int			ft_tmpfile(void)
{
	char	*path;
	char	*tmp;
	int		fd;
	int		time_out;

	path = get_path();
	time_out = 0;
	fd = -1;
	while (fd < 0)
	{
		time_out++;
		fd = open(path, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
		if (fd < 0 && time_out > 10)
			return (fd);
		else if (fd < 0)
		{
			tmp = ft_itoa(time_out);
			path = ft_strrejoin(path, tmp);
			free(tmp);
		}
	}
	unlink(path);
	free(path);
	return (fd);
}
