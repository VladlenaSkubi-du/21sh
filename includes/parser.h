
#ifndef PARSER_H
# define PARSER_H

# define HEREDOC_BUF	200

/*
** Defines for @flags in blocks
*/

# define PIPED_OUT		0x1 
# define PIPED_IN		0x2

/*
** Define for @err in blocks and
** @flags (temporarily) in fd_blocks
*/

# define REDIR_HARD		0x4
# define REDIR_SOFT		0x8

/*
** Define for @flags (permanantly) in
** fd_blocks
*/

# define CLOSE_FD		0x10
# define CREATE_FD		0x20
# define OPEN_FD		0x40
# define REDIRECTION_FD	0x80

/*
** ____________________________________________________________________________
*/

typedef	struct			s_cmd
{
	char				*cmd;
	char				*tech;
	int					len_tech;
}						t_cmd;

typedef struct			s_pblks
{
	t_cmd				*lcmd;
	int					beg;
	int					end;
	t_list				*fd;
	int					err;
	int					flag;
}						t_pblks;

typedef struct  		s_fd
{
	int					fd_old;
	int					fd_new;
	char				*file;
	int					flag;
}						t_fd;

/*
** Globals:
** @g_pline = global parser line
** @g_grblks = global grammar blocks
*/

t_cmd					*g_pline; //question
t_list					*g_grblks;
int						g_herenum;

/*
** ____________________________________________________________________________
*/

/*
** File parser21.c
*/

int					parser(char *line);
int					prepare_parser(char *line);
int					slice_by_scolons(void);
int					slice_by_pipes_cycle(void);
int					slice_by_pipes(t_list **current, int beg, int end,
						t_pblks *ptr_block_cont);


/*
** File quote_control.c
*/

int					start_quotes(char *techline);
int					quotes_make_text_inside(t_stack **stack,
						int i, char *techline);
int					quotes_define_prompts(t_stack **stack);

/*
** File grammar_analysis.c
*/

int					gramlex_analysis(void);
int					delete_quotes_from_line(t_pblks **current_cont,
						t_cmd **ptr_lcmd);
int					check_redirections(t_pblks **current_cont,
						t_cmd **ptr_lcmd);
int					redir_heredoc(t_pblks **current_cont,
						t_cmd **ptr_lcmd, int *i);
int					shift_harderror_to_last_heredoc(void);

/*
** File parser_line_processing.c
*/

void				print_all_lists(void);
void				print_fd_blocks(t_pblks	*ptr_block_cont);
void				print_techline(char *cmd, char *techline, int len_tech);

/*
** File parser_blocks_processing.c
*/

t_list				*create_new_list(void);
void				bzero_grammar_block(t_pblks *block);
int					free_pblocks_except_heredoc(t_list **head);
int					free_pblock_not_heredoc(t_list **runner_blk,
						t_list **last_here_blk, t_pblks	**ptr_cont, int step);
int					free_parser_blocks_all(t_list **head);

/*
** File parser_global_processing.c
*/

t_cmd				*init_parser_line(char *line);
void				free_parser_line(t_cmd **pline);
int					delete_or_insert_to_pline(t_cmd **pline,
						int i, int num);
int					expansion_pline_processing(t_cmd **lcmd, int *i,
						int start, char *find);
void				free_fdredir_content(t_list **runner_fd,
						t_fd *ptr_fd);
void				free_pblock_content(t_list **runner_blk,
						t_pblks	**ptr_cont);

/*
** File redirections.c
*/

int					redir_inand(t_pblks **current_cont,
						t_cmd **ptr_lcmd, int *i);
int					redir_in(t_pblks **current_cont,
						t_cmd **ptr_lcmd, int *i);
int					redir_outout(t_pblks **current_cont,
						t_cmd **ptr_lcmd, int *i);
int					redir_outand(t_pblks **current_cont,
						t_cmd **ptr_lcmd, int *i);
int					redir_out(t_pblks **current_cont,
						t_cmd **ptr_lcmd, int *i);

