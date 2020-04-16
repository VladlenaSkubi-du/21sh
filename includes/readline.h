
#ifndef READLINE_H
# define READLINE_H

# include "readline_simple.h"
# define SESC_NUM		5

# define TERMCAP_SIZE 	20
# define CMD_SIZE		100
# define TAB			0x1
# define NEW_LINE_SY	0x2
# define NEW_LINE_TE	0x4

# define RED			"\033[31m"
# define ORANGE			"\033[38;5;208m"
# define YELLOW			"\033[33m"
# define GREEN			"\033[32m"
# define BLUE			"\033[36m"
# define PURPLE			"\033[35m"
# define DEFAULT		"\033[0m"

/*
** @t_rline is for the whole readline part:
**
** @cmd is a command string printed by the user
** @pos - position of the cursor in the command-string
** @pos_x - number of column in the terminal - needs always
** to be updated with the real terminal x-position, absolute value
** @pos_y - relevant according to the beginning of g_rline.cmd and
** the terminal width coordinate of the cursor vertically
** @str_num - number of lines the command-string consists of
** @prompt_len - length of the prompt (invitation to enter the command)
** @cmd_buff_len - buffer of the cmd-line
** (can grow, after printing "Enter" is freed)
** @flag - the "working" variable
*/

typedef struct			s_rline
{
	char				*cmd;
	int					cmd_len;
	int					pos;
	int					pos_x;
	int					pos_y;
	int					str_num;
	int					prompt_len;
	int					cmd_buff_len;
	int					flag;
}						t_rline;

/*
** The main termcap codes used
*/

typedef struct			s_cap
{
	char				sf[TERMCAP_SIZE];
	char				le[TERMCAP_SIZE];
	char				nd[TERMCAP_SIZE];
	char				up[TERMCAP_SIZE];
	char				dow[TERMCAP_SIZE];
	char				cd[TERMCAP_SIZE];
	char				cr[TERMCAP_SIZE];
}						t_cap;

/*
** @t_complition is for the auto-completion part
**
** @buffer - the menu-buffer (all the options for completion)
** @buf_lines - how many lines the menu buffer consists of after
** allocations into columns and lines
** @buf_width - the length of each buffer line (including all tabs)
** @word_len - the maximal length of the word with the tab inscluded,
** according to which alignment is done (as in ls-program)
** @word_nb - the number of menu-options
** @i - counter
*/

typedef struct			s_completion
{
	char				**buffer;
	int					buf_lines;
	int					buf_width;
	int					word_len;
	int					word_nb;
	int					i;
}						t_completion;

t_rline					g_rline;
struct winsize			g_screen;
t_cap					g_cap;
struct termios			g_backup_tty;

/*
** File main.c
*/

int						readline_start(void);
int						check_terminal(void);
int						set_noncanonical_input(void);
int						reset_canonical_input(void);


/*
** File readline.c - the beginning of the work with readline
*/

int						start_readline21(int tmp);
char					*finalize_cmd(char *cmd);
char					*readline(void);
void					init_readline(void);
int						readline_choice(char sy);

/*
** File prompts.c
*/

int						main_prompt(void);
int						dquote_prompt(void);
int						heredoc_prompt(void);
int						other_prompt(void);
int						prompt_len(void);

/*
** File termcap_usage.c - library of functions to use termcap easily
*/

int						putcap(char *cap);
int						printc(int c);
int						position_cursor(char *cap, int x, int y);
int						init_termcap(void);

/*
** File str_edit.c - universal functions for changing the main command-string
** and dealing with other global-parameters of the command string
*/

int						char_add(char c, char *color);
int						str_shift(char *str, int shift);
int						insert_char(char c, char *color);
int						front_insert_by_letters(char *str, int *pos_x);
int						front_insert_cmd_till_the_end(int str_num_print);

/*
** File escape.c - router to the functions performing actions with
** escape-sequences
*/

int						escape_init(void);
int						escape_check(char **seq_base);
int						incorrect_sequence(void);
int						sequence_process(int sequence_num);

/*
** File ctrl_key.c
*/

int						ctrl_key(char sy);
int						ctrl_process(char *ctrl_base, char sy);
int						ctrl_call(size_t call_num);
int						make_ctrl_p_wrap(void);

/*
** File cursor_position.c - operations to get the termcap cursor postion
** and move it after actions
*/

int						count_x_position_new_line(int nl_pos);
int						move_cursor_from_old_position(int pos_old,
							char direction);
int						front_move_one_char_right(int pos_x);
int						front_move_one_char_left(int pos_x);
int						front_set_cursor_jmp(int *pos, int *pos_x,
							int *pos_y, int flag);

/*
** File front_insertions.c
*/

int						front_insert_one_char(char c, int pos_x,
							char flag, char *color);
int						front_insert_if_newline(int *pos_x, int *pos_y,
							int *str_num, int *flag);
int						front_insert_if_terminal(int *pos_x, int *pos_y,
							int *flag);
int						front_insert_if_line(int *pos_x, int *str_num, int *flag);
int						front_write_one_char(char c, char *color);

/*
** File colors.c
*/

char					*colors_process(int sequence_num);

/*
** Folder KEY_ACTIONS
** ____________________________________________________________________________
*/

/*
** File cut_keys.c
*/

int						backspace_process(void);
int						backspace_newline(char *swap, int len_swap);
int						delete_process(void);
int						delete_till_compl(int delete);

/*
** File arrow_keys.c
*/

int						key_right_proc(void);
int						key_up_proc(void);
int						key_left_proc(void);
int						key_down_proc(void);
int						save_current_grline(int flag); //correct

/*
** File esc_jump_proc.c
*/

