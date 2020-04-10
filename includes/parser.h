
#ifndef PARSER_H
# define PARSER_H

# define HEREDOC_BUF 200

/*
** Defines for FLAGS
*/

# define PIPED_OUT		0x00000001U
# define PIPED_IN		0x00000002U
# define REDIRECTION	0x00000004U
# define IS_BG			0x00000008U
# define LOG_AND_IN		0x00000010U
# define LOG_AND_OUT	0x00000020U
# define LOG_OR_IN		0x00000040U
# define LOG_OR_OUT		0x00000080U
# define GR_START		0x00000100U
# define ERR_IN			0x40000000U
# define ERR_R			0x20000000U
# define ERR_CONT		0x08000000U
# define ERR_OUT		0x10000000U

/*
** Is used in before_execution.c
*/

# define TMPL "/tmp/tmp42sh_XXXXXX" //сделать свою обработку

enum					e_way
{
	REW,
	FF,
	IN_R,
	OUT_R,
	CLOSE = -42,
	MINUS = 5,
	CONTINUE,
	LINE,
	ASSIGN,
	LARGE,
	SMALL
};

typedef	struct			s_word
{
	size_t				start;
	size_t				len;
}						t_word;

/*
** Struct to save and work with techline
*/

typedef struct  		s_tech
{
   char					*line;
   size_t				len;
   size_t				alloc_size;
}               		t_tech;

//TODO to fill

/*
** @l_cmd is
** @l_tline is
** @start is the index with that block in l_cmd starts
** @end is the index with that block in l_cmd ends
** @fd is
** @envir is environment for the command to be executed
** @ar_v is an agrument for the command to be executed
** @ar_c is a number of arguments for the command to be executed
** @flags is
** @token is
** @err is
** @err_i is
** Struct to work with lextree fd[3] needs to know if it is redirection
** FLAGS:
** 0x01 -- PIPED_OUTPUT
** 0x02 -- PIPED_INPUT
** 0x04 -- REDIRECTION (It's kinda different, as we have to take fd from another place)
** 0x08 -- IS_BG
*/

typedef struct  		s_ltree
{
	char				*l_cmd;
	t_tech				l_tline;
	size_t				start;
	size_t				end;
	t_list				*fd;
	char				**envir;
	char				**ar_v;
	int					ar_c;
	int					flags;
	char				*token;
	char				*err;
	size_t				err_i;
}              			t_ltree;

/*
** Struct needs for list of redirections before exec
*/

typedef struct  		s_fd
{
	int					fd_out;
	int					fd_in;
	int					type;
}              			t_fd_redir;

/*
** Struct to save and work with env
** flag needs to know main list
*/

typedef struct  		s_block
{
	char				*name;
	char				*path;
	struct s_block		*next;
	struct s_block		*prev;
	struct s_block		*down;
	struct s_block		*up;
	char				flag;
}               		t_block;

/*
** Struct to save and work with PATH
*/

typedef struct  		s_path
{
	char				*name;
	struct s_path		*next;
	struct s_path		*prev;
	char				flag;
}               		t_path;

/*
** Struct to save and work with here-docs
*/

typedef struct			s_stop
{
	char				*stop_w;
	int					flag;
	int					fd;
}						t_stop;

typedef struct			s_here
{
	t_list				*list;
	t_stop				stop;
	char				*g_cmd_copy;
	char				*g_techline_copy;
	size_t				g_len_copy;
	char				**buf;
	int					buf_size;
}						t_here;

/*
** Global vars
*/

char					*g_cmd;
size_t					g_cmd_size;
t_tech					g_techline;
t_here					g_heredoc;
t_list					*g_start_list;

/*
** File parser.c
*/

int						parser(char *line);
int						pars_lex_exec(void);
int						ft_get_techline(char *cmd, t_tech *result);
char					get_tech_num(char check);
int						ltree_init(t_ltree *final);

/*
** File slice_to_blocks.c
*/

int 					ft_block_start(t_list **list);
int						ft_block_foward(t_ltree **sub, t_list **start);
int						ft_block_add_to_list(t_ltree *block, t_list **list);
int     				ft_slice_fg(void);
int     				ft_slice_bg(size_t *i, t_ltree	*block, t_list **start_list);

/*
** File find_spec.c
*/

