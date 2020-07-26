/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:02:57 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:02:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "readline.h"

/*
** Comes to the function after pushing "DELETE" key and
** ctrl + H
** Deletes the previous symbol in the line
*/

int					backspace_process(void)
{
	char			*swap;
	int				len_swap;
	char			*save_yank;

	check_after_line();
	if (g_rline.pos <= 0)
		return (incorrect_sequence());
	save_yank = ft_strndup(g_rline.cmd + g_rline.pos - 1, 1);
	make_ctrl_p(0, save_yank);
	swap = g_rline.cmd + g_rline.pos;
	len_swap = ft_strlen(swap);
	if (g_rline.cmd[g_rline.pos - 1] == '\n')
		return (backspace_newline(swap, len_swap));
	ft_strcpy(g_rline.cmd + g_rline.pos - 1, swap);
	ft_bzero(g_rline.cmd + g_rline.pos - 1 + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	g_rline.cmd_len--;
	key_left_proc();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x, &g_rline.pos_y, 1);
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

/*
** If we delete a \n, we need to know what we delete
** in the front part before we delete in the back to
** jump to the right part of the terminal screen
*/

int					backspace_newline(char *swap, int len_swap)
{
	int				pos_back;

	pos_back = g_rline.pos;
	key_left_proc();
	front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
		&g_rline.pos_y, 1);
	ft_strcpy(g_rline.cmd + pos_back - 1, swap);
	ft_bzero(g_rline.cmd + pos_back - 1 + len_swap,
		g_rline.cmd_buff_len - g_rline.cmd_len);
	g_rline.cmd_len--;
	tputs(g_cap.cd, 1, printc);
	front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	return (0);
}

/*
** Comes to these function after pushing ctrl + D
** That is a EOF identifier
*/

int					delete_process(void)
{
	t_exec			*exec;

	check_after_line();
	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
	{
		if (g_prompt.prompt_func == main_prompt)
		{
			exec = (t_exec*)ft_xmalloc(sizeof(t_exec));
			exec->argv = (char**)ft_xmalloc(3 * sizeof(char*));
			exec->argv[0] = ft_strdup("exit");
			exec->argv[1] = ft_strdup("0");
			reset_canonical_input();
			clean_readline();
			btin_exit(exec);
		}
		if (g_prompt.prompt_func != main_prompt)
		{
			g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
			return (OUT);
		}
	}
	else
		return (incorrect_sequence());
	return (0);
}

/*
** In auto-completion block we need to delete the word inserted
** in the front and back part till the part we started to insert
*/

int					delete_till_compl(int delete)
{
	char			*swap;
	int				len_swap;
	int				i;

	if (g_rline.pos > 0)
	{
		swap = g_rline.cmd + g_rline.pos;
		len_swap = ft_strlen(swap);
		ft_strcpy(g_rline.cmd + g_rline.pos - delete, swap);
		ft_bzero(g_rline.cmd + g_rline.pos - delete + len_swap,
			g_rline.cmd_buff_len - ft_strlen(g_rline.cmd));
		g_rline.cmd_len -= delete;
		i = -1;
		while (++i < delete)
			key_left_proc();
		front_set_cursor_jmp(&g_rline.pos, &g_rline.pos_x,
			&g_rline.pos_y, 1);
		tputs(g_cap.cd, 1, printc);
		front_insert_cmd_till_the_end(g_rline.pos_y + 1);
	}
	else
		return (incorrect_sequence());
	return (0);
}
