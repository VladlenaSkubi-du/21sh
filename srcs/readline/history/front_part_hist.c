#include "shell21.h"
#include "readline.h"

int					make_ctrl_r_history(void)
{
	int				len;
	int				len_x;
	char			*find;
	int				pos_back;
	int				coincidence;

	pos_back = g_rline.pos;
	len_x = g_rline.pos_x;
	coincidence = 0;
	position_cursor_after_line(g_rline.cmd_len);
	len = 22;
	front_insert_by_letters("We search in history: ", &coincidence);
	find = get_the_answer_hist(&len);
	clean_output_question(0, pos_back, len, len_x);
	if (find == NULL || find[0] == '\0')
	{
		free(find);
		return (OUT);
	}
	coincidence = find_in_history(find);
	free(find);
	if (coincidence < 0)
		return (incorrect_sequence());
	print_new_cmd_from_history(coincidence);
	return (OUT);
}

/*int					make_ctrl_r_history(void)
{
	int				len;
	int				len_x;
	char			*find;
	int				pos_back;
	int				coincidence;

	pos_back = g_rline.pos;
	len_x = g_rline.pos_x;
	coincidence = 0;
	position_cursor_after_line(g_rline.cmd_len);
	len = 22;
	g_rline.flag |= AFTER_LINE_HIST;
	front_insert_by_letters("We search in history: ", &coincidence);
	find = get_the_answer_hist(&len);
	clean_output_question(0, pos_back, len, len_x);
	(find && find[0] == '\0') ? free(find) : 0;
	if (find == NULL || find[0] == '\0')
		return (OUT);
	coincidence = find_in_history(find);
	free(find);
	if (coincidence < 0)
		return (incorrect_sequence());
	print_new_cmd_from_history(coincidence);
	return (OUT);
}*/

char				*get_the_answer_hist(int *len)
{
	char			*find;
	int				len_find;
	char			c;

	find = (char*)ft_xmalloc(CMD_SIZE + 1);
	c = 0;
	while (read(STDOUT_FILENO, &c, 1) && c != '\n')
	{
		if (c == '\033')
			return (free_find_hist(&find));
		if ((c >= 0 && c < 2) || (c >= 4 && c < 32))
			continue;
		else if (insert_valid_sy_hist(c,
			len, &find, &len_find) == 1)
			return (find);
	}
	if (find[0] == 0)
		return (free_find_hist(&find));
	return (find);
}

char				*free_find_hist(char **find)
{
	free(*find);
	*find = NULL;
	return (NULL);
}

int					insert_valid_sy_hist(char c,
						int *len, char **find, int *len_find)
{
	if (ft_isprint(c) == 1)
	{
		if (*len >= g_screen.ws_col - 1)
			return (1);
		write(STDOUT_FILENO, &c, 1);
		*find = ft_straddsy(*find, c);
		*len_find = ft_strlen(*find);
		(*len)++;
		if (*len_find == CMD_SIZE - 1)
			return (1);
	}
	if (c == 127)
		backspace_one_sy(find, len_find, len);
	return (0);
}

int					backspace_one_sy(char **find, int *len_find,
						int *len)
{
	char			*tmp;

	tmp = *find;
	if (*len_find > 0)
	{
		tmp[*len_find - 1] = 0;
		(*len_find)--;
		(*len)--;
		write(STDOUT_FILENO, "\033[D \033[D", 7);
	}
	return (0);
}
