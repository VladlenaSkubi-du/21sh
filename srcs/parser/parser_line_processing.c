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

int				expansion_pline_processing(t_cmd **lcmd, int *i,
					int start, char *find)
{
	char	*old_cmd;
	int		len;

	len = ft_strlen(find);
	old_cmd = (char*)ft_xmalloc(ft_strlen((*lcmd)->cmd) + len + 1);
	ft_strncpy(old_cmd, (*lcmd)->cmd, start - 1);
	ft_strcpy(old_cmd + start - 1, find);
	ft_strcpy(old_cmd + start - 1 + len, (*lcmd)->cmd + start - 1);
	free(find);
	free_parser_line(lcmd);
	*lcmd = init_parser_line(old_cmd);
	*i = start - 1 + len;
	return (0);
}