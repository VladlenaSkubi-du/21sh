#include "shell21.h"
#include "parser.h"

int			tilda_expansion(t_cmd **cmd_part)
{
	return (0);
}

int			dollar_expansion(t_cmd **cmd_part, char **str)
{
	t_cmd	*str_cmd;
	int		i;
	int		start;

	str_cmd = (cmd_part == NULL && str) ?
		init_parser_line(*str) : *cmd_part;
	i = -1;
	while (++i < str_cmd->len_tech)
	{
		if (str_cmd->tech[i] == DOLLAR &&
				(str_cmd->tech[i + 1] == DOLLAR ||
				str_cmd->tech[i + 1] == WORD_P))
		{
			start = i + 1;
			dollar_expansion_processing(&str_cmd, &i, start);
		}
	}
	if (cmd_part == NULL && str)
	{
		*str = str_cmd->cmd;
		free_parser_line(&str_cmd);
	}
	else
		*cmd_part = str_cmd;
	return (0);
}

int			dollar_expansion_processing(t_cmd **str_cmd, int *i, int start)
{
	char	*find;
	char	*tmp;
	int		j;
	int		len;
	
	j = start;
	find = NULL;
	if ((*str_cmd)->tech[start] == DOLLAR)
	{
		find = ft_strdup("$");
		delete_or_insert_to_pline(str_cmd, start + 1, -2);
		find = find_var_in_arrays(&find);
	}
	else
	{
		while (j < (*str_cmd)->len_tech && (*str_cmd)->tech[j] == WORD_P)
			j++;
		find = ft_strndup((*str_cmd)->cmd + start, j - start);
		delete_or_insert_to_pline(str_cmd, start, start - j - 1);
		find = find_var_in_arrays(&find);
	}
	if (find == NULL)
		return (0);
	len = ft_strlen(find);
	tmp = ft_strdup((*str_cmd)->cmd);
	str_shift(tmp + start - 1, len);
	ft_strcpy(tmp + start - 1, find);
	free(find);
	free_parser_line(str_cmd);
	*str_cmd = init_parser_line(tmp);
	*i += len;
	return (0);
}