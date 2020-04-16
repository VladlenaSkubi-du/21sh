#include "shell21.h"
#include "parser.h"

/*
** Simle to remove unused number (num_sym) of symbols by moving end of g_pline.cmd
** g_pline.tech and resizing g_pline.len and g_pline.len.
*/

int		ft_reglue(int *i, int num, t_ltree *sub)
{
	int	z;
	int	size;

	ft_memmove(&(sub->lcmd.cmd[*i]), &(sub->lcmd.cmd[*i + num]),
	sub->lcmd.len - (*i + num - 1));
	ft_memmove(&(sub->lcmd.tech[*i]), &(sub->lcmd.tech[*i + num]),
	sub->lcmd.len - (*i + num - 1));
	sub->lcmd.len -= num;
	sub->end -= num;
	z = sub->lcmd.len;
	size = z + num;
	while (++z <= size)
	{
		sub->lcmd.cmd[z] = '\0';
		sub->lcmd.tech[z] = '\0';
	}
	return (0);
}

int		pre_parsing_squote(int *i, t_ltree *sub)
{
	char	*end;

	end = sub->lcmd.tech;
	if (end[*i] == SQUOTE || end[*i] == DQUOTE)
	{
		ft_reglue(i, 1, sub);
		while (end[*i] != SQUOTE && end[*i] != DQUOTE)
			(*i)++;
		ft_reglue(i, 1, sub);
	}
	return (0);
}

/*
** This function and subfunctions needs to cut and glue line before parsing.
** It shall be done by POSIX to remove \, "" and '' from line
*/

int		pre_parsing_cut_glue(t_ltree *sub)
{
	char	*end;
	int		i;

	i = 0;
	end = sub->lcmd.tech;
	while (i < sub->lcmd.len)
	{
		pre_parsing_squote(&i, sub);
		if (end[i] == ENTER)
			ft_reglue(&i, 1, sub);
		i++;
	}
		// printf("techline pre:");//печать для проверки
		// i = -1;
		// while (++i < sub->l_tline.len + 1)
		// 	printf("%3d", sub->l_tline.line[i]);
		// printf("\n");
		// printf("l_cmd pre=%s<end\n", sub->l_cmd);
	return (0);
}
