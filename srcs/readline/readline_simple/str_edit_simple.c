#include "shell21.h"
#include "readline.h"

int				schar_add(char c)
{
	if (g_rline.cmd_len >= g_rline.cmd_buff_len - 1)
	{
		g_rline.cmd = (char *)ft_realloc(g_rline.cmd, g_rline.cmd_len,
			g_rline.cmd_buff_len,
			g_rline.cmd_buff_len + CMD_SIZE);
		g_rline.cmd_buff_len += CMD_SIZE;
	}
	g_rline.cmd_len++;
	sstr_add_symbol(c);
	return (0);
}

int				sstr_add_symbol(char add)
{
	char			*swap;

	swap = NULL;
	if (g_rline.cmd_len + g_rline.prompt_len == g_screen.ws_col - 1)
		return (bell_sound());
	swap = ft_strdup(g_rline.cmd + g_rline.pos);
	g_rline.cmd[g_rline.pos] = add;
	if (swap != NULL)
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
		while (swap[++i])
			g_rline.cmd[g_rline.pos + 1 + i] = swap[i];
		write(STDOUT_FILENO, &add, 1);
		write(STDOUT_FILENO, swap, len);
		while (len--)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	else
	{
		while (swap[++i])
			g_rline.cmd[g_rline.pos + i] = swap[i];
		g_rline.cmd[g_rline.pos + i] = '\0';
		write(STDOUT_FILENO, swap, len);
		write(STDOUT_FILENO, " ", 1);
		while (len-- >= 0)
			write(STDOUT_FILENO, "\033[D", 3);
	}
	return (0);
}
