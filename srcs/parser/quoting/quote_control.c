#include "shell21.h"
#include "parser.h"

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
	stack = ft_init_stack(); //описание символа, в стеке, на каждый символ свой стек - если за символом может идти что-то еще значимое
	while (++count <= cmd_size)
	{
		if (!(stack->data))
		{
			if (*ptr == DQUOTE || *ptr == SQUOTE)
				ft_push_stack(&stack, *ptr);
		}
		else
			nullify_dquotes(&ptr, &stack);
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

int		nullify_promt_check(t_stack **stack)
{
	if ((*stack)->data != 0)
	{
		if ((*stack)->data == DQUOTE || (*stack)->data == SQUOTE)
			g_prompt.prompt_func = dquote_prompt;
		
		if ((*stack)->data == EOF && g_prompt.prompt_func != heredoc_prompt)
		{
			g_prompt.prompt_func = main_prompt;
			error_handler(SYNTAX_ERROR | (ERR_SQUOTE << 9), NULL); //исправить обработку ошибки
		}
		ft_clear_stack(stack);
		return (OUT);
	}
	else
		g_prompt.prompt_func = main_prompt;
	ft_clear_stack(stack);
	return (0);
}

/*
** Function to null symbols in techline between " ", or ' '
** also it send line to check brackets ( ) or { }
*/

int		nullify_dquotes(char **ptr, t_stack **stack)
{
	if ((*stack)->data == DQUOTE && **ptr == DQUOTE)
		ft_pop_stack(stack);
	else if ((*stack)->data == SQUOTE && **ptr == SQUOTE) //проверка валидного закрытия одинарных
		ft_pop_stack(stack);
	else if (((*stack)->data == SQUOTE || (*stack)->data == DQUOTE) &&
		**ptr != EOF)
		**ptr = TEXT;
	return (0);
}