/*
** File redirection_processing.c
*/

int					find_fdbefore_redir(t_cmd **ptr_lcmd,
						t_fd *fd_inout, int *i);
int					find_fdafter_redir(t_cmd **ptr_lcmd,
						t_fd *fd_inout, int *i);
int					minus_close_redir(t_pblks **current_cont, t_cmd **ptr_lcmd,
						t_fd fd_inout, int *i);
int					activate_redir_error(t_pblks **current_cont, t_fd fd_inout);
int					only_num_fdafter_redir(t_fd *fd_inout);

/*
** File fd_content_processing.c
*/

void				bzero_fd_redir(t_fd *fd_block);
t_list				*add_redir_to_block(t_fd fd_inout);
int					free_fdredir_except_heredoc(t_pblks **current_cont);
int					free_fd_not_heredoc(t_list **runner_fd,
						t_list **last_here_fd, t_fd *ptr_fd, int step);
int					free_fdredir_from(t_list **fd_from);

/*
** File heredoc.c
*/

int					check_heredoc_closure(t_cmd *pline);
t_list				*find_first_heredoc(void);
int					close_heredoc(t_list **fd_hered, t_cmd *pline,
						char **heredoc_buf, int *buf_size);
int					load_heredocbuf_into_file(int fd, char *heredoc_buf);
int					save_heredoc_buffer(char **here_buf, int *buf_size,
						char *cmd, int mode);

/*
** File prepare and exec.c
*/

int					prepare_and_exec(void);
int					prepare_fdredir(t_pblks **pblk_cont);
int					prepare_fdredir_fd(t_list **fd_runner);


/*
** File check_hard_errors.c
*/

int					check_hard_errors(void);
int					check_empty_pblock(t_pblks **pblk_cont);
int					close_empty_fd_blocks(t_list **fd_runner);

/*
** File expansions.c
*/

int					tilda_expansion(t_cmd **cmd_part);
char				*home_from_etcpasswd(void);
int					dollar_expansion(t_cmd **cmd_part, char **str);
int					dollar_expansion_loop(t_cmd **lcmd);
int					dollar_expansion_processing(t_cmd **str_cmd, int *i,
						int start, char *find);

// enum					e_way
// {
// 	REW,
// 	FF,
// 	IN_R,
// 	OUT_R,
// 	CLOSE_FD = -42,
// 	MINUS = 5,
// 	CONTINUE,
// 	LINE,
// 	ASSIGN,
// 	LARGE,
// 	SMALL
// };

typedef	struct			s_word
{
	size_t				start;
	size_t				len;
}						t_word;

/*
** Struct to save and work with techline
*/

// typedef struct  		s_tech
// {
//    char					*line;
//    size_t				len;
//    size_t				alloc_size;
// }               		t_tech;

//TODO to fill

/*
** @l_cmd is local copy of @g_pline.cmd but cut according
** to the block to be executed
** @l_tline is @g_pline.tech of the @l_cmd
** @start is the index with that block in l_cmd starts
** @end is the index with that block in l_cmd ends
** @fd is a list where all the fds entered with the command are saved
** @envir is environment for the command to be executed
** @ar_v is an agrument for the command to be executed
** @ar_c is a number of arguments for the command to be executed
** @flags are flags defined above
** @token is token in the end of the block for errors output
** @err is string where there is the error message saved
** @err_i is index, on which position the error was found (what token does not see)
** Struct to work with lextree fd[3] needs to know if it is redirection
** FLAGS:
** 0x01 -- PIPED_OUTPUT
** 0x02 -- PIPED_INPUT
** 0x04 -- REDIRECTION (It's kinda different, as we have to take fd from another place)
** 0x08 -- IS_BG
*/

typedef struct  		s_ltree
{
	// char				*l_cmd;
	// t_tech				l_tline;
	t_cmd				lcmd;
	size_t				start;
	size_t				end;
	t_list				*fd; //на одну команду может быть очень много fd и по грамматике мы должны чистать их по порядку и по порядку перенаправлять
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
	char				**buf;
	int					buf_size;
}						t_here;

