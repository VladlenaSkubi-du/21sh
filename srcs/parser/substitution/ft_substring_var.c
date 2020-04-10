#include "shell21.h"
#include "parser.h"

/*
** Function finds and substitudes classic vars of type "${#parameter}"
*/

int		ft_substring_len(t_ltree *sub, char **line, char *oper, size_t *i)
{
	size_t	size;
	char	*tmp;
	int		ret;

	size = ft_strlen(*line);
	ft_reglue(i, size + 2, sub);
	tmp = ft_strdup(oper + 1);
	free(*line);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		ret = ft_strlen(tmp);
		free(tmp);
		tmp = ft_itoa(ret);
		insert_str_in_loc_strs(sub, &tmp, i, TEXT);
	}
	else
		ft_reglue(i, 1, sub);
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter#[word]} and ${parameter##[word]}
*/

int		ft_substring_s_l_prefix(t_ltree *sub, char **line,
			char *oper, size_t *i)
{
	size_t	len;
	char	*tmp;
	char	*pattern;

	ft_reglue(i, ft_strlen(*line) + 2, sub);
	*oper = '\0';
	oper += (oper[1] == '#') ? 2 : 1;
	tmp = ft_strdup(*line);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		pattern = ft_parsing_str(oper);
		free(*line);
		len = ft_strlen(pattern);
		if (!ft_strncmp(tmp, pattern, len))
		{
			*line = ft_strdup(tmp + len);
			free(tmp);
			tmp = *line;
		}
		free(pattern);
		insert_str_in_loc_strs(sub, &tmp, i, TEXT);
	}
	else
		ft_reglue(i, 1, sub);
	return (0);
}

/*
** Function finds and substitudes classic vars of types
** ${parameter%[word]} and ${parameter%%[word]}
*/

int		ft_substring_s_l_suffix(t_ltree *sub, char **line,
			char *oper, size_t *i)
{
	size_t	len;
	size_t	len_tmp;
	char	*tmp;
	char	*pattern;

	ft_reglue(i, ft_strlen(*line) + 2, sub);
	*oper = '\0';
	oper += (oper[1] == '%') ? 2 : 1;
	tmp = ft_strdup(*line);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		pattern = ft_parsing_str(oper);
		free(*line);
		len = ft_strlen(pattern);
		len_tmp = ft_strlen(tmp);
		if (!ft_strncmp(&tmp[len_tmp - len], pattern, len))
			tmp[len_tmp - len] = '\0';
		free(pattern);
		insert_str_in_loc_strs(sub, &tmp, i, TEXT);
	}
	else
		ft_reglue(i, 1, sub);
	return (0);
}
