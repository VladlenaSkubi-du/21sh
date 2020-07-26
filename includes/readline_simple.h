/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_simple.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:24:08 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:24:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_SIMPLE_H
# define READLINE_SIMPLE_H

# define SESC_NUM   5

/*
** File readline_simple.c
*/

int					readline_simple(void);
int					sreadline_choice(char sy);
int					bell_sound(void);

/*
** File str_edit_simple.c
*/

int					schar_add(char c);
int					sstr_add_symbol(char add);
int					sstr_del_symbol(void);
int					sstr_edit(char *swap, char add);
int					sstr_insert(char *swap, int len, int add);

/*
** File escape_simple.c
*/

int					sescape_init(void);
int					sescape_check(char **seq_base);
int					ssequence_process(int sequence_num);
int					sesc_left(void);
int					sesc_right(void);

/*
** File key_simple.c
*/

int					sbackspace_proc(void);
int					make_sctrl_e(void);
int					make_sctrl_a(void);
int					make_sexit(void);

#endif
