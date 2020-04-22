#include "shell21.h"
#include "parser.h"

void			bzero_fd_block(t_fd *fd_block)
{
	fd_block->fd_in = -1;
	fd_block->fd_out = -1;
	fd_block->file = NULL;
	fd_block->flag = 0;
}

int				find_fdbefore_redir(t_cmd **ptr_lcmd,
					t_fd *fd_inout, int *i)
{
	int			j;

	if (*i == 0)
		return (0);
	j = (*i) - 1;
	while (j > 0 &&
			(*ptr_lcmd)->tech[j] == WORD_P &&
			ft_isdigit((*ptr_lcmd)->cmd[j]))
		j--;
	if (j > 0 && (*ptr_lcmd)->tech[j] != SPACE)
	{
		fd_inout->flag |= REDIR_SOFT;
		return (OUT);
	}
	if (*i != j)
	{
		j++;
		fd_inout->fd_out = ft_atoi(&(*ptr_lcmd)->cmd[j]);
		delete_symbols_from_parser_line(ptr_lcmd, *i, 0 - j);
		*i -= j;
	}
	return (0);
}

/*
** @flag can be 'n' = number (for >& or <&)
**				'w' = word (for >>, >, <)
** Here we check if there are only spaces till the end of line or
** the end of line itself - that will be the redirection error
** If we do not come into the second cycle, it means that there is
** not a word but some syntax sign after the space - that is also
** the redirection error
*/

int				find_fdafter_redir(t_cmd **ptr_lcmd,
					t_fd *fd_inout, int *i, char flag)
{
	int			j;
	int			start;

	j = *i;
	while ((*ptr_lcmd)->tech[j] != END_T && (*ptr_lcmd)->tech[j] == SPACE)
		j++;
	if ((*ptr_lcmd)->tech[j] == END_T)
	{
		fd_inout->flag |= REDIR_HARD;
		return (OUT);
	}
	start = j;
	while ((*ptr_lcmd)->tech[j] != END_T && ((*ptr_lcmd)->tech[j] == WORD_P ||
			(*ptr_lcmd)->tech[j] == TEXT))
		j++;
	if (start - j == 0)
	{
		fd_inout->flag |= REDIR_HARD;
		return (OUT);
	}
	fd_inout->file = ft_strndup((*ptr_lcmd)->cmd + start, j);
	return (0);
}

t_list			*add_redir_to_block(t_pblks **current_cont, t_fd fd_inout)
{
	t_list		*result;
	t_fd		*ptr_fd;

	result = ft_lstnew(NULL, 0);
	result->content = (t_fd*)ft_xmalloc(sizeof(t_fd));
	ptr_fd = result->content;
	ptr_fd->fd_in = fd_inout.fd_in;
	ptr_fd->fd_out = fd_inout.fd_out;
	ptr_fd->flag = fd_inout.flag;
	return (result);
}

int				activate_redir_error(t_pblks **current_cont, int fd_flag)
{
	if (fd_flag & REDIR_SOFT)
		(*current_cont)->err |= REDIR_SOFT;
	else
	{
		(*current_cont)->err |= REDIR_HARD;
		free_fd_blocks(current_cont);
	}
	return (OUT);
}

int				free_fd_blocks(t_pblks **current_cont)
{
	t_list		*runner_fd;
	t_list		*tmp_fd;
	t_fd		*ptr_fd;

	runner_fd = (*current_cont)->fd;
	while (runner_fd)
	{
		tmp_fd = runner_fd;
		runner_fd = runner_fd->next;
		ptr_fd = tmp_fd->content;
		free(ptr_fd->file);
		free(ptr_fd);
		free(tmp_fd);
		tmp_fd = NULL;
	}
	(*current_cont)->fd = NULL;
	return (0);
}