int						word_left_proc(void);
int						word_left_onetwo_chars(void);
int						word_right_proc(void);
char					*save_word(int *i, char *cmd, int pos);
char					*save_end(int pos_back);

/*
** File esc_t.c
*/

int						esc_t(void);
int						esc_t_first_left(char flag, int pos_back);
int						esc_t_need_left(char *word_first, int fi,
							char *end);
int						esc_t_need_right(char *word_first, int fi,
							char *end);
int						esc_t_len_pos(char *word_first, int fi);

/*
** File ctrl_kult.c
*/

int						make_ctrl_k(void);
int						make_ctrl_u(void);
int						make_ctrl_l(void);
int						make_ctrl_t(void);
int						make_ctrl_t_begend(int len);

/*
** File cut_words.c
*/

int						make_ctrl_w(void);
int						esc_r(void);
int						esc_d(void);


/*
** File jump_around.c
*/

int             		jump_up(void);
int             		jump_down(void);
int						make_ctrl_a(void);
int						make_ctrl_e(void);

/*
** File paste_keys.c
*/

int						make_ctrl_p(int mode, char *yank);
int						paste_insert(char *yank_str);

/*
** Folder AUTO_COMPLETION
** ____________________________________________________________________________
*/

/*
** File start_completion.c
*/

int						auto_completion(void);
char					**route_menu_receipt(char *tech_line,
							int tech_len, int *total,
							int *max_len);
char					**route_by_prompts(int *total, int *max_len);
int						check_menu(void);
int						insert_word_compl(void);

/*
** File analyse_line_compl.c
*/

char					*get_techline_compl(char *complete,
							int len);
int						analyse_techline_compl(char *compl,
							char *tech_line,
							int len, int *pool);
int						pass_symbols(char *compl, char *tech,
							int i, int *pool);
int						route_to_pools(char *tech, int i,
							int *pool);
int						route_to_arguments(char *compl,
							int i, int *pool);

/*
** File menu_receipt_compl.c
*/

char					**get_variables(char *complete,
							int *total, int *max_len);
t_path					*fill_tree_with_variables(char *complete,
							int *total);
int						insert_variables_to_tree(char *array,
							char *complete, t_path **root,
							int *total);
char					**get_arguments(char **complete,
							int *total, int *max_len);
t_path					*fill_tree_with_arguments(char *path,
							char *complete, int *total);

/*
** File front_part_compl.c
*/

int						print_menu(int pos_back, char **menu,
							int total, int max_len);
int						print_menu_buf_after_insert(int pos_back);
int						clean_menu(void);
int						clean_menu_buf(void);

/*
** File question_if_many_compl.c and also a small function (because of norm)
*/

int						ask_output(int total, int buf_lines,
							int pos_back, int len_x);
int						after_big_menu(int pos_back,
							int len_x, int len_y);
int						count_comment_len(int *find, int num);
int						clean_output_question(int from, int pos_back,
							int len, int len_x);
int						clean_strings_compl(char *compl,
							char *tech_line, int flag);

/*
** File path_and_cursor_processing_compl.c
*/

char					*find_path_compl(char *compl, int tmp);
char					*path_parse_compl(void);
int						position_cursor_for_menu(int len);
int						position_cursor_after_menu_back
							(int len_x, int len_y, int buf_lines, int pos_back);

/*
** File output_buffer_compl.c
*/

t_completion			menu_buf_init(int total, int max_len);
int						buffer_col_print(char *add,
							t_completion *menu_buf);
void					buffer_col_calc(t_completion *menu_buf);
void					buffer_col_finish(t_completion *menu_buf);
void					buf_add(char *str, int size);

/*
** File start_pathtree.c
*/

char					**start_search_in_path(char *find, char *path,
							int *total, int *max);
int						save_path_entry(char *name_d, t_path **root, int *len,
							char *find);
int						save_builtins(t_path **root, int *len, char *find);
char					**form_result_array(t_path **root, int len, int *max);
int						free_path_tree(t_path **root);

/*
** File insert_and_read_leaf_pathtree.c
*/

int						insert_to_path_tree(char *entry_name,
							t_path **root, int *len);
int						insert_new_leaf_to_tree(t_path **root,
							t_path **new_leaf, int *len);
int						insert_leaf_prev(t_path **current,
							t_path **parent, t_path **temp, int *len);
int						insert_leaf_next(t_path **current,
							t_path **parent, t_path **temp, int *len);
int						fill_array_from_tree(t_path **root, char **list,
							int *len, int *max);

/*
** Folder HISTORY
** ____________________________________________________________________________
*/

/*
** File start_history.c
*/

int								start_history(void);
void            				init_history_buffer(void);
char							*define_history_file(void);
int								add_to_history(char *cmd);
int								add_other_prompts_history(char *cmd,
									int flag);

/*
** File history_buffer_proc.c
*/

int								scroll_hist_buffer(int num);
int								save_hist_buffer(int fd);
int								check_if_histsize_changed(void);
char							**make_hist_buffer_smaller(int size);
int								delete_last_history_element(void);

/*
** File history_file_proc.c
*/

int								fill_hist_in_file(void);
int								insert_hist_in_file(int fd, int user_len);
int								open_hist_file(int user_len, char *path);
int                 			read_hist_from_file(int fd);

/*
** File front_part_hist.c
*/

int								make_ctrl_r_history(void);
char							*get_the_answer_hist(int *len);
int								insert_valid_sy_hist(char c,
									int *len, char **find,
									int *len_find);
int								backspace_one_sy(char **find, int *len_find,
									int *len);
int								find_in_history(char *find);

/*
** File back_part_hist.c
*/

int								print_new_cmd_from_history(int coincidence);
char							*free_find_hist(char **find);
int								delete_from_history();

#endif
