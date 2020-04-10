#include "shell21.h"
#include "readline.h"

/*
** @pos_x_com is pos_x for comment
** Here we print the question about the columns to print
*/

int					ask_output(int total, int buf_lines,
						int pos_back, int len_x)
{
	char			c;
	int				len;
	int				total_len;
	char			*question;
	int				pos_x_com;

	pos_x_com = 0;
	count_comment_len(&total_len, total);
	len = 20 + 16 + 18 + total_len;
	count_comment_len(&total_len, buf_lines);
	len += total_len;
	front_insert_by_letters("21sh: display all ", &pos_x_com);
	question = ft_itoa(total);
	front_insert_by_letters(question, &pos_x_com);
	free(question);
	front_insert_by_letters(" possibilities (", &pos_x_com);
	question = ft_itoa(buf_lines);
	front_insert_by_letters(question, &pos_x_com);
	free(question);
	front_insert_by_letters(" lines)? [y or n] ", &pos_x_com);
	read(STDOUT_FILENO, &c, 1);
	if (c == 'y' || c == 'Y')
		return (clean_output_question(1, pos_back, len, len_x));
	clean_output_question(0, pos_back, len, len_x);
	return (1);
}

/*
** After printing some kind of big menu (the number of lines is bigger
** than the space left in the terminal) the behavior is as in bash -
** printing new prompt and the line without any changes
*/

int					after_big_menu(int pos_back, int len_x, int len_y)
{
	tputs(g_cap.sf, 1, printc);
	position_cursor("ch", 0, 0);
	g_prompt.prompt_func();
	g_rline.pos = pos_back;
	g_rline.pos_x = len_x;
	g_rline.pos_y = len_y;
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	g_rline.pos = 0;
	g_rline.pos_x = g_rline.prompt_len;
	if (g_rline.prompt_len >= g_screen.ws_col)
		g_rline.pos_x = g_rline.prompt_len % g_screen.ws_col;
	g_rline.pos_y = 0;
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	g_rline.flag &= ~TAB;
	return (0);
}

/*
** Here we count how long are the values of @total and @buf_len
** to get the full length of the question string and be able
** to clean it after
*/

int					count_comment_len(int *find, int num)
{
	int				number;

	*find = (num == 0) ? 1 : 0;
	number = num;
	while (number != 0)
	{
		(*find)++;
		number /= 10;
	}
	return (0);
}

/*
** If the answer is yes and all the options do not fit in the
** terminal screen, we clear
** the question and after, print all the options, a new prompt and
** the cmd-line if it was filled (return 0 to print_menu and do there)
** If the answer is other than y or Y, we just clear the question
** and return back to the state as the cmd-line had before TAB was
** pushed
*/

int					clean_output_question(int from, int pos_back,
						int len, int len_x)
{
	int				lines_nb;

	lines_nb = len / g_screen.ws_col + ((from == 0) ? 1 : 0);
	if ((len + 1) % g_screen.ws_col == 0)
		lines_nb += 1;
	if (lines_nb > 1)
		position_cursor("UP", 0, lines_nb - 1);
	position_cursor("ch", 0, 0);
	tputs(g_cap.cd, 1, printc);
	if (from == 0)
	{
		position_cursor("ch", 0, len_x);
		tputs(g_cap.up, 1, printc);
		move_cursor_from_old_position(pos_back, 'l');
		return (0);
	}
	return (0);
}

/*
** If there are no options for completion, we clear the 
** allocated @g_complete and @g_techline strings and ring
** the bell
*/

int					clean_strings_compl(char *compl,
						char *tech_line, int flag)
{
	free(compl);
	free(tech_line);
	if (flag == 1)
		return (incorrect_sequence());
	return (0);
}
