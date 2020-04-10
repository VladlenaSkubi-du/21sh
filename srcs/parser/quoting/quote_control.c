#include "shell21.h"
#include "parser.h"

/*
** Dquote removed
** if (*ptr == 1 || *ptr == 3 || *ptr == 4 || *ptr == 9 || *ptr == 10
** || *ptr == 14 || *ptr == 15 || *ptr == 16 || *ptr == 17 || *ptr == 18)
*/

static char	*g_sign[22] = {
	"\0", " ", "\\", ";", "&", "\"", "\'", "(", ")", "[", "]",
	"{", "}", "$", "~", "|", ">", "<", "*", "=", "\n", "#"};

/*
** Function needs to nullify symbols in comments and check if is EOF at end
*/

int		nullify_comment(char **ptr, t_stack **stack)
{
	if ((**ptr == COMENT && (*stack)->data != SQUOTE && \
		(*stack)->data != OBRACE &&
		(*stack)->data != DQUOTE) || ((*stack)->data == COMENT && \
		**ptr != ENTER))
	{
		**ptr = SPACE;
		if ((*stack)->data != COMENT)
			ft_push_stack(stack, COMENT);
	}
	if ((*stack)->data == COMENT && **ptr == ENTER)
		ft_pop_stack(stack);
	if (**ptr == EOF)
		ft_push_stack(stack, EOF);
	return (0);
}

int		nullify_backslash(char **ptr, t_stack **stack,\
		size_t *count, size_t size)
{
	if (((*stack)->data == 0 || ((*stack)->data == DQUOTE && \
		(ptr[0][1] == DOLLAR || ptr[0][1] == SQUOTE ||
		ptr[0][1] == DQUOTE || ptr[0][1] == BSLASH)))
		&& **ptr == BSLASH && ptr[0][1] != ENTER)
	{
		ptr[0][1] = TEXT;
		(*ptr)++;
	}
	else if (**ptr == BSLASH && ptr[0][1] != ENTER && (*stack)->data == DQUOTE)
		**ptr = TEXT;
	if ((*stack)->data == 0 \
		&& **ptr == BSLASH && ptr[0][1] == ENTER &&\
		(size - *count) == 2)
		ft_push_stack(stack, BSLASH);
	return (0);
}

/*
** Function to null symbols in techline between " ", or ' '
** also it send line to check brackets ( ) or { }
*/

int		nullify_dquotes(char **ptr, t_stack **stack)
{
	if ((*stack)->data == DOLLAR && **ptr != WORD_P && **ptr != DOLLAR)
		ft_pop_stack(stack);
	if ((*stack)->data == DQUOTE && **ptr == DQUOTE)
		ft_pop_stack(stack);
	else if ((*stack)->data == SQUOTE && **ptr == SQUOTE)
		ft_pop_stack(stack);
	else if ((*stack)->data == SQUOTE && **ptr != EOF)
		**ptr = TEXT;
	else if ((*stack)->data == DQUOTE && \
			(**ptr != DOLLAR && **ptr != EOF &&
			**ptr != BSLASH && **ptr != ENTER &&\
			!((**ptr == OPAREN || **ptr == OBRACE) && \
			*(*ptr - 1) == DOLLAR)) && **ptr != SPACE)
		**ptr = TEXT;
	else if ((*stack)->data != SQUOTE && **ptr == OPAREN)
		ft_push_stack(stack, OPAREN);
	else if ((*stack)->data == OPAREN && **ptr == CPAREN)
		ft_pop_stack(stack);
	else if ((*stack)->data != SQUOTE && **ptr == OBRACE)
		ft_push_stack(stack, OBRACE);
	else if ((*stack)->data == OBRACE && **ptr == CBRACE)
		ft_pop_stack(stack);
	else if ((*stack)->data == OBRACE || (*stack)->data == OPAREN)
		**ptr = TEXT;
	return (0);
}

int		nullify_promt_check(t_stack **stack)
{
	if ((*stack)->data != 0)
	{
		if ((*stack)->data == DOLLAR)
			ft_pop_stack(stack);
		if ((*stack)->data == DQUOTE || (*stack)->data == SQUOTE)
			g_prompt.prompt_func = dquote_prompt;
		if ((*stack)->data == OPAREN)
			g_prompt.prompt_func = other_prompt;
		if ((*stack)->data == OBRACE)
			g_prompt.prompt_func = other_prompt;
		if ((*stack)->data == BSLASH)
			g_prompt.prompt_func = other_prompt;
		if ((*stack)->data == EOF && g_prompt.prompt_func != heredoc_prompt)
		{
			g_prompt.prompt_func = main_prompt;
			error_handler(SYNTAX_ERROR | (ERR_SQUOTE << 9),
				g_sign[(*stack)->next->data]);
		}
		return (OUT);
	}
	else
		g_prompt.prompt_func = main_prompt;
	ft_clear_stack(stack);
	return (0);
}

/*
** Function to check quotes " ", ' ' and send to null
** symbols between them in techline
** also it send line to check brackets ( ) or { }
** If it needs, doing return to Readline module to close
** brackets or quotes
*/

int		nullify(char **techline, size_t cmd_size)
{
	char	*ptr;
	size_t	count;
	t_stack	*stack;

	count = -1;
	ptr = *techline;
	stack = ft_init_stack();
	while (++count <= cmd_size)
	{
		if (*ptr == DOLLAR && (stack->data == DQUOTE || stack->data == 0))
			ft_push_stack(&stack, *ptr);
		if (!(stack->data))
		{
			if (*ptr == DQUOTE || *ptr == SQUOTE)
				ft_push_stack(&stack, *ptr);
		}
		else
			nullify_dquotes(&ptr, &stack);
		nullify_backslash(&ptr, &stack, &count, cmd_size);
		nullify_comment(&ptr, &stack);
		ptr++;
	}
		// printf("g_cmd nul=%s\n", g_cmd);//печать для проверки
		// printf("techline cur:");
		// count = -1;
		// while (++count <= g_techline.len)
		// 	printf("%3d", g_techline.line[count]);
		// printf("\n");
	return (nullify_promt_check(&stack));
}
