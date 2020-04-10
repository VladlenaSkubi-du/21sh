#include "shell21.h"
#include "parser.h"

int		add_to_heredoc_buf(char ***array, char *add, int *buf_size)
{
	int	i;

	i = 0;
	while ((*array)[i])
		i++;
	if (i == *buf_size)
	{
		ft_realloc_array(array, *buf_size, *buf_size + HEREDOC_BUF);
		*buf_size += HEREDOC_BUF;
	}
	(*array)[i] = ft_strdup(add);
	return (0);
}

/*
** Function remove "\\n" and and find substitutions
*/

int		null_here_line(void)
{
	size_t	i;
	char	*tmp;

	i = -1;
	tmp = ft_parsing_str(g_cmd);
	g_prompt.prompt_func = heredoc_prompt;
	free(g_cmd);
	g_cmd = tmp;
	g_cmd_size = ft_strlen(g_cmd);
	while (++i <= g_cmd_size)
	{
		if (g_techline.line[i] == BSLASH && g_techline.line[i + 1] != ENTER)
			g_techline.line[i + 1] = TEXT;
	}
	if (g_cmd[g_cmd_size - 2] == '\\' && g_cmd[g_cmd_size - 1] == '\n')
	{
		g_cmd[g_cmd_size - 2] = '\0';
		g_cmd[g_cmd_size - 1] = '\0';
	}
	return (0);
}

int		recover_g_cmd_here(void)
{
	clean_parser21();
	g_cmd = ft_strdup(g_heredoc.g_cmd_copy);
	g_cmd_size = g_heredoc.g_len_copy;
	g_techline.line = ft_strdup(g_heredoc.g_cmd_copy);
	g_techline.len = g_heredoc.g_len_copy;
	g_techline.alloc_size = g_heredoc.g_len_copy;
	return (0);
}

int		here_tab_remove(char **line)
{
	size_t	len;

	len = ft_strlen(*line);
	while ((*line)[0] == '\t')
	{
		ft_memmove(&(line[0]), &(line[1]), len);
		len--;
	}
	return (0);
}
