#include "shell21.h"
#include "parser.h"

int			start_quotes(char *techline)
{
	t_stack		*stack;
	int			i;

	stack = ft_init_stack();
	i = -1;
	while (techline[++i] != END_T)
	{
		if (g_prompt.prompt_func != heredoc_prompt && techline[i] == EOF)
			ft_push_stack(&stack, EOF);
		if (!(stack->data))
		{
			if (techline[i] == DQUOTE || techline[i] == SQUOTE)
				ft_push_stack(&stack, techline[i]);
		}
		else
			quotes_make_text_inside(&stack, i, techline);
	}
	return (quotes_define_prompts(&stack));
}

int		quotes_define_prompts(t_stack **stack)
{
	if ((*stack)->data != 0)
	{
		if ((*stack)->data == DQUOTE || (*stack)->data == SQUOTE)
			g_prompt.prompt_func = dquote_prompt;
		if ((*stack)->data == EOF && g_prompt.prompt_func != heredoc_prompt)
		{
			g_prompt.prompt_func = main_prompt;
			error_handler (SYNTAX_ERROR | (ERR_QUOTE << 9), NULL);
		}
		ft_clear_stack(stack);
		return (OUT);
	}
	g_prompt.prompt_func = main_prompt;
	ft_clear_stack(stack);
	return (0);
}

int		quotes_make_text_inside(t_stack **stack, int i, char *techline)
{
	t_stack			*st_tmp;
	
	st_tmp = *stack;
	if ((st_tmp->data == DQUOTE && techline[i] == DQUOTE) ||
			(st_tmp->data == SQUOTE && techline[i] == SQUOTE))
		ft_pop_stack(stack);
	else if ((st_tmp->data == SQUOTE || st_tmp->data == DQUOTE) &&
			techline[i] != EOF)
		techline[i] = TEXT;
	return (0);
}
