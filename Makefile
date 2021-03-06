NAME = 21sh

FLAGS = -Wall -Wextra -Werror
FLAGS += -g

#______________________________________________________________________________

BUILTIN_DIR = builtin
BUILTIN = \
			$(BUILTIN_DIR)/builtin_processing.c \
			$(BUILTIN_DIR)/echo.c \
			$(BUILTIN_DIR)/env.c \
			$(BUILTIN_DIR)/exit.c \
			$(BUILTIN_DIR)/history.c \
			$(BUILTIN_DIR)/pwd.c \
			$(BUILTIN_DIR)/unsetenv.c \
			$(CD) \
			$(SETENV)

CD_DIR = cd
CD =		$(BUILTIN_DIR)/$(CD_DIR)/cd.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_change_path.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_flags.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_new_path.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_parser.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_static.c \
			$(BUILTIN_DIR)/$(CD_DIR)/cd_valid.c

SETENV_DIR = setenv
SETENV = 	$(BUILTIN_DIR)/$(SETENV_DIR)/setenv.c \
			$(BUILTIN_DIR)/$(SETENV_DIR)/setenv_helper.c

#______________________________________________________________________________

GLOBAL_DIR = global
GLOBAL = 	$(GLOBAL_DIR)/clean_all.c \
			$(GLOBAL_DIR)/error_handler.c \
			$(GLOBAL_DIR)/options_proc.c \
			$(GLOBAL_DIR)/signals_processing.c \
			$(SHELL_VARIABLES) \
			$(UNIX_FUNCTIONS)

SHELL_VARS_DIR = shell_variables
SHELL_VARIABLES = \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/add_new_value.c \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/envir_variables.c \
			$(GLOBAL_DIR)/$(SHELL_VARS_DIR)/form_environment.c

UNIX_FUNCS_DIR = unix_functions
UNIX_FUNCTIONS = \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_count_words.c \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_find_token.c \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_make_techline.c \
			$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)/ft_tmpfile.c
			
#______________________________________________________________________________			

PARSER_DIR = parser
PARSER = \
			$(PARSER_DIR)/parser21.c \
			$(PARSER_DIR)/slice_line_by_grammar.c \
			$(PARSER_DIR)/quote_control.c \
			$(PARSER_DIR)/grammar_analysis.c \
			$(PARSER_DIR)/parser_line_processing.c \
			$(PARSER_DIR)/parser_blocks_processing.c \
			$(PARSER_DIR)/parser_global_processing.c \
			$(PARSER_DIR)/prepare_and_exec.c \
			$(PARSER_DIR)/check_hard_errors.c \
			$(PARSER_DIR)/expansions.c \
			$(REDIRECTION) \
			$(EXEC)

EXEC_DIR = exec
EXEC = 		$(PARSER_DIR)/$(EXEC_DIR)/start_exec.c \
			$(PARSER_DIR)/$(EXEC_DIR)/pathparse_exec.c \
			$(PARSER_DIR)/$(EXEC_DIR)/exec_processing.c

REDIRECTION_DIR = redirection
REDIRECTION = \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/redirections.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/redirections_processing.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/fd_content_processing.c \
			$(PARSER_DIR)/$(REDIRECTION_DIR)/heredoc.c			

#______________________________________________________________________________

READLINE_DIR = readline
READLINE = 	$(READLINE_DIR)/readline.c \
			$(READLINE_DIR)/readline_processing.c \
			$(READLINE_DIR)/prompts.c \
			$(READLINE_DIR)/termcap_usage.c \
			$(READLINE_DIR)/front_processing.c \
			$(READLINE_DIR)/cursor_position.c \
			$(READLINE_DIR)/front_insertions.c \
			$(READLINE_DIR)/str_edit.c \
			$(READLINE_DIR)/escape.c \
			$(READLINE_DIR)/ctrl_key.c \
			$(READLINE_SIMPLE) \
			$(KEY_ACTIONS) \
			$(AUTO_COMPLETION) \
			$(HISTORY)

READLINE_SIMPLE_DIR = readline_simple
READLINE_SIMPLE = \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/readline_simple.c \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/str_edit_simple.c \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/escape_simple.c \
			$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)/keys_simple.c

KEY_ACTIONS_DIR = key_actions
KEY_ACTIONS = \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/arrow_keys.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/ctrl_kult.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/cut_words.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/delete_keys.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/esc_jump_words.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/esc_t.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/jump_around.c \
			$(READLINE_DIR)/$(KEY_ACTIONS_DIR)/paste_key.c

AUTO_COMPL_DIR = auto_completion
AUTO_COMPLETION = \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/start_completion.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/front_part_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/analyse_line_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/menu_receipt_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/question_if_many_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/path_and_cursor_processing_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/output_buffer_compl.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/insert_and_read_leaf_pathtree.c \
			$(READLINE_DIR)/$(AUTO_COMPL_DIR)/start_pathtree.c

HISTORY_DIR = history
HISTORY = 	$(READLINE_DIR)/$(HISTORY_DIR)/start_history.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/history_buffer_proc.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/history_file_proc.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/front_part_hist.c \
			$(READLINE_DIR)/$(HISTORY_DIR)/back_part_hist.c

#______________________________________________________________________________

SOURCES =	main.c \
			$(BUILTIN) \
			$(GLOBAL) \
			$(PARSER) \
			$(READLINE) \

#______________________________________________________________________________

DIR_O = objs

DIR_S = srcs

LIB_INCLUDE_DIR = libft/includes
LIB_PRINTF_INCLUDE_DIR = libft/ft_printf/includes
LIB_HEADERS = $(wildcard $(LIB_INCLUDE_DIR)/*.h) $(wildcard $(LIB_PRINTF_INCLUDE_DIR)/*.h)

INCLUDE_DIR = includes
BUILTIN_INCLUDE_DIR = $(INCLUDE_DIR)/builtin
SHARED_INCLUDE_DIR = $(INCLUDE_DIR)

INCLUDES = -I $(BUILTIN_INCLUDE_DIR) -I $(SHARED_INCLUDE_DIR) -I $(LIB_INCLUDE_DIR) -I$(LIB_PRINTF_INCLUDE_DIR)

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = $(addsuffix .libft , libft/)

%.libft:  $(LIB_HEADERS)
		@make -C $*

LIBS_INCLUDED = -Llibft -lft -ltermcap

#______________________________________________________________________________

all:	$(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "\033[32;01mCompiling 21sh...\033[0m"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBS_INCLUDED)
	@echo "\033[32;01m21sh is ready\033[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c $(wildcard $(BUILTIN_INCLUDE_DIR)/*.h) \
									$(wildcard $(SHARED_INCLUDE_DIR)/*.h)
	@mkdir -p $(DIR_O)
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)/$(CD_DIR)
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)/$(SETENV_DIR)
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)/$(SHELL_VARS_DIR)
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)/$(UNIX_FUNCS_DIR)	
#_____________________________________________________	
	@mkdir -p $(DIR_O)/$(PARSER_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(EXEC_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/$(REDIRECTION_DIR)
#_____________________________________________________	
	@mkdir -p $(DIR_O)/$(READLINE_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(READLINE_SIMPLE_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(KEY_ACTIONS_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(AUTO_COMPL_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/$(HISTORY_DIR)
#_____________________________________________________	
	gcc $(FLAGS) -c $(INCLUDES) -o $@ $<

clean:
	@echo "\033[34mDeleting 21sh o-files\033[0m"
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@echo "\033[34mDeleting 21sh binary\033[0m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re:		fclean all

.PHONY: all fclean clean re
