/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:49:37 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/25 15:54:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define TAIL ft_add_tail
#define GET ft_get_buf_line
#define C_SIZE			content_size
#define G_SIZE			4096

static void				ft_gnl_clean(t_fd_list **p)
{
	t_fd_list	*new;
	t_fd_list	*tmp;

	new = *p;
	while (new)
	{
		tmp = new->next;
		ft_lstclear(&(new->buf));
		free(new);
		new = tmp;
	}
}

static t_fd_list		*ft_fd_check(int fd, t_fd_list **p)
{
	t_fd_list	*new;

	if (fd < 0)
	{
		if (fd == GNL_CLEAN)
			ft_gnl_clean(p);
		return (NULL);
	}
	new = *p;
	while (new)
	{
		if (new->fd == fd)
			return (new);
		new = new->next;
	}
	if (!(new = (t_fd_list*)ft_memalloc(sizeof(t_fd_list))))
		return (NULL);
	new->fd = fd;
	new->next = *p;
	return (*p = new);
}

static	int				ft_add_tail(int fd, t_fd_list **fd_buf)
{
	t_list	*start;
	int		i;
	char	buf[G_SIZE];

	if (!(start = (t_list *)ft_memalloc(sizeof(t_list))))
		return (-1);
	ft_lstadd(&(*fd_buf)->buf, start);
	while ((start->content_size = read(fd, buf, G_SIZE)))
	{
		if (!(start->content = malloc(start->content_size)))
		{
			ft_lstclear(&start);
			return (-1);
		}
		(*fd_buf)->index += start->content_size;
		ft_memmove(start->content, buf, start->content_size);
		if (!(ft_memchr(start->content, 10, start->content_size)))
			return (((i = TAIL(fd, fd_buf)) == 1) ? 1 : i);
		else
			break ;
	}
	if ((i = start->C_SIZE) == 0)
		if (++((*fd_buf)->index))
			ft_memset((start->content = ft_memalloc(++start->C_SIZE)), '\n', 1);
	return ((i <= 0) ? i : 1);
}

static	int				ft_get_buf_line(char **line, t_fd_list **fd_buf)
{
	void	*p;
	t_list	*start;
	void	*buf;
	int		i;

	i = 0;
	start = (*fd_buf)->buf;
	if (!(buf = malloc((*fd_buf)->index)))
		return (-1);
	while (start)
	{
		i += start->content_size;
		ft_memmove(buf + (*fd_buf)->index - i, start->content, start->C_SIZE);
		start = start->next;
	}
	ft_memset((p = ft_memchr(buf, 10, (*fd_buf)->index)), 0, 1);
	*line = (*(char *)buf != '\0') ? ft_strdup((char *)buf) : NULL;
	ft_lstclear(&(*fd_buf)->buf);
	if (((*fd_buf)->index -= ((size_t)ft_strlen(*line) + 1)) > 0)
		(*fd_buf)->buf = ft_lstnew(p + 1, (*fd_buf)->index);
	else
		(*fd_buf)->buf = NULL;
	free(buf);
	return (1);
}

int						ft_gnl(const int fd, char **line)
{
	static t_fd_list	*fd_list;
	t_fd_list			*fd_buf;
	int					i;

	if (!(fd_buf = ft_fd_check(fd, &fd_list)) || read(fd, NULL, 0) ||
		line == NULL)
		return (-1);
	if (fd_buf->buf)
		if (ft_memchr(fd_buf->buf->content, 10, fd_buf->index))
			return (GET(line, &fd_buf));
	i = TAIL(fd, &fd_buf);
	if (i == 1)
		return (GET(line, &fd_buf));
	if (i == 0)
		fd_buf->end = 1;
	if (fd_buf->end == 1 && fd_buf->index == 1)
		return ((GET(line, &fd_buf) == 1) ? 0 : -1);
	if (fd_buf->end == 1 && fd_buf->index != 1)
	{
		ft_memset(fd_buf->buf->content, 10, 1);
		return (GET(line, &fd_buf));
	}
	return (-1);
}
