#include "shell21.h"
#include "readline.h"

int					analyse_techline_compl(char *compl, char *tech,
						int len, int *pool)
{
	int				i;

	i = len - 1;
	if (check_quoting_of_syntax(tech, i))
		return (-1);
	i = pass_symbols_compl(compl, tech, i, pool);
	if (*pool == 1 || *pool == 3)
		return (i);
	if (i < 0)
		return (-1);
	if (tech[i] == BSLASH || tech[i] == DQUOTE || tech[i] == SQUOTE ||
			tech[i] == CPAREN || tech[i] == OBRACKET || tech[i] == CBRACKET ||
			tech[i] == CBRACE || tech[i] == TILDA || tech[i] == GTHAN ||
			tech[i] == LTHAN || tech[i] == AST || tech[i] == EQUAL ||
			tech[i] == ENTER || tech[i] == COLON)
		return (-1);
	if (compl[i] == '#' || compl[i] == '%' || compl[i] == ',' ||
			compl[i] == '@' || compl[i] == '!' || compl[i] == '^' ||
			compl[i] == '?' || compl[i] == '-' || compl[i] == '+' ||
			compl[i] == '`')
		return (-1);
	i = route_to_pools(tech, i, pool);
	return (i);
}

int					check_quoting_of_syntax(char *tech, int now)
{
	int				j;
	
	j = now;
	while (j > 0 && (tech[j] == SPACE || tech[j] == ENTER))
		j--;
	if (j > 0 && tech[j - 1] == BSLASH)
		return (-1);
	return (0);
}

int					pass_symbols_compl(char *compl, char *tech, int i, int *pool)
{
	while (i > 0 && (tech[i] == WORD_P && ft_isalnum(compl[i])))
		i--;
	if (tech[i] == WORD_P && ft_isalnum(compl[i]))
	{
		*pool = (g_prompt.prompt_func == main_prompt) ? 1 : 3;
		return (i);
	}
	if (tech[i] == WORD_P && (compl[i] == '/' ||
			compl[i] == '_' || compl[i] == '.'))
		return (check_path_pool_three_compl(compl, tech, pool, i));
	if ((tech[i] == SPACE || tech[i] == ENTER) && i == 0)
	{
		*pool = (g_prompt.prompt_func == main_prompt) ? 1 : 3;
		return (i + 1);
	}
	return (i);
}

int					check_path_pool_three_compl(char *compl, char *tech,
						int *pool, int i)
{
	int				start;
	
	while (i >= 0 && tech[i] == WORD_P && (ft_isalnum(compl[i]) ||
			compl[i] == '/' || compl[i] == '_' || compl[i] == '.'))
		i--;
	start = i + 1;
	while (i >= 0 && (tech[i] == SPACE || tech[i] == ENTER))
		i--;
	if (i < 0 && start >= 0 && (compl[start] == '_' ||
			(compl[start] == '.' && ft_isalnum(compl[start + 1]))))
	{
		*pool = 1;
		return (start);
	}
	if (i >= 0 && tech[i] == BSLASH && i + 2 == start)
		return (-1);
	*pool = 3;
	return (start);
}

int					route_to_pools(char *tech, int i, int *pool)
{
	int				save_i;

	save_i = i;
	if (tech[i] == DOLLAR || (tech[i] == OBRACE && i > 0 &&
		tech[i - 1] == DOLLAR))
	{
		*pool = 2;
		return (i + 1);
	}
	while (i > 0 && (tech[i] == SPACE || tech[i] == ENTER))
		i--;
	if (tech[i] == OBRACE || tech[i] == OPAREN || tech[i] == SCOLON ||
			tech[i] == AND || tech[i] == PIPE)
	{
		*pool = 1;
		return ((i == save_i) ? i + 1 : save_i + 1);
	}
	if (tech[i] != ENTER)
	{
		*pool = 3;
		return (save_i + 1);
	}
	return (save_i);
}
