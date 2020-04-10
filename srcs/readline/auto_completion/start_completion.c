#include "shell21.h"
#include "readline.h"

/*
** @g_tablevel is a counter according to that we complete this or that line
** from the g_menu
** @g_complete - is a string, according to which we search
** @g_len_compl is the length of @g_complete
** options for completion. Can be empty if TAB is pushed before any other key
** @g_delete is the number of inserted symbols that should be delete after
** user pushes TAB for insertion of the other option
** @g_menu - the full menu for completion, all the possible options
** @g_total is the number of options (words to auto-complete possible)
*/

int					g_tablevel;
char				*g_complete;
int					g_len_compl;
int					g_delete;
char				**g_menu;
int					g_total;

/*
** @pool = pool of variables: binary-files (1), variables (2),
** arguments (3), bell (nothing can be done - 0);
** @total = total number of options
** @max_len = maximal length of the option-string within the whole
** menu array - is needed for the buffer output part
** @tech_line = is needed for analysis of the g_complete string -
** parsing of the g_complete string
** @delete = by each TAB a word-option is added to the
** g_complete part. If this option does not taken by the user and
** the user pushes TAB to change the option - the old option should
** be deleted - as many symbols as in @delete variable
** If there are no options to be auto-completed, there is a bell.
*/

int					auto_completion(void)
{
	int				pos_back;
	int				max_len;
	char			*tech_line;

	pos_back = g_rline.pos;
	if (g_rline.flag & TAB)
	{
		g_tablevel++;
		return (insert_word_compl());
	}
	g_total = 0;
	max_len = 0;
	g_complete = ft_strndup(g_rline.cmd, pos_back);
	tech_line = get_techline_compl(g_complete, g_rline.pos);
	g_menu = route_menu_receipt(tech_line, pos_back, &g_total, &max_len);
	if (g_menu == NULL || g_menu[0] == 0)
		return (clean_strings_compl(g_complete, tech_line, 1));
	if (print_menu(pos_back, g_menu, g_total, max_len))
		return (clean_strings_compl(g_complete, tech_line, 0));
	g_tablevel = 0;
	g_delete = 0;
	g_len_compl = ft_strlen(g_complete);
	free(tech_line);
	return (0);
}

/*
** Not in the main prompt pushing TAB in the first-pool position
** will auto-complete directory arguments because other prompts
** usually mean that we already have a program in the cmd-line
*/

char				**route_by_prompts(int *total, int *max_len)
{
	char			**menu;
	t_path			*root;

	if (g_prompt.prompt_func == main_prompt)
		menu = start_search_in_path("", path_parse_compl(),
			total, max_len);
	else
	{
		root = fill_tree_with_arguments("./", "", total);
		if (root == NULL)
			return (NULL);
		menu = form_result_array(&root, *total, max_len);
		free_path_tree(&root);
	}
	return (menu);
}

/*
** If the @g_complete line is empty and @pool is 1, menu consists of all
** the binary-options found in the environmental variable PATH and
** in the internal list of builtin programs.
** If @g_complete is not empty and @pool is 1 - the function
** start_search_in_path returns only those options that match.
** The same principle for other pools.
*/

char				**route_menu_receipt(char *tech_line,
						int tech_len, int *total, int *max_len)
{
	char			**menu;
	int				pool;
	int				tmp;
	char			*final;

	menu = NULL;
	pool = 0;
	if (tech_line == NULL)
		menu = route_by_prompts(total, max_len);
	else
	{
		if ((tmp = analyse_techline_compl(g_complete, tech_line,
			tech_len, &pool)) == -1)
			return (NULL);
		final = ft_strdup(g_complete + tmp);
		free(g_complete);
		g_complete = final;
		if (pool == 1)
			menu = start_search_in_path(g_complete, path_parse_compl(),
				total, max_len);
		else if (pool == 2)
			menu = get_variables(g_complete, total, max_len);
		else
			menu = get_arguments(&g_complete, total, max_len);
	}
	return (menu);
}

/*
** Here we insert an option to the cmd-line
** Example: we have "ca[] abcd" where cursor stays on the []
** And the first option to be inserted is the "caffeinate"
** @g_complete is "ca"
** @g_compl_len is 2
** @len_option is 10
** @counter is the position of the word in the menu-buffer, if
** caffeinate is the first word in the list like:
** "caffeinate cal calendar caller cancel cap_mkdb captoinfo case cat"
** @counter will be 1
** @flag is for pool 2: {$PARAMETER}
*/

int					insert_word_compl(void)
{
	int				len_option;
	int				counter;
	int				flag;
	int				i;

	flag = 0;
	(g_delete > 0) ? delete_till_compl(g_delete) : 0;
	if (g_tablevel > 0 && g_total > 0)
	{
		if (g_rline.pos > 1 && g_rline.cmd[g_rline.pos - 1] == '{' &&
			g_rline.cmd[g_rline.pos - 2] == '$')
			flag = 1;
		counter = (g_tablevel - 1 < g_total) ? g_tablevel - 1 :
			(g_tablevel - 1) % g_total;
		len_option = ((flag == 1) ? ft_strlen(g_menu[counter]) + 1 :
			ft_strlen(g_menu[counter]));
		g_delete = len_option - g_len_compl;
		i = -1;
		while (++i < g_delete - flag)
			char_add(g_menu[counter][g_len_compl + i], NULL);
		(flag > 0) ? char_add('}', NULL) : 0;
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
		print_menu_buf_after_insert(g_rline.pos);
	}
	return (0);
}

/*
** After any key except of TAB is pushed, the menu under the line
** is cleared
** Stays in all the key_action functions
*/

int					check_menu(void)
{
	if (g_rline.flag & TAB)
	{
		clean_menu();
		free(g_complete);
		ft_arrdel(g_menu);
		g_rline.flag &= ~TAB;
		g_tablevel = 0;
	}
	return (0);
}
