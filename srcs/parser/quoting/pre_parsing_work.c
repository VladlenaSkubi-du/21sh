#include "shell21.h"
#include "parser.h"

/*
** Simle to remove unused number (num_sym) of symbols by moving end of g_cmd
** g_techline.line and resizing g_cmd_size and g_techline.len.
*/

int		ft_reglue(size_t *i, int num, t_ltree *sub)
{
	size_t	z;
	size_t	size;

	ft_memmove(&(sub->l_cmd[*i]), &(sub->l_cmd[*i + num]),
	sub->l_tline.len - (*i + num - 1));
	ft_memmove(&(sub->l_tline.line[*i]), &(sub->l_tline.line[*i + num]),
	sub->l_tline.len - (*i + num - 1));
	sub->l_tline.len -= num;
	sub->end -= num;
	z = sub->l_tline.len;
	size = z + num;
	while (++z <= size)
	{
		sub->l_cmd[z] = '\0';
		sub->l_tline.line[z] = '\0';
	}
	return (0);
}

int		pre_parsing_squote(size_t *i, t_ltree *sub)
{
	char	*end;

	end = sub->l_tline.line;
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
	size_t	i;

	i = 0;
	end = sub->l_tline.line;
	while (i < sub->l_tline.len)
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
