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
	t_ltree *buf;

	buf = (t_ltree *)ft_xmalloc(sizeof(t_ltree));
	ltree_init(buf);
	buf->lcmd.cmd = ft_strdup(g_pline.cmd);
	buf->lcmd.tech = ft_make_techline(buf->lcmd.cmd, ft_strlen(buf->lcmd.cmd) + 1);
	buf->end = buf->l_tline.len;
	ft_substitution(buf);
	free(g_pline.cmd);
	g_pline.cmd = buf->l_cmd;
	g_pline.len = buf->l_tline.len;
	buf->l_cmd = NULL;
	ft_one_ltree_clear(buf);
	g_prompt.prompt_func = heredoc_prompt;
	if (g_pline.cmd[g_pline.len - 3] == '\\' && g_pline.cmd[g_pline.len - 2] == '\n')
	{
		g_pline.cmd[g_pline.len - 3] = '\0';
		g_pline.cmd[g_pline.len - 2] = '\0';
	}
	add_to_heredoc_buf(&g_heredoc.buf, g_pline.cmd, &g_heredoc.buf_size);
	return (0);
}

// int		recover_g_cmd_here(void)
// {
// 	clean_parser();
// 	g_pline.cmd = ft_strdup(g_heredoc.g_cmd_copy);
// 	g_cmd_size = g_heredoc.g_len_copy;
// 	g_techline.line = ft_strdup(g_heredoc.g_cmd_copy);
// 	g_techline.len = g_heredoc.g_len_copy;
// 	g_techline.alloc_size = g_heredoc.g_len_copy;
// 	return (0);
// }

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
