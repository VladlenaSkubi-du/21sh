/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:03:40 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 20:03:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "readline.h"

int				make_sctrl_e(void)
{
	while (g_rline.pos < g_rline.cmd_len - 1 &&
			g_rline.pos + g_rline.prompt_len < g_screen.ws_col - 2)
		sesc_right();
	return (0);
}

int				make_sctrl_a(void)
{
	while (g_rline.pos)
		sesc_left();
	return (0);
}

int				sbackspace_proc(void)
{
	if (g_rline.pos == 0)
		return (bell_sound());
	g_rline.pos--;
	write(STDOUT_FILENO, "\033[D \033[D", 7);
	sstr_del_symbol();
	return (0);
}

int				make_sexit(void)
{
	t_exec		*exec;

	if (g_rline.pos == 0 && g_rline.cmd_len == 0)
	{
		if (g_prompt.prompt_func != main_prompt)
		{
			if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
				realloc_readline_cmd();
			g_rline.cmd = ft_straddsy(g_rline.cmd, EOF);
			return (OUT);
		}
		exec = (t_exec*)ft_xmalloc(sizeof(t_exec));
		exec->argv = (char**)ft_xmalloc(3 * sizeof(char*));
		exec->argv[0] = ft_strdup("exit");
		exec->argv[1] = ft_strdup("0");
		reset_canonical_input();
		clean_readline();
		btin_exit(exec);
	}
	else
		return (incorrect_sequence());
	return (0);
}
