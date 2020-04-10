
#ifndef READLINE_SIMPLE_H
# define READLINE_SIMPLE_H

# define SESC_NUM 5

/*
** File readline_simple.c
*/

char				*readline_simple(void);
int					sreadline_choice(char sy);
int					sescape_init(void);
int					bell_sound(void);

/*
** File str_edit_simple.c
*/

int					schar_add(char c);
int					sstr_add_symbol(char add);
int					sstr_del_symbol(void);
int					sstr_edit(char *swap, char add);

/*
** File escape_simple.c
*/

int					sescape_check(char **seq_base);
int					ssequence_process(int sequence_num);
int					sesc_left(void);
int					sesc_right(void);
int					sesc_r(void);

/*
** File key_simple.c
*/

int					sbackspace_proc(void);
int					make_sctrl_u(void);
int					make_sctrl_k(void);
int					make_sctrl_e(void);
int					make_sctrl_a(void);

#endif
