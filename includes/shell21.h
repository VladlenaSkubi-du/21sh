/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:24:48 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/26 19:26:07 by sschmele         ###   ########.fr       */
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
** @prompt_func is prompt that is valid according to some
** readline and parser analysis
** Can be: main, dquote, heredoc and so on
*/

typedef struct		s_prompt
{
	int				(*prompt_func)(void);
	int				prompt_len_real;
	int				prompt_len;
}					t_prompt;

/*
** @hist is an array with commands (not separated by \n but
** separated as they came to parser)
** @len is the number of lines (commands) in the history
** @last is counter of the last command saved in the history
** @start is a counter from which command from history file we start to
** fill out buffer - not to rewrite the whole buffer to the file but to add
** We need all
*/

typedef struct		s_history
{
	char			**hist;
	int				len;
	int				counter;
	int				last;
	int				start;
	int				last_fc;
}					t_history;

/*
** @BSLASH is "\", @SCOLON is ";", @AND is "&", @DQUOTE is '"',
** @SQUOTE is "'", @OPAREN is "(", @CPAREN is ")", @OBRACKET is "["
** @CBRACKET is "]", @OBRACE is "{", CBRACE is "}", @DOLLAR is "$",
** @TILDA is "~", @PIPE is "|", @GTHAN is ">", @LTHAN is "<",
** @AST is "*", @EQUAL = "=", @ENTER is "\n", @COMENT is "#"
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
	GLUE,
	TEXT,
	END_T,
};

/*
** @g_env - global variable with (char **environ) parameters
** @g_sh_var - shell variables
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
** Folder SHELL_VARIABLES
** ____________________________________________________________________________
*/

/*
** File form_environment.c
*/

int					create_env(void);
int					save_environment_variable(int num);
int					save_shell_variable(int num);
int					exit_status_variables(int status);
int					save_readonly_variable(int num);

/*
** File add_new_value.c
*/

char				*find_env_value(char *str);
int					find_in_variable(int *j, char *name);
int					form_local_envir(char ***arr, int size);
int					add_new_env(char *name);
int					change_env_value(char *new_val, int i);

/*
** File envir_variables.c
*/

int					find_in_any_variable(char **env, int *j, char *name);

/*
** Folder UNIX_FUNCTIONS
** ____________________________________________________________________________
*/

size_t				ft_count_words(char const *s, char c, size_t len);
char				*ft_find_token_sep(char *str);
char				*ft_make_techline(char *cmd, int len);
char				get_tech_num(char check);
int					ft_tmpfile(void);

/*
**_____________________________________________________________________________
*/

/*
** File errors_handler42.c
*/

int					error_handler(int status, char *str);
int					error_handler_continuation(int status, char *str);
int					variable_errors(int status, char *str);
int					options_errors(int status, char *str);
int					syntax_errors(int status, char *str);
int					syntax_errors_files(int status, char *str);

/*
** File clean_all42.c
*/

int					clean_everything(void);
int					clean_readline(void);
int					clean_parser(void);
int					clean_termcap(void);

/*
** File signals_processing21.c
*/

int					signals_reroute(int from);
void				signal_ctrl_c_readline(int sig);
void				signal_screen_readline(int sig);
void				signal_ctrl_c_parser(int sig);

#endif
