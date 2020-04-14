#include "shell21.h"
#include "parser.h"

/*
** Here we come with the counters of the beginning and the end of the 
** final processes and all the fds defined after redirection block
** Flags are defined also before in the parser block. Here we finish the
** preparation by forming the environ array for execution, forming 
** argc and argv variables
*/

int		before_exec(t_ltree *sub)
{
	int	err;
	
	if ((err = ft_substitution(sub)) & (ERR_OUT | ERR_IN))
		return (OUT);
	assignment(sub);
	if (sub->flags & (ERR_OUT))
	{
	 	sub->err_i = ERR_OUT | VARIABLE_ERROR;
		ft_error_vars(sub, 0, NULL);
		ft_lst_ltree_clear(&g_start_list);
		return (OUT);
	}
	argv_forming(sub);
	if (sub->flags & ERR_R)
		ft_error_redir(sub);
	return (0);
}

int		argv_forming(t_ltree *sub)
{
	t_word	word;
	int		i;
	int		p;
	int		count;

	p = sub->start;
	sub->ar_c = ft_count_words(&(sub->l_tline.line[0]), SPACE,
				sub->l_tline.len);
	sub->ar_v = (char **)ft_xmalloc(sizeof(char *) * (sub->ar_c + 1));
	i = 0;
	count = 0;
	while (count < sub->ar_c)
	{
		word = ft_give_me_word(&(sub->l_tline.line[p]), SPACE,
			sub->l_tline.len - p);
		word.start += p;
		(sub->ar_v)[i] = (char *)ft_xmalloc(sizeof(char) * (word.len + 1));
		ft_memcpy((sub->ar_v)[i], sub->l_cmd + word.start, word.len);
		p = word.start + word.len;
		i++;
		count++;
	}
	sub->ar_v[sub->ar_c] = NULL;
	return (0);
}

t_word	ft_give_me_word(char const *s, char c, size_t len)
{
	t_word	k;
	size_t	i;
	size_t	l;

	i = 0;
	while (s[i] == c)
		i++;
	k.start = i;
	l = 0;
	while (s[i] != c && i < len)
	{
		l++;
		i++;
	}
	k.len = l;
	return (k);
}

int		ft_local_copy_lines(t_ltree *sub, char *cmd, char *tline)
{
	sub->l_cmd = ft_strndup(&cmd[sub->start], sub->end - sub->start);
	sub->l_tline.line = ft_strndup(&tline[sub->start],
		sub->end - sub->start + 1);
	sub->l_tline.len = sub->end - sub->start;
	sub->l_tline.alloc_size = sub->end - sub->start + 1;
	sub->start = 0;
	sub->end = sub->l_tline.len;
	return (0);
}

int		erroring_andor_pipe(t_ltree *final, size_t *i, size_t bl_end)
{
	if (*i == g_techline.len)
	{
		final->flags |= ERR_OUT;
		error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), "newline");
		return (OUT);
	}
	else if (*i == bl_end || g_techline.line[*i] == PIPE)
	{
		final->err_i = *i;
		final->err = ft_find_token_sep(&g_cmd[*i]);
		final->flags |= ERR_OUT;
		final->flags |= ERR_REDIR << 16;
		if (final->err_i < g_techline.len)
			error_handler((SYNTAX_ERROR | (ERR_REDIR << 9)), final->err);			
	}
	g_prompt.prompt_func = main_prompt;
	return (0);
}