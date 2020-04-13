#include "shell21.h"
#include "parser.h"

/*
** Function finds and substitudes classic vars of type "$PATH"
*/

int		ft_find_var(t_ltree *sub)
{
	size_t	i;
	size_t	size;
	char	*find;

	i = -1;
	while (++i < sub->l_tline.len)
	{
		if (sub->l_tline.line[i] == DOLLAR && sub->l_tline.line[i + 1] != OBRACE &&
			sub->l_tline.line[i + 1] != OPAREN)
		{
			size = 1;
			while (i + size < sub->end && sub->l_tline.line[i + size] == WORD_P)
				size++;
			find = ft_strndup(&sub->l_cmd[i + 1], size - 1);
			if ((find = ft_find_var_value(&find)) != NULL)
			{
				ft_reglue(&i, size - 1, sub);
				insert_str_in_loc_strs(sub, &find, &i, TEXT);
			}
			else
				ft_reglue(&i, size, sub);
		}
	}
	return (0);
}

/*
** Function finds and substitudes vars of type "${parameter}"
*/

int		ft_find_curv_var(t_ltree *sub)
{
	size_t	i;
	size_t	size;
	char	*find;

	i = -1;
	while (++i < sub->l_tline.len)
	{
		if (sub->l_tline.line[i] == DOLLAR &&
			sub->l_tline.line[i + 1] == OBRACE)
		{
			size = 2;
			while (i + size < sub->end && sub->l_tline.line[i + size] != CBRACE)
				size++;
			find = ft_strndup(&sub->l_cmd[i + 2], size - 2);
			return (ft_type_param_check(sub, &find, &i));
		}
	}
	return (0);
}

char	*ft_find_var_value(char **find)
{
	int		li;
	int		sj;
	char	*res;

	li = -1;
	sj = -1;
	res = NULL;
	if ((li = find_in_variables(g_rdovar, &sj, *find)) != -1)
		res = ft_strdup(&g_rdovar[li][sj]);
	else if ((li = find_in_variables(g_env, &sj, *find)) != -1)
		res = ft_strdup(&g_env[li][sj]);
	else if ((li = find_in_variables(g_shvar, &sj, *find)) != -1)
		res = ft_strdup(&g_shvar[li][sj]);
	else if ((li = find_in_variables(g_lovar, &sj, *find)) != -1)
		res = ft_strdup(&g_lovar[li][sj]);
	free(*find);
	return (res);
}

int		ft_param_empty(t_ltree *sub, char **find, size_t *i)
{
	char	*tmp;
	size_t	size;

	size = ft_strlen(*find);
	if ((tmp = ft_find_var_value(find)) != NULL)
	{
		ft_reglue(i, size + 2, sub);
		insert_str_in_loc_strs(sub, &tmp, i, TEXT);
	}
	else
		ft_reglue(i, size + 3, sub);
	return (0);
}

int		ft_error_vars(t_ltree *sub, int err, char *msg)
{
	sub->flags |= ERR_OUT;
	sub->err_i |= err;
	if (msg)
		sub->err = ft_strdup(msg);
	if (!(sub->err_i & ERR_UNSET << 9 || sub->err_i & ERR_SET << 9))
		sub->err_i |= ERR_RDONLY << 9;
	error_handler(sub->err_i, sub->err);
	return (err);
}
