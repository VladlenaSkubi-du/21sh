#include "shell21.h"
#include "parser.h"

void			free_fdredir_content(t_list **runner_fd,
					t_fd *ptr_fd)
{
	free(ptr_fd->file);
	ptr_fd->file = NULL;
	free((*runner_fd)->content);
	(*runner_fd)->content = NULL;
}

void			free_pblock_content(t_list **runner_blk,
					t_pblks	**ptr_cont)
{
	free_parser_line(&(*ptr_cont)->lcmd);
	free((*runner_blk)->content);
	(*runner_blk)->content = NULL;
}
