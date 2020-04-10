#include "shell21.h"
#include "readline.h"

int				main_prompt(void)
{
	const char	*prompt = "21sh";

	ft_putstr_fd("\033[1;31m", STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	ft_putstr_fd("> ", STDOUT_FILENO);
	return (0);
}

int				dquote_prompt(void)
{
	ft_putstr_fd("dquote> ", STDOUT_FILENO);
	return (0);
}

int				heredoc_prompt(void)
{
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	return (0);
}

int				other_prompt(void)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
	return (0);
}

int				prompt_len(void)
{
	int			len;
	
	len = 0;
	if (g_prompt.prompt_func == main_prompt)
		len = ft_strlen("21sh> ");
	else if (g_prompt.prompt_func == dquote_prompt)
		len = ft_strlen("dquote> ");
	else if (g_prompt.prompt_func == heredoc_prompt)
		len = ft_strlen("heredoc> ");
	else if (g_prompt.prompt_func == other_prompt)
		len = ft_strlen("> ");
	return (len);
}