t_ltree					*ft_find_pipe(t_ltree *block, t_ltree *final, size_t *i);
t_ltree					*ft_find_logic(t_ltree *block, t_ltree *final);
t_ltree					*ft_check_andor_pipes(t_ltree *block, t_ltree *final,
						t_list **list);
void					ft_lst_ltree_clear(t_list **begin_list);
int						ft_correct_after_andor_pipe(size_t *i);

/*
** File before_execution.c
*/

int						before_exec(t_ltree *sub);
int						argv_forming(t_ltree *sub);
t_word					ft_give_me_word(char const *s, char c, size_t len);
int						ft_local_copy_lines(t_ltree *sub, char *cmd,
							char *tline);
int						erroring_andor_pipe(t_ltree *final, size_t *i,
						int tmp, size_t block_end);

/*
** Folder redirection_________________________________________________________
*/

/*
** File ft_tmpfile.c
*/

int						ft_tmpfile(char *template);

/*
** File redirect.c
*/

int						ft_find_redirection(t_ltree *final);
char					*ft_word_to_redir(size_t *i, t_ltree *final,
							int rew_ff);
int						ft_word_to_redir_rew(size_t *i, t_ltree *final,
						long long *size, size_t *start);
int						ft_null_redir(t_ltree *pos, size_t i, long long num);
int						ft_error_redir(t_ltree *final);

/*
** File redir_types_out.c
*/

int						ft_redir_great(t_ltree *final, size_t *i);
int						ft_redir_dgreat(t_ltree *final, size_t *i);
int						ft_redir_greatand(t_ltree *final, size_t *i);
int						ft_access_check(char **f_name, t_ltree *final,
							int type);


/*
** File redir_types_in.c
*/

int						ft_redir_less(t_ltree *final, size_t *i);
int						ft_redir_dless(t_ltree *final, size_t *i);
int						ft_redir_dless_min(t_ltree *final, size_t *i);
int						ft_redir_lessand(t_ltree *final, size_t *i);
int						ft_heredoc_form(t_fd_redir *fd_open, char *f_name,
						t_ltree *final, int flag);

/*
** File fd_block.c
*/

int						add_redir_fd(t_ltree *final, t_fd_redir *redir);
int						ft_check_n_redir_op(size_t i, t_ltree *final, int std);
int						ft_check_redir_op_n(char *find, int std);
int						ft_num_or_word_out(char **f_name, t_fd_redir *fd_open,
							t_ltree *final);
int						ft_num_or_word_in(char **f_name, t_fd_redir *fd_open,
							t_ltree *final);

/*
** File here_doc.c
*/

int						ft_check_is_heredoc(int	ret);
int						ft_check_heredoc_end(void);
int						ft_heredoc_fill(int ret);
int						ft_heredoc_rem(void);
int						ft_g_init_heredoc(void);

/*
** File here_doc_buffer.c
*/

int						add_to_heredoc_buf(char ***array, char *add,
						int *buf_size);
int						null_here_line(void);
int						recover_g_cmd_here(void);
int						here_tab_remove(char **line);

/*
** Folder assignment__________________________________________________________
*/

/*
** File backend_variables.c
*/

int             		find_assignment_in_vars(char *sub, size_t var,
							size_t eq, size_t val);
int						assignment_in_curv_var(t_ltree *sub,
							char **line, char *oper, size_t *i);
int						ft_colon_check(int *len, char **line,
							char **oper, int *j);

/*
** File assignment.c
*/

int						assignment(t_ltree *sub);
int						get_assign_and_add(t_ltree *sub, size_t *var,
							size_t *eq, size_t *val);
int						it_is_command(t_ltree *sub, size_t *i, size_t *var);
int						is_it_argv_n(t_ltree *sub, size_t var);

/*
** Folder substitution________________________________________________________
*/

/*
** File substitution.c
*/

int						ft_substitution(t_ltree *sub);
int						before_add(t_ltree *sub, t_list **lst);
int						ft_check_null(t_ltree *final, t_list **list);
int						insert_str_in_loc_strs(t_ltree *sub,
							char **insert, size_t *i, int flag);

/*
** File ft_find_var.c
*/

int	   					ft_find_var(t_ltree *sub);
int						ft_find_curv_var(t_ltree *sub);
char					*ft_find_var_value(char **find);
int						ft_param_empty(t_ltree *sub, char **find, size_t *i);
int						ft_error_vars(t_ltree *sub, int err, char *msg);

