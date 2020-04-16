#include "shell21.h"
#include "parser.h"

// исправить проверку на аргументы, на команду, на несколько присвоений. 
// лучше работать на стадии c разбитием на  argv, чтобы понимать есть ли ещё команды

int		assignment(t_ltree *sub)
{
	size_t 	eq;
	size_t	var;
	size_t	val;

	eq = 0;
	while (eq < sub->lcmd.len)
	{
		if (sub->lcmd.tech[eq] == EQUAL)
		{
			var = (eq != 0) ? eq - 1 : 0;
			val = (eq != sub->end) ? eq + 1 : sub->end;
			while (sub->lcmd.tech[var] != SPACE && var != 0)
				var--;
			(sub->lcmd.tech[var] == SPACE) ? var++ : 0;
			while (sub->lcmd.tech[val] != SPACE && val < sub->l_tline.len)
				val++;
			val--;
			if (is_it_argv_n(sub, var) == OUT)
				break ;
			if (get_assign_and_add(sub, &var, &eq, &val) == OUT)
				break ;
		}
		eq++;
	}
	return (0);
}

int		get_assign_and_add(t_ltree *sub, size_t *var, size_t *eq, size_t *val)
{
	size_t	i;
	char	*buf;

	if (*var == *eq)
		return (it_is_command(sub, &i, var));
	i = *val + 1;
	while (i < sub->lcmd.len && sub->lcmd.tech[i] == SPACE)
		i++;
	if (i == sub->lcmd.len)
	{
		sub->flags |= ERR_IN;
		if ((sub->flags |= find_assignment_in_vars(sub->lcmd.cmd,
			*var, *eq, *val)) & (ERR_OUT))
			sub->err = ft_strndup(&sub->lcmd.cmd[*var], *eq - *var);
		*eq = *val;
		return (0);
	}
	else
	{
		buf = ft_strndup(sub->lcmd.cmd + *var, *val - *var + 1);
		add_new_to_exec_env(&(sub->envir), &buf);
		ft_reglue(var, *val - *var + 1, sub);
		*eq = *var;
	}
	return (0);
}

int		it_is_command(t_ltree *sub, size_t *i, size_t *var)
{
	*i = sub->start;
	while (*i < *var && sub->lcmd.tech[*i] == SPACE)
		(*i)++;
	if (*i == *var)
		ft_reglue(i, 1, sub);
	return (OUT);
}

int		is_it_argv_n(t_ltree *sub, size_t var)
{
	var > sub->start ? var-- : 0;
	while (var > sub->start && sub->lcmd.tech[var] == SPACE)
		var--;
	if (var == sub->start)
		return (0);
	else
		return (OUT);
}