/*
** Global vars
** @g_pline is parser line
*/

// char					*g_pline.cmd;
// size_t					g_cmd_size;
// t_tech					g_techline;
t_here					g_heredoc;

/*
** File slice_to_blocks.c
*/

int 					ft_block_start(t_list **list);
int						ft_block_foward(t_ltree **sub, t_list **start);
int						ft_block_add_to_list(t_ltree *block, t_list **list);
int     				slice_by_scolons(void);
int     				ft_slice_bg(size_t *i, t_ltree	*block, t_list **start_list);

/*
** File find_spec.c
*/

t_ltree					*ft_find_pipe(t_ltree *block, t_ltree *final, size_t *i);
t_ltree					*ft_find_logic(t_ltree *block, t_ltree *final);
t_ltree					*ft_check_andor_pipes(t_ltree *block, t_ltree *final);
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
							size_t block_end);

/*
** Folder redirection_________________________________________________________
*/

/*
** File ft_tmpfile.c
*/

int						ft_tmpfile(void);

/*
** File redirect.c
*/

// int						ft_find_redirection(t_ltree *final);
// char					*ft_word_to_redir(size_t *i, t_ltree *final,
// 							int rew_ff);
// int						ft_word_to_redir_rew(size_t *i, t_ltree *final,
// 						long long *size, size_t *start);
// int						ft_null_redir(t_ltree *pos, size_t i, long long num);
// int						ft_error_redir(t_ltree *final);

/*
** File redir_types_out.c
*/

// int						ft_redir_great(t_ltree *final, size_t *i);
// int						ft_redir_dgreat(t_ltree *final, size_t *i);
// int						ft_redir_greatand(t_ltree *final, size_t *i);
// int						ft_access_check(char **f_name, t_ltree *final,
// 							int type);


/*
** File redir_types_in.c
*/

// int						ft_redir_less(t_ltree *final, size_t *i);
// int						ft_redir_dless(t_ltree *final, size_t *i);
// int						ft_redir_dless_min(t_ltree *final, size_t *i);
// int						ft_redir_lessand(t_ltree *final, size_t *i);
// int						ft_heredoc_form(t_fd_redir *fd_open, char **f_name,
// 						t_ltree *final, int flag);

/*
** File fd_block.c
*/

// int						add_redir_fd(t_ltree *final, t_fd_redir *redir);
// int						ft_check_n_redir_op(size_t i, t_ltree *final, int std);
// int						ft_check_redir_op_n(char *find, int std);
// int						ft_num_or_word_out(char **f_name, t_fd_redir *fd_open,
// 							t_ltree *final);
// int						ft_num_or_word_in(char **f_name, t_fd_redir *fd_open,
// 							t_ltree *final);

/*
** File here_doc.c
*/

// int						check_heredoc_closure(void);
// int						ft_check_heredoc_end(void);
// int						ft_heredoc_fill(int ret);
// int						ft_heredoc_rem(void);
// int						ft_g_init_heredoc(void);

/*
** File here_doc_buffer.c
*/

// int						add_to_heredoc_buf(char ***array, char *add,
// 						int *buf_size);
// int						null_here_line(void);
// int						recover_g_cmd_here(void);
// int						here_tab_remove(char **line);

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
char					*ft_find_var_value(char **find);
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



/*
** File pre_parsing_work.c
*/

int						pre_parsing_cut_glue(t_ltree *sub);
int						pre_parsing_squote(int *i, t_ltree *sub);
int						pre_parsing_back(int *i, t_ltree *sub);
int						pre_parsing_andor_pipe(int *i, t_ltree *sub);
int						ft_reglue(int *i, int num, t_ltree *sub);

/*
** Folder PATH_TREE_ORDER
** ____________________________________________________________________________
*/



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

char					*path_init(t_ltree *pos);
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