/*
** File ft_curv_var.c
*/

int						ft_type_param_check(t_ltree *sub, char **find,
							size_t *i);
int						ft_param_colon_dash(t_ltree *sub,
							char **line, char *oper, size_t *i);
int						ft_param_colon_equal(t_ltree *sub,
							char **line, char *oper, size_t *i);
int						ft_param_colon_qmark(t_ltree *sub,
							char **line, char *oper, size_t *i);
int						ft_param_colon_plus(t_ltree *sub,
							char **line, char *oper, size_t *i);

/*
** File ft_substring_var.c
*/

int						ft_substring_len(t_ltree *sub, char **line,
							char *oper, size_t *i);
int						ft_substring_s_l_prefix(t_ltree *sub,
							char **line, char *oper, size_t *i);
int						ft_substring_s_l_suffix(t_ltree *sub,
								char **line, char *oper, size_t *i);

/*
** File param_help_func.c
*/

int						ft_param_word_sub(t_ltree *sub,
							char **line, char *oper, size_t *i);
void					ft_one_ltree_clear(t_ltree *buf);
int     				ft_param_error_msg(t_ltree *sub, char **find,
							char *oper);
char					*ft_parsing_str(char *str);

/*
** File tilda.c
*/

int						ft_find_tilda(t_ltree *sub, int flag);
int						ft_getdir_by_name(t_ltree *sub, size_t *i, int flag);
int						ft_get_home(t_ltree *sub, size_t *i);
int						ft_find_dir_info(t_ltree *sub, char *user, size_t *i);

/*
** File history_sign.c
*/

int						ft_find_history(t_ltree *sub);

/*
** Folder quoting_____________________________________________________________
*/

/*
** File quote_control.c
*/

int						nullify(char **techline, size_t size);
int						nullify_dquotes(char **ptr, t_stack **stack);
int						nullify_backslash(char **ptr, t_stack **stack,\
						size_t *count, size_t size);
int						nullify_comment(char **ptr, t_stack **stack);
int						nullify_promt_check(t_stack	**stack);

/*
** File pre_parsing_work.c
*/

int						pre_parsing_cut_glue(t_ltree *sub);
int						pre_parsing_squote(size_t *i, t_ltree *sub);
int						pre_parsing_back(size_t *i, t_ltree *sub);
int						pre_parsing_andor_pipe(size_t *i, t_ltree *sub);
int						ft_reglue(size_t *i, int num, t_ltree *sub);

/*
** Folder PATH_TREE_ORDER
** ____________________________________________________________________________
*/

/*
** File start_pathtree.c
*/

char					**start_search_in_path(char *find, char *path,
							int *total, int *max);
int						save_path_entry(char *name_d, t_path **root, int *len,
							char *find);
int						save_builtins(t_path **root, int *len, char *find);
int						free_path_tree(t_path **root);

/*
** File insert_leaf_pathtree.c
*/

int						insert_to_path_tree(char *entry_name,
							t_path **root, int *len);
void					init_new_leaf(char *entry_name, t_path **tmp);
int						insert_new_leaf_to_tree(t_path **root,
							t_path **new, int *len);
int						insert_leaf_prev(t_path **current,
							t_path **parent, t_path **temp, int *len);
int						insert_leaf_next(t_path **current,
							t_path **parent, t_path **temp, int *len);

/*
** File result_pathtree.c
*/

char					**form_result_array(t_path **root, int len, int *max);
int						fill_array_from_tree(t_path **root, char **list,
							int *len, int *max);

// char					*ft_take_path(char *dir_name);

/*
** Folder exec_________________________________________________________________
*/

/*
** File exec_init.c
*/

int						exec_init(t_ltree *pos);

/*
** File exec_core.c
*/

int						exec_core(t_ltree *pos);

/*
** File path_parse.c
*/

char					*path_init(char **exec_av);
char					**path_parse(void);
char					*form_path(char *ret, char *env_path, char *name);
char					*locate_file(char *env_path, char *name);
char					*path_search(char *name);

/*
** File exec_utils.c
*/

void					free_vec(char **vec);
char					*get_env(char *var);
int						exec_clean(char *path, int exit_status, char *msg);
int						ft_builtins_check(t_ltree *pos, int flag);
int						fd_list_process(t_ltree *pos);

#endif