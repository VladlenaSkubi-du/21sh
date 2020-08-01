/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:24:48 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/01 18:10:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# include "exit_status.h"
# include "libft.h"
# include "parser.h"
# include "readline.h"
# include "./builtin/builtin.h"

/*
** MAXDIR according to POSIX:  _POSIX_PATH_MAX
*/

# define HISTORY_LIMIT		32767
# define MAX_HISTFILE		500
# define MAX_HISTBUF		500
# define MAXDIR				256
# define MAX_EXIT_STATUS	10
# define ENV_BUFFER			17
# define OUT				42

# define ENV_VIS			0x1
# define READONLY			0x2

/*
** Structures
** ____________________________________________________________________________
*/

/*
** @t_prompt is used in interactive shell as a bunch between
** readline and parser
**
** @prompt_func is function where prompt that is valid
** according to some readline and parser analysis is
** stated, output and length counted
** Prompts can be: main, dquote, heredoc and other
** @prompt_len_real is the length of prompt text that
** should be putput
** @prompt_len is length of prompt according to the terminal
** length
*/

typedef struct		s_prompt
{
	int				(*prompt_func)(void);
	int				prompt_len_real;
	int				prompt_len;
}					t_prompt;

/*
** @t_history - is a global working with history
** in the interactive shell session
**
** @hist is an array with commands (not separated by \n but
** separated as they came to parser)
** @len is the number of lines (commands) in the history
** @last is counter of the last command saved in the history
** @last_number is a number that is output near the command
** from the command list
*/

typedef struct		s_history
{
	char			**hist;
	int				len;
	int				counter;
	int				last;
	int				last_number;
}					t_history;

/*
** Is used in all the blocks for convenient work with
** command interpreter syntax
**
** @WORD_P is for letters, "/", "_" and other signs
** that is not analysed as syntax
** @SPACE is " "
** @BSLASH is "\"
** @SCOLON is ";"
** @AND is "&"
** @DQUOTE is '"',
** @SQUOTE is "'"
** @OPAREN is "("
** @CPAREN is ")"
** @OBRACKET is "["
** @CBRACKET is "]"
** @OBRACE is "{"
** CBRACE is "}"
** @DOLLAR is "$",
** @TILDA is "~"
** @PIPE is "|"
** @GTHAN is ">"
** @LTHAN is "<",
** @AST is "*"
** @EQUAL = "="
** @ENTER is "\n"
** @COMMENT is "#",
** @BANG is "!"
** @COLON is ":",
** @TEXT is quoted symbol
** @END_T is end of line
*/

enum				e_techline
{
	WORD_P = 1,
	SPACE,
	BSLASH,
	SCOLON,
	AND,
	DQUOTE,
	SQUOTE,
	OPAREN,
	CPAREN,
	OBRACKET,
	CBRACKET,
	OBRACE,
	CBRACE,
	DOLLAR,
	TILDA,
	PIPE,
	GTHAN,
	LTHAN,
	AST,
	EQUAL,
	ENTER,
	COMENT,
	BANG,
	COLON,
	TEXT,
	END_T,
};

/*
** Globals
** ____________________________________________________________________________
*/

/*
** @g_envi - global variable with all the shell variables
** @g_var_size is the length of the @g_envi buffer
** @g_prompt is the function and the prompt valid
** @g_hist is the structure with the history valid for
** the shell session
*/

t_prompt			g_prompt;
t_history			g_hist;
char				**g_envi;
int					g_var_size;

/*
** Functions
** ____________________________________________________________________________
*/

/*
** File main.c
*/

int					readline_start(void);
int					check_terminal(void);
int					set_noncanonical_input(void);
int					reset_canonical_input(void);

/*
** File options_proc.c
*/

int					find_options(int num, char *flags_arr[num], char **arr);
int					options_in_arg(char *arri, int num,
						char *flags_arr[num], int *final);
int					options_proc(char arrij, char *flags_arr, int *final);
int					suboptions_proc(char *arri, int num,
						char *flags_arr[num], int *final);

/*
** File errors_handler.c
*/

int					error_handler(int status, char *str);
int					error_handler_continuation(int status, char *str);
int					variable_errors(int status, char *str);
int					options_errors(int status, char *str);
int					syntax_errors(int status, char *str);
int					syntax_errors_files(int status, char *str);

/*
** File clean_all.c
*/

int					clean_everything(void);
int					clean_readline(void);
int					clean_parser(void);
int					clean_termcap(void);

/*
** File signals_processing.c
*/

int					signals_reroute(int from);
void				signal_ctrl_c_readline(int sig);
void				signal_screen_readline(int sig);
void				signal_ctrl_c_parser(int sig);

/*
** Folder SHELL_VARIABLES
** ____________________________________________________________________________
*/

/*
** File form_environment.c
*/

int					create_env(void);
int					save_environment_variable(int num);
int					save_shell_variable(int num);
int					save_readonly_variable(int num);
char				*ft_add_rdovar(char *first, char *scnd, int flag);

/*
** File add_new_value.c
*/

char				*find_env_value(char *str);
int					find_in_variable(int *j, char *name);
int					add_new_env(char *name);
int					change_env_value(char *new_val, int i);

/*
** File envir_variables.c
*/

int					find_in_any_variable(char **env, int *j, char *name);
int					exit_status_variables(int status);
char				**form_envir_for_cmd(void);

/*
** Folder UNIX_FUNCTIONS
** ____________________________________________________________________________
*/

size_t				ft_count_words(char const *s, char c, size_t len);
char				*ft_find_token_sep(char *str);
char				*ft_make_techline(char *cmd, int len);
char				get_tech_num(char check);
int					ft_tmpfile(void);

#endif
