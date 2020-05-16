
#ifndef PARSER_H
# define PARSER_H

# define HEREDOC_BUF	3 //проверить

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

typedef	struct			s_exec
{
	char				**argv;
	int					argc;
	int					flag;
	t_list				*fd;
}						t_exec;

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

t_cmd				*init_parser_line(char *line);
void				free_parser_line(t_cmd **pline);
int					delete_or_insert_to_pline(t_cmd **pline,
						int i, int num);
int					expansion_pline_processing(t_cmd **lcmd, int *i,
						int start, char *find);

/*
** File parser_blocks_processing.c
*/

t_list				*create_new_list(void);
void				bzero_grammar_block(t_pblks *block);
int					free_pblocks_except_heredoc(t_list **head);
int					free_pblock_not_heredoc(t_list **runner_blk,
						t_list **last_here_blk, int step);
int					free_parser_blocks_all(t_list **head);

/*
** File parser_global_processing.c
*/

void				print_all_lists(void);
void				print_fd_blocks(t_pblks	*ptr_block_cont);
void				print_techline(char *cmd, char *techline, int len_tech);
void				free_fdredir_content(t_list **runner_fd,
						t_fd *ptr_fd);
void				free_pblock_content(t_pblks **ptr_cont);

/*
** File prepare_and_exec.c
*/

int					prepare_and_exec(void);
int					prepare_fdredir(t_pblks **pblk_cont);
int					prepare_fdredir_fd(t_list **fd_runner);
char				**form_argv(t_cmd *lcmd, int *eargc);
char				*new_arg_from_lcmd(t_cmd *lcmd, int *j);

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

/*
** Folder REDIRECTION
** ____________________________________________________________________________
*/

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
** Folder EXEC
** ____________________________________________________________________________
*/

int			form_and_exec(t_pblks *pblk_cont);
int			start_exec(t_exec *exec);
int			builtins_exec(t_exec *exec, int flag);
int			exec_clean(char *path, int exit_status, char *err_msg);
int			redirection_exec(t_exec *exec);
char		*path_start_exec(t_exec *exec);
char		*search_cmd_exec(char *name);
char		*cmd_binary_path(char *env_path, char *name);
char		*form_path(char *ret, char *env_path, char *name);
int			save_streams(int mode);
int			cmd_fork_and_exec(t_exec *exec, char *path, pid_t *child_pid);

#endif
