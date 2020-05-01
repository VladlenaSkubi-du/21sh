#include "shell21.h"
#include "parser.h"

int			tilda_expansion(t_cmd **cmd_part)
{
	return (0);
}

int			dollar_expansion(t_cmd **cmd_part, char **str)
{
	t_cmd	*str_cmd;

	if (cmd_part == NULL && str)
	{
		str_cmd = init_parser_line(*str);
		dollar_expansion_loop(&str_cmd);
		*str = ft_strdup(str_cmd->cmd);
		free_parser_line(&str_cmd); //can be leaks
	}
	else
		dollar_expansion_loop(cmd_part);
	return (0);
}

int			dollar_expansion_loop(t_cmd **lcmd)
{
	int		i;
	int		start;
	char	*find;
	
	i = -1;
	while (++i < (*lcmd)->len_tech)
	{
		if ((*lcmd)->tech[i] == DOLLAR && (*lcmd)->tech[i + 1] == DOLLAR)
		{
			start = i + 1;
			find = ft_strdup("$");
			delete_or_insert_to_pline(lcmd, start + 1, -2);
			dollar_expansion_processing(lcmd, &i, start, find);
		}
		else if ((*lcmd)->tech[i] == DOLLAR && (*lcmd)->tech[i + 1] == WORD_P)
		{
			start = i + 1;
			while (++i < (*lcmd)->len_tech && (*lcmd)->tech[i] == WORD_P)
				;
			find = ft_strndup((*lcmd)->cmd + start, i - start);
			delete_or_insert_to_pline(lcmd, i, start - i - 1);
			dollar_expansion_processing(lcmd, &i, start, find);
		}
	}
	return (0);
}

int			dollar_expansion_processing(t_cmd **lcmd, int *i,
				int start, char *find)
{
	char	*old_cmd;
	int		len;

	find = find_var_in_arrays(&find);
	if (find == NULL)
		return (0);
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