#include "shell21.h"
#include "readline.h"

char				*get_techline_compl(char *complete, int len)
{
	char			*tech_line;
	int				i;

	if (!complete || complete[0] == 0)
		return (NULL);
	tech_line = (char*)ft_xmalloc(len);
	i = 0;
	while (g_rline.cmd[i] && i < len)
	{
		tech_line[i] = get_tech_num(g_rline.cmd[i]);
		i++;
	}
	return (tech_line);
}

int					analyse_techline_compl(char *compl, char *tech,
						int len, int *pool)
{
	int				i;

	if (!(g_rline.cmd[g_rline.pos] == 0 || g_rline.cmd[g_rline.pos] == ' '))
		return (0);
	i = len - 1;
	i = pass_symbols(compl, tech, i, pool);
	if (*pool == 1 || *pool == 3)
		return (i);
	if (tech[i] == BSLASH || tech[i] == DQUOTE || tech[i] == SQUOTE ||
		tech[i] == CPAREN || tech[i] == OBRACKET || tech[i] == CBRACKET ||
		tech[i] == CBRACE || tech[i] == TILDA || tech[i] == GTHAN ||
		tech[i] == LTHAN || tech[i] == AST || tech[i] == EQUAL ||
		tech[i] == ENTER)
		return (-1);
	if (compl[i] == ':' || compl[i] == '#' || compl[i] == '%' ||
		compl[i] == '@' || compl[i] == '!' || compl[i] == '^' ||
		compl[i] == '?' || compl[i] == '-' || compl[i] == '+' ||
		compl[i] == ',')
		return (-1);
	if (compl[i] == '/' || compl[i] == '.' || compl[i] == '_')
		return (route_to_arguments(compl, i, pool));
	i = route_to_pools(tech, i, pool);
	return (i);
}

int					pass_symbols(char *compl, char *tech, int i, int *pool)
{
	while (i > 0 && (tech[i] == WORD_P && ft_isalnum(compl[i])))
		i--;
	if (tech[i] == WORD_P && ft_isalnum(compl[i]))
	{
		*pool = (g_prompt.prompt_func == main_prompt) ? 1 : 3;
		return (i);
	}
	if (tech[i] == WORD_P && compl[i] == '/')
	{
		*pool = 3;
		return (i);
	}
	if (tech[i] == SPACE && i == 0)
	{
		*pool = (g_prompt.prompt_func == main_prompt) ? 1 : 3;
		return (i + 1);
	}
	return (i);
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
	while (i > 0 && tech[i] == SPACE)
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

int					route_to_arguments(char *compl, int i, int *pool)
{
	if (compl[i] == '.')
		return (i);
	*pool = 3;
	while (i > 0 && (ft_isalnum(compl[i]) ||
			compl[i] == '/' || compl[i] == '_'))
		i--;
	if (i > 0 && compl[i] == ' ' && compl[i - 1] != '\\')
		return (i + 1);
	return (-1);
}
