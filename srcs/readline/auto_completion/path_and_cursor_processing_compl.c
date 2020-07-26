#include "shell21.h"
#include "readline.h"

int					init_completion(void)
{
	g_compl.to_compl = (g_rline.pos >= g_rline.cmd_len) ?
		ft_strdup(g_rline.cmd) :
		ft_strndup(g_rline.cmd, g_rline.pos);
	g_compl.len_tocompl = ft_strlen(g_compl.to_compl);
	g_compl.menu = NULL;
	g_compl.total = 0;
	g_compl.tablevel = 0;
	g_compl.to_del = 0;
	g_compl.menu_buffer.buffer = NULL;
	return (0);
}

/*
** If there are no options for completion, we clear the
** allocated @g_complete and @g_techline strings and ring
** the bell
*/

int					clear_completion(int flag)
{
	free(g_compl.to_compl);
	g_compl.to_compl = NULL;
	g_compl.len_tocompl = 0;
	if (g_compl.menu != NULL)
	{
		ft_arrdel(g_compl.menu);
		g_compl.menu = NULL;
	}
	g_compl.total = 0;
	g_compl.tablevel = 0;
	g_compl.to_del = 0;
	if (g_compl.menu_buffer.buffer != NULL)
	{
		ft_arrdel(g_compl.menu_buffer.buffer);
		g_compl.menu_buffer.buffer = NULL;
	}
	return ((flag == 1) ? incorrect_sequence() : 0);
}

int					make_one_slash(char **final,
						int last_slash, char *compl)
{
	int				check;
	int				i;

	check = last_slash;
	i = check;
	while (i >= 0)
	{
		if (compl[i] == '/')
		{
			i = check;
			while (i >= 0 && compl[i] == '/')
				i--;
			if (i < check)
				ft_strshift((*final) + check, i - check + 1);
		}
		i--;
		check = i;
	}
	return (0);
}

/*
** Sending the PATH value to be parsed for the tree
*/

// char				*path_parse_compl(void) //VARIABLES DELETE
// {
// 	int				i;

// 	i = 0;
// 	while (g_env[i])
// 	{
// 		if (ft_strncmp(g_env[i], "PATH=", 5) == 0)
// 			return (g_env[i] + 5);
// 		i++;
// 	}
// 	return (NULL);
// }
