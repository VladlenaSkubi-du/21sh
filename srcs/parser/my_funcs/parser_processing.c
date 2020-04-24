#include "shell21.h"
#include "parser.h"

//int count
// printf("g_cmd nul=%s\n", g_pline->cmd);//печать для проверки
		// printf("techline cur:");
		// count = -1;
		// while (++count <= g_pline->len_tech)
		// 	printf("%3d", g_pline->tech[count]);
		// printf("\n");

	// printf("g_cmd nul=%s - len=%d\n", (*ptr_lcmd)->cmd, (*ptr_lcmd)->len_tech);//печать для проверки
	// printf("techline cur:");
	// int count = -1;
	// while (++count < (*ptr_lcmd)->len_tech)
	// 	printf("%3d", (*ptr_lcmd)->tech[count]);
	// printf("\n");

	// runner_fd = start_fd;
	// while (runner_fd)
	// {
	// 	ptr_fd = runner_fd->content;
	// 	printf("******************************\n");
	// 	printf("Fd_in is %d\n", ptr_fd->fd_in);
	// 	printf("Fd_out is %d\n", ptr_fd->fd_out);
	// 	printf("Fd_file is %s\n", ptr_fd->file);
	// 	if (ptr_fd->flag)
	// 	{
	// 		(ptr_fd->flag & CLOSE_FD) ? printf("close fd\n") : 0;
	// 		(ptr_fd->flag & CREATE_FD) ? printf("create file\n") : 0;
	// 		(ptr_fd->flag & OPEN_FD) ? printf("open file\n") : 0;
	// 		(ptr_fd->flag & REDIRECTION_FD) ? printf("redirection\n") : 0;
	// 	}
	// 	runner_fd = runner_fd->next;
	// }

void			print_all_lists(void)
{
	t_list		*runner;
	t_pblks		*ptr_block_cont;
	t_cmd		*ptr_lcmd;
	t_list		*ptr_struct_fd;
	t_list		*fd_runner;
	t_fd		*ptr_fd;
	int			end;

	runner = g_grblks;
	while (runner)
	{
		ptr_block_cont = runner->content;
		if (g_pline->tech[ptr_block_cont->end] == END_T)
			end = ptr_block_cont->end - 1;
		else
			end = ptr_block_cont->end;
		printf("______________________________\n");
		printf("NEW LIST\n");
		printf("******************************\n");
		printf("beg = %d, end = %d\n", ptr_block_cont->beg, end);
		ptr_lcmd = ptr_block_cont->lcmd;
		printf("Local saved is the same: %s\n", ptr_lcmd->cmd);
		printf("Size tech: %d\n", ptr_lcmd->len_tech);
		if (ptr_block_cont->fd)
		{
			ptr_struct_fd = ptr_block_cont->fd;
			fd_runner = ptr_struct_fd;
			while (fd_runner)
			{
				ptr_fd = fd_runner->content;
				printf("******************************\n");
				printf("Fd_in is %d\n", ptr_fd->fd_in);
				printf("Fd_out is %d\n", ptr_fd->fd_out);
				printf("Fd_file is %s\n", ptr_fd->file);
				if (ptr_fd->flag)
				{
					(ptr_fd->flag & CLOSE_FD) ? printf("close fd\n") : 0;
					(ptr_fd->flag & CREATE_FD) ? printf("create file\n") : 0;
					(ptr_fd->flag & OPEN_FD) ? printf("open file\n") : 0;
					(ptr_fd->flag & REDIRECTION_FD) ? printf("redirection\n") : 0;
				}
				fd_runner = fd_runner->next;
			}
		}
		printf("******************************\n");
		if (ptr_block_cont->flag & PIPED_IN)
			printf("pipe in\n");
		if (ptr_block_cont->flag & PIPED_OUT)
			printf("pipe out\n");
		if (ptr_block_cont->err & REDIR_HARD)
			printf("redir_hard error\n");
		if (ptr_block_cont->err & REDIR_SOFT)
			printf("redir_soft mistake\n");
		printf("______________________________\n");
		printf("\n");
		runner = runner->next;
	}
}

t_cmd			*init_parser_line(char *line)
{
	t_cmd		*parser;
	int			len_cmd;

	parser = (t_cmd*)ft_xmalloc(sizeof(t_cmd));
	parser->cmd = line;
	len_cmd = ft_strlen(parser->cmd);
	parser->tech = ft_make_techline(parser->cmd, len_cmd);
	parser->len_tech = len_cmd + 1;
	return (parser);
}

int				delete_symbols_from_parser_line(t_cmd **pline,
					int i, int num)
{
	str_shift((*pline)->cmd + i, num);
	str_shift((*pline)->tech + i, num);
	(*pline)->len_tech += num;
	return (0);
}

t_list			*create_new_list(void)
{
	t_list		*result;
	t_pblks		*ptr_cont;

	result = ft_lstnew(NULL, 0);
	result->content = (t_pblks*)ft_xmalloc(sizeof(t_pblks));
	ptr_cont = result->content;
	ptr_cont->lcmd = (t_cmd*)ft_xmalloc(sizeof(t_cmd));
	bzero_grammar_block(result->content);
	return (result);
}

void			bzero_grammar_block(t_pblks *block)
{
	t_cmd		*ptr_lcmd;
	
	ptr_lcmd = block->lcmd;
	ptr_lcmd->cmd = NULL;
	ptr_lcmd->tech = NULL;
	ptr_lcmd->len_tech = 0;
	block->beg = 0;
	block->end = 0;
	block->fd = NULL;
	block->err = 0;
	block->flag = 0;
}

int				free_parser_blocks(t_list **head)
{
	t_list		*runner;
	t_list		*tmp;
	t_pblks		*ptr_cont;
	t_cmd		*ptr_lcmd;
	t_fd		*fd_heredoc;

	runner = *head;
	while (runner)
	{
		tmp = runner;
		runner = runner->next;
		ptr_cont = tmp->content;
		free_fd_redir(&ptr_cont);
		ptr_lcmd = ptr_cont->lcmd;
		free(ptr_lcmd->cmd);
		free(ptr_lcmd->tech);
		free(ptr_lcmd);
		ptr_lcmd = NULL;
		free(ptr_cont);
		ptr_cont = NULL;
	}
	*head = NULL;
	return (0);
}