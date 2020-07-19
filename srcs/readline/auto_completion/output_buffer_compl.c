#include "shell21.h"
#include "readline.h"
#define OUT_BUF 10

t_compl_output			menu_buf_init(int total, int max_len)
{
	t_compl_output		menu_buf;

	menu_buf.buffer = NULL;
	menu_buf.buf_lines = 0;
	menu_buf.buf_width = 0;
	(max_len == 8) ? (max_len)++ : 0;
	while (max_len % 8 != 0)
		max_len++;
	menu_buf.word_len = max_len + 1;
	menu_buf.word_nb = total;
	menu_buf.i = 0;
	buffer_col_calc(&menu_buf);
	return (menu_buf);
}

void					buffer_col_calc(t_compl_output *menu_buf)
{
	int					i;

	menu_buf->buf_width = (g_screen.ws_col / menu_buf->word_len) *
		menu_buf->word_len + 1;
	if (menu_buf->buf_width == 1)
		menu_buf->buf_width = g_screen.ws_col;
	menu_buf->buf_lines = g_screen.ws_col / menu_buf->word_len;
	if (menu_buf->buf_lines != 0)
	{
		menu_buf->buf_lines = menu_buf->word_nb / menu_buf->buf_lines
		+ (menu_buf->word_nb % menu_buf->buf_lines ? 1 : 0);
	}
	else
		menu_buf->buf_lines = menu_buf->word_nb;
	menu_buf->buffer = (char**)ft_xmalloc(sizeof(char*) *
		(menu_buf->buf_lines + 1));
	menu_buf->buffer[menu_buf->buf_lines] = 0;
	i = 0;
	while (i < menu_buf->buf_lines)
	{
		menu_buf->buffer[i] = (char*)ft_xmalloc(menu_buf->buf_width + 2);
		i++;
	}
}

int						buffer_col_print(char *add,
							t_compl_output *menu_buf)
{
	int					len;

	len = ft_strlen(add);
	if (!menu_buf->buffer)
		buffer_col_calc(menu_buf);
	ft_memcpy(menu_buf->buffer[menu_buf->i % menu_buf->buf_lines]
		+ (menu_buf->i / menu_buf->buf_lines * menu_buf->word_len),
			add, len);
	ft_memset(menu_buf->buffer[menu_buf->i % menu_buf->buf_lines]
		+ (menu_buf->i / menu_buf->buf_lines * menu_buf->word_len) + len,
		' ', menu_buf->word_len - len);
	if (menu_buf->i++ == menu_buf->word_nb - 1)
		buffer_col_finish(menu_buf);
	return (0);
}


void					buffer_col_finish(t_compl_output *menu_buf)
{
	int					i;

	i = 0;
	while (i < menu_buf->buf_lines - 1)
	{
		buf_add(menu_buf->buffer[i], menu_buf->buf_width);
		buf_add("\n", 1);
		i++;
	}
	buf_add(menu_buf->buffer[i], menu_buf->buf_width);
}

void					buf_add(char *str, int size)
{
	static char			buf[OUT_BUF];
	static char			*ptr = buf;

	if (!str && !size)
	{
		write(STDOUT_FILENO, buf, ptr - buf);
		ptr = buf;
	}
	else if (size + (ptr - buf) < OUT_BUF)
	{
		ft_memcpy(ptr, str, size);
		ptr += size;
	}
	else
	{
		write(STDOUT_FILENO, buf, ptr - buf);
		write(STDOUT_FILENO, str, size);
		ptr = buf;
	}
}
