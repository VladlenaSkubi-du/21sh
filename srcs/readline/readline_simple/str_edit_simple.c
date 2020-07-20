#include "shell21.h"
#include "readline.h"

int				schar_add(char c)
{
	if (g_rline.cmd_len + g_prompt.prompt_len >= g_screen.ws_col - 1)
		return (bell_sound());
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
		realloc_readline_cmd();
	g_rline.cmd_len++;
	if (g_rline.cmd_len + 1 < 0 || g_rline.cmd_buff_len + 1 < 0)
		return (OUT);
	sstr_add_symbol(c);
	return (0);
}

int				sstr_add_symbol(char add)
{
		char			*swap;

	swap = NULL;
	if (g_rline.pos < g_rline.cmd_len - 1)
		swap = ft_strdup(g_rline.cmd + g_rline.pos);
	g_rline.cmd[g_rline.pos] = add;
	sstr_edit(swap, add);
	g_rline.pos++;
	free(swap);
	return (0);
}

int				sstr_del_symbol(void)
{
	char			*swap;

	swap = ft_strdup(g_rline.cmd + g_rline.pos + 1);
	sstr_edit(swap, -1);
	free(swap);
	return (0);
}

int				sstr_edit(char *swap, char add)
{
	int				i;
	int				len;

	i = -1;
	len = ft_strlen(swap);
	if (add > 0)
	{
		if (swap)
			while (swap[++i])
				g_rline.cmd[g_rline.pos + 1 + i] = swap[i];
		write(STDOUT_FILENO, &add, 1);
		if (len > 0)
			sstr_insert(swap, len, add);
	}
	else
	{
		if (swap)
			while (swap[++i])
				g_rline.cmd[g_rline.pos + i] = swap[i];
		g_rline.cmd[g_rline.pos + i] = '\0';
		if (len > 0)
			sstr_insert(swap, len, add);
	}
	return (0);
}

int				sstr_insert(char *swap, int len, int add)
{
	if (swap)
		write(STDOUT_FILENO, swap, len);
	if (add < 0)
	{
		write(STDOUT_FILENO, " ", 1);
		while (len-- >= 0)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	else
		while (len--)
			write(STDOUT_FILENO, "\033[D", 3);
	return (0);
}
