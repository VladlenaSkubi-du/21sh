#include "shell21.h"
#include "parser.h"

int			prepare_and_exec(void)
{
	t_list		*pblk_hered;
	t_pblks		*pblk_cont;
	t_cmd		*ptr_lcmd;

	if (check_hard_errors() == OUT)
		return (0);
	pblk_hered = g_grblks;
	while (pblk_hered)
	{
		pblk_cont = (t_pblks*)pblk_hered->content;
		prepare_fdredir(&pblk_cont);
		pblk_hered->content = pblk_cont;
		ptr_lcmd = pblk_cont->lcmd;
		if (ptr_lcmd->len_tech > 1)
		{
			tilda_expansion(&ptr_lcmd);
			dollar_expansion(&ptr_lcmd, NULL);
			pblk_cont->lcmd = ptr_lcmd;
		}
			// printf("Before form and exec\n");
			// print_all_lists();
		pblk_hered->content = pblk_cont;
		form_and_exec(pblk_cont);
		pblk_hered = pblk_hered->next;
	}
	return (0);
}

int			prepare_fdredir(t_pblks **pblk_cont)
{
	t_list		*fd_runner;
	t_list		*last_fd;

	last_fd = NULL;
	fd_runner = (*pblk_cont)->fd;
	while (fd_runner)
	{
		if (prepare_fdredir_fd(&fd_runner) == -1)
		{
			(*pblk_cont)->err |= REDIR_SOFT;
			free_fdredir_from(&fd_runner);
			if (last_fd)
				last_fd->next = NULL;
			break ;
		}
		last_fd = fd_runner;
		fd_runner = fd_runner->next;
	}
	if (fd_runner != NULL && last_fd == NULL)
		(*pblk_cont)->fd = NULL;
	return (0);
}

int			prepare_fdredir_fd(t_list **fd_runner)
{
	t_fd		*fd_cont;

	fd_cont = (t_fd*)(*fd_runner)->content;
	if (!(fd_cont->flag & REDIRECTION_FD))
	{
		if (fd_cont->flag & OPENIN_FD)
		{
			fd_cont->fd_new = open(fd_cont->file, O_RDONLY |
				O_CLOEXEC | O_SYNC | O_NOCTTY);
		}
		else if (fd_cont->flag & OPEN_FD)
		{
			fd_cont->fd_new = open(fd_cont->file, O_CREAT |
				O_WRONLY | O_TRUNC | O_CLOEXEC | O_SYNC | O_NOCTTY,
				S_IRUSR | S_IWUSR);
		}
		else if (fd_cont->flag & CREATE_FD)
			fd_cont->fd_new = open(fd_cont->file, O_CREAT |
				O_WRONLY | O_APPEND | O_CLOEXEC | O_SYNC | O_NOCTTY,
				S_IRUSR | S_IWUSR);
		if (fd_cont->fd_new < 0 && !(fd_cont->flag & CLOSE_FD))
			return (-1);
	}
	return (0);
}

char		**form_argv(t_cmd *lcmd, int *eargc, int len)
{
	char		**args;
	char		*arg;
	int			i;
	int			j;

	args = (char**)ft_xmalloc(sizeof(char*) * len);
		print_techline(lcmd->cmd, lcmd->tech, lcmd->len_tech);
	i = 0;
	j = 0;
	while (i < lcmd->len_tech - 1)
	{
		arg = new_arg_from_lcmd(lcmd, &i);
		if (arg == NULL || arg[0] == '\0')
		{
			free(arg);
			break ;
		}
		args[j] = arg;
		j++;
		if (j >= len)
			args = extended_local_agrv(args, &len);
	}
	*eargc = j;
	return (args);
}

char		**extended_local_agrv(char **args, int *len)
{
	args = ft_realloc_array(&args, *len, (*len) * 2);
	(*len) *= 2;
	return (args);
}

char		*new_arg_from_lcmd(t_cmd *lcmd, int *i)
{
	char		*cmd;
	int			start;

	cmd = NULL;
	while (*i < lcmd->len_tech - 1 && lcmd->tech[*i] == SPACE)
		(*i)++;
	start = *i;
	if (lcmd->tech[*i] == WORD_P)
		while (*i < lcmd->len_tech - 1 && lcmd->tech[*i] == WORD_P)
			(*i)++;
	else if (lcmd->tech[*i] == TEXT)
		while (*i < lcmd->len_tech - 1 && lcmd->tech[*i] == TEXT)
			(*i)++;
	else
		(*i)++;
	if (start < lcmd->len_tech && lcmd->tech[start] == ENTER &&
			lcmd->tech[start + 1] == END_T)
		return (NULL);
	cmd = ft_strndup(lcmd->cmd + start, *i - start);
	printf("cmd = %s\n", cmd);
	return (cmd);
}
