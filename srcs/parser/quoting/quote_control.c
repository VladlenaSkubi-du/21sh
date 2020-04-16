#include "shell21.h"
#include "parser.h"

int			start_quotes(void)
{
	t_stack		*stack;
	int			i;

	i = -1;
	stack = ft_init_stack();
	while (++i <= g_pline.len && g_pline.tech[i])
	{
		if (!(stack->data))
		{
			if (g_pline.tech[i] == DQUOTE || g_pline.tech[i] == SQUOTE)
				ft_push_stack(&stack, g_pline.tech[i]);
		}
		else
		{
			if ((stack->data == DQUOTE && g_pline.tech[i] == DQUOTE) ||
					(stack->data == SQUOTE && g_pline.tech[i] == SQUOTE))
				ft_pop_stack(&stack);
			else if ((stack->data == SQUOTE || stack->data == DQUOTE) &&
					g_pline.tech[i] != EOF)
				g_pline.tech[i] = TEXT;
		}
	}
		// printf("g_pline.cmd nul=%s\n", g_pline.cmd);//печать для проверки
		// printf("techline cur:");
		// count = -1;
		// while (++count <= g_techline.len)
		// 	printf("%3d", g_techline.line[count]);
		// printf("\n");
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
			error_handler (SYNTAX_ERROR | (ERR_SQUOTE << 9), NULL);
		}
		ft_clear_stack(stack);
		return (OUT);
	}
	g_prompt.prompt_func = main_prompt;
	ft_clear_stack(stack);
	return (0);
}
