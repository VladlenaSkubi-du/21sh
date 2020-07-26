/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:43:29 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:43:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

int				find_fdbefore_redir(t_cmd **ptr_lcmd,
					t_fd *fd_inout, int *i)
{
	int			j;

	if (*i == 0)
		return (0);
	j = (*i) - 1;
	while (j >= 0 &&
			(*ptr_lcmd)->tech[j] == WORD_P &&
			ft_isdigit((*ptr_lcmd)->cmd[j]))
		j--;
	if (j >= 0 && !((*ptr_lcmd)->tech[j] == SPACE ||
			(*ptr_lcmd)->tech[j] == WORD_P))
	{
		fd_inout->flag |= REDIR_SOFT;
		return (OUT);
	}
	if ((*i) - 1 != j)
	{
		j++;
		fd_inout->fd_old = ft_atoi(&(*ptr_lcmd)->cmd[j]);
		delete_or_insert_to_pline(ptr_lcmd, *i, j - (*i));
		*i -= (*i) - j;
	}
	return (0);
}

/*
** Here we check if there are only spaces till the end of line or
** the end of line itself - that will be the redirection error
** If we do not come into the second cycle, it means that there is
** not a word but some syntax sign after the space - that is also
** the redirection error
*/

int				find_fdafter_redir(t_cmd **ptr_lcmd,
					t_fd *fd_inout, int *i)
{
	int			j;
	int			start;

	j = *i;
	while (j < (*ptr_lcmd)->len_tech && (*ptr_lcmd)->tech[j] == SPACE)
		j++;
	if (j == (*ptr_lcmd)->len_tech - 1)
	{
		fd_inout->flag |= REDIR_HARD;
		return (OUT);
	}
	start = j;
	while (j < (*ptr_lcmd)->len_tech && ((*ptr_lcmd)->tech[j] == WORD_P ||
			(*ptr_lcmd)->tech[j] == TEXT))
		j++;
	if (start - j == 0)
	{
		fd_inout->flag |= REDIR_HARD;
		return (OUT);
	}
	fd_inout->file = ft_strndup((*ptr_lcmd)->cmd + start, j - start);
	delete_or_insert_to_pline(ptr_lcmd, j, start - j);
	return (0);
}

int				activate_redir_error(t_pblks **current_cont, t_fd fd_inout)
{
	if (fd_inout.flag & REDIR_SOFT)
		(*current_cont)->err |= REDIR_SOFT;
	else
	{
		(*current_cont)->err |= REDIR_HARD;
		free_fdredir_except_heredoc(current_cont);
	}
	return (OUT);
}

int				minus_close_redir(t_pblks **current_cont, t_cmd **ptr_lcmd,
									t_fd fd_inout, int *i)
{
	t_list		*new_fd;

	fd_inout.flag |= CLOSE_FD;
	delete_or_insert_to_pline(ptr_lcmd, *i + 1, -1);
	new_fd = add_redir_to_block(fd_inout);
	ft_lstadd_to_end(&(*current_cont)->fd, new_fd);
	return (0);
}

int				only_num_fdafter_redir(t_fd *fd_inout)
{
	int			j;

	j = 0;
	while (fd_inout->file[j])
	{
		if (!ft_isdigit(fd_inout->file[j]))
		{
			fd_inout->flag |= REDIR_SOFT;
			return (OUT);
		}
		j++;
	}
	fd_inout->fd_new = ft_atoi(fd_inout->file);
	free(fd_inout->file);
	fd_inout->file = NULL;
	return (0);
}
