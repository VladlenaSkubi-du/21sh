#include "shell21.h"
#include "parser.h"

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

void			free_parser_line(t_cmd **pline)
{
	free((*pline)->cmd);
	(*pline)->cmd = NULL;
	free((*pline)->tech);
	(*pline)->tech = NULL;
	free(*pline);
	*pline = NULL;
}

int				delete_or_insert_to_pline(t_cmd **pline,
					int i, int num)
{
	str_shift((*pline)->cmd + i, num);
	str_shift((*pline)->tech + i, num);
	(*pline)->len_tech += num;
	return (0);
}

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
