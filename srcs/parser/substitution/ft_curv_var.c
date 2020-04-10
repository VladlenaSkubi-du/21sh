#include "shell21.h"
#include "parser.h"

/*
** Function finds and check subfunction of type "${parameter}"
** ${parameter:-word} and ${parameter-word}
** ${parameter:=word} and ${parameter=word}
** ${parameter:?word} and ${parameter?word}
** ${parameter:+word} and ${parameter+word}
** substring processing
** ${#parameter}
** ${parameter%[word]} and ${parameter%%[word]}
** ${parameter#[word]} and ${parameter##[word]}
*/

int		ft_type_param_check(t_ltree *sub, char **find, size_t *i)
{
	char	*oper;

	if ((oper = ft_strstr(*find, "-")))
		return (ft_param_colon_dash(sub, find, oper, i));
	else if ((oper = ft_strstr(*find, "=")))
		return (ft_param_colon_equal(sub, find, oper, i));
	else if ((oper = ft_strstr(*find, "?")) && oper != *find)
		return (ft_param_colon_qmark(sub, find, oper, i));
	else if ((oper = ft_strstr(*find, "+")))
		return (ft_param_colon_plus(sub, find, oper, i));
	else if ((oper = ft_strstr(*find, "#")))
	{
		if (oper == *find)
			return (ft_substring_len(sub, find, oper, i));
		else
			return (ft_substring_s_l_prefix(sub, find, oper, i));
	}
	else if ((oper = ft_strstr(*find, "%")))
		return (ft_substring_s_l_suffix(sub, find, oper, i));
	else
		return (ft_param_empty(sub, find, i));
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:-[word]} and ${parameter-[word]}
*/

int		ft_param_colon_dash(t_ltree *sub, char **find, char *oper, size_t *i)
{
	int		colon;
	char	*tmp;
	size_t	size;

	colon = (*(oper - 1) == ':') ? 1 : 0;
	size = ft_strlen(*find);
	tmp = (colon) ? ft_strndup(*find, oper - *find - 1) :
		ft_strndup(*find, oper - *find);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		if (*tmp != '\0')
		{
			free(*find);
			ft_reglue(i, size + 2, sub);
			return (insert_str_in_loc_strs(sub, &tmp, i, TEXT));
		}
		else if (*tmp == '\0' && !colon)
		{
			free(*find);
			return (ft_reglue(i, size + 3, sub));
		}
		else
			return (ft_param_word_sub(sub, find, oper, i));
	}
	return (ft_param_word_sub(sub, find, oper, i));
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:=[word]} and ${parameter=[word]}
*/

int		ft_param_colon_equal(t_ltree *sub, char **find, char *oper, size_t *i)
{
	int		colon;
	char	*tmp;
	size_t	size;

	colon = (*(oper - 1) == ':') ? 1 : 0;
	size = ft_strlen(*find);
	tmp = (colon) ? ft_strndup(*find, oper - *find - 1) :
		ft_strndup(*find, oper - *find);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		if (*tmp != '\0')
		{
			free(*find);
			ft_reglue(i, size + 2, sub);
			return (insert_str_in_loc_strs(sub, &tmp, i, TEXT));
		}
		else if (*tmp == '\0' && !colon)
		{
			free(*find);
			return (ft_reglue(i, size + 3, sub));
		}
		else
			return (assignment_in_curv_var(sub, find, oper, i));
	}
	return (assignment_in_curv_var(sub, find, oper, i));
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:?[word]} and ${parameter?[word]}
*/

int		ft_param_colon_qmark(t_ltree *sub, char **find, char *oper, size_t *i)
{
	int		colon;
	char	*tmp;
	size_t	size;

	colon = (*(oper - 1) == ':') ? 1 : 0;
	size = ft_strlen(*find);
	tmp = (colon) ? ft_strndup(*find, oper - *find - 1) :
		ft_strndup(*find, oper - *find);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		if (*tmp != '\0')
		{
			free(*find);
			ft_reglue(i, size + 2, sub);
			return (insert_str_in_loc_strs(sub, &tmp, i, TEXT));
		}
		else if (*tmp == '\0' && !colon)
		{
			free(*find);
			return (ft_reglue(i, size + 3, sub));
		}
		else
			return (ft_param_error_msg(sub, find, oper));
	}
	return (ft_param_error_msg(sub, find, oper));
}

/*
** Function finds and substitudes classic vars of types
** ${parameter:?[word]} and ${parameter?[word]}
*/

int		ft_param_colon_plus(t_ltree *sub, char **find, char *oper, size_t *i)
{
	int		colon;
	char	*tmp;
	size_t	size;

	colon = (*(oper - 1) == ':') ? 1 : 0;
	size = ft_strlen(*find);
	tmp = (colon) ? ft_strndup(*find, oper - *find - 1) :
		ft_strndup(*find, oper - *find);
	if ((tmp = ft_find_var_value(&tmp)) != NULL)
	{
		if (*tmp != '\0')
			return (ft_param_word_sub(sub, find, oper, i));
		else if (*tmp == '\0' && colon)
		{
			free(*find);
			return (ft_reglue(i, size + 3, sub));
		}
		else
			return (ft_param_word_sub(sub, find, oper, i));
	}
	free(*find);
	return (ft_reglue(i, size + 3, sub));
}
