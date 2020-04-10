#include "shell21.h"
#include "parser.h"

/*
** Is used in parser to execute the assignment command "VARIABLE=VALUE"
** Checks all the arrays if such variable exists and if not found - 
** adds the variable to @g_lovar (local shell variables that exist only
** within the session)
** @g_rdovar can not be changed by the user, therefore if the variable
** is one of the rdonly shell variables - there is an error
*/

int			find_assignment_in_vars(char *sub, size_t var,
				size_t eq, size_t val)
{
	int			li;
	int			sy;
	char		*find;

	li = -1;
	sy = -1;
	find = ft_strndup(sub + var, eq - var);
	if ((li = find_in_variables(g_rdovar, &sy, find)) != -1)
		return (ERR_OUT);
	if ((li = find_in_variables(g_env, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, ft_strndup(sub + var,
			val - var + 1),	&g_env[li]));
	else if ((li = find_in_variables(g_shvar, &sy, find)) != -1)
	{
		insert_assign_to_arrays(find, ft_strndup(sub + var, val - var + 1),
			&g_shvar[li]);
		return (check_if_histsize_changed());
	}
	else if ((li = find_in_variables(g_lovar, &sy, find)) != -1)
		return (insert_assign_to_arrays(find, ft_strndup(sub + var,
			val - var + 1), &g_lovar[li]));
	free(find);
	find = ft_strndup(sub + var, val - var + 1);
	add_to_local_variables(find); //TODO доделать
	return (0);
}

int			assignment_in_curv_var(t_ltree *sub, char **line,
				char *oper, size_t *i)
{
	int		j;
	int		len;
	char	*buf;
	
	ft_colon_check(&len, line, &oper, &j);
	buf = ft_parsing_str(oper + 1);
	ft_reglue(i, len + 2, sub);
	oper[1] = '\0';
	j = oper - *line;
	*line = ft_strrejoin(*line, buf);
	if ((j = find_assignment_in_vars(*line, 0, j, ft_strlen(*line))) ==
		(ERR_OUT))
		sub->err = ft_strndup(*line, ft_strchri(*line, '='));
	free (*line);
	insert_str_in_loc_strs(sub, &buf, i, TEXT);
	return (sub->err_i |= j);
}

int			ft_colon_check(int *len, char **line, char **oper, int *j)
{
	*len = ft_strlen(*line);
	if ((*j = ft_strchri(*line, ':')) != -1)
	{
		ft_memmove(&(line[0][*j]), &(line[0][*j + 1]), *len - *j);
		line[0][--(*len)] = '\0';
		*oper -= 1;
		(*len)++;
	}
	return (0);
}
