NAME = 21sh

FLAGS = -Wall -Werror -Wextra
FLAGS += -g

#______________________________________________________________________________

BUILTIN_DIR = builtin
BUILTIN = \
			$(BUILTIN_DIR)/echo.c \
			$(BUILTIN_DIR)/env.c \
			$(BUILTIN_DIR)/exit.c \
			$(BUILTIN_DIR)/history.c \
			$(BUILTIN_DIR)/init_structures.c \
			$(BUILTIN_DIR)/pwd.c \
			$(BUILTIN_DIR)/set.c \
			$(BUILTIN_DIR)/unset.c \
			$(BUILTIN_DIR)/usages.c \
            $(CD)

CD =		$(BUILTIN_DIR)/cd/cd.c \
			$(BUILTIN_DIR)/cd/cd_flags.c \
			$(BUILTIN_DIR)/cd/cd_valid.c \
			$(BUILTIN_DIR)/cd/cd_parser.c \
			$(BUILTIN_DIR)/cd/cd_change_path.c \
			$(BUILTIN_DIR)/cd/cd_new_path.c

#______________________________________________________________________________

GLOBAL_DIR = global
GLOBAL = 	$(GLOBAL_DIR)/clean_all.c \
			$(GLOBAL_DIR)/error_handler.c \
			$(GLOBAL_DIR)/options_proc.c \
			$(GLOBAL_DIR)/signals_processing.c \
			$(SHELL_VARIABLES) \
			$(UNIX_FUNCTIONS)

SHELL_VARIABLES = \
			$(GLOBAL_DIR)/shell_variables/environment21.c \
			$(GLOBAL_DIR)/shell_variables/variables_processing.c \
			$(GLOBAL_DIR)/shell_variables/variables_array_processing.c

UNIX_FUNCTIONS = \
			$(GLOBAL_DIR)/unix_functions/ft_count_words.c \
			$(GLOBAL_DIR)/unix_functions/ft_find_token.c
			
#______________________________________________________________________________			

PARSER_DIR = parser
PARSER = 	$(PARSER_DIR)/before_execution.c \
			$(PARSER_DIR)/find_spec.c \
			$(PARSER_DIR)/parser21.c \
			$(PARSER_DIR)/slice_to_blocks.c \
			$(ASSIGNMENT) \
			$(EXEC) \
			$(PATH_TREE_ORDER) \
			$(QUOTING) \
			$(REDIRECTION) \
			$(SUBSTITUTION)

ASSIGNMENT = \
			$(PARSER_DIR)/assignment/backend_variables.c \
			$(PARSER_DIR)/assignment/assignment.c

EXEC = 		$(PARSER_DIR)/exec/exec_init.c \
			$(PARSER_DIR)/exec/exec_core.c \
			$(PARSER_DIR)/exec/exec_utils.c \
			$(PARSER_DIR)/exec/path_parse.c

PATH_TREE_ORDER = \
			$(PARSER_DIR)/path_tree_order/insert_leaf_pathtree.c \
			$(PARSER_DIR)/path_tree_order/result_pathtree.c \
			$(PARSER_DIR)/path_tree_order/start_pathtree.c

QUOTING =	$(PARSER_DIR)/quoting/quote_control.c \
			$(PARSER_DIR)/quoting/pre_parsing_work.c

REDIRECTION = \
			$(PARSER_DIR)/redirection/redirect.c \
			$(PARSER_DIR)/redirection/ft_tmpfile.c \
			$(PARSER_DIR)/redirection/redir_types_out.c \
			$(PARSER_DIR)/redirection/redir_types_in.c \
			$(PARSER_DIR)/redirection/fd_block.c \
			$(PARSER_DIR)/redirection/here_doc.c \
			$(PARSER_DIR)/redirection/here_doc_buffer.c

SUBSTITUTION = \
			$(PARSER_DIR)/substitution/substitution.c \
			$(PARSER_DIR)/substitution/ft_find_var.c \
			$(PARSER_DIR)/substitution/ft_curv_var.c \
			$(PARSER_DIR)/substitution/param_help_func.c \
			$(PARSER_DIR)/substitution/ft_substring_var.c \
			$(PARSER_DIR)/substitution/tilda.c \
			$(PARSER_DIR)/substitution/history_sign.c

#______________________________________________________________________________

READLINE_DIR = readline
READLINE = 	$(READLINE_DIR)/readline.c \
			$(READLINE_DIR)/prompts.c \
			$(READLINE_DIR)/termcap_usage.c \
			$(READLINE_DIR)/cursor_position.c \
			$(READLINE_DIR)/front_insertions.c \
			$(READLINE_DIR)/str_edit.c \
			$(READLINE_DIR)/escape.c \
			$(READLINE_DIR)/ctrl_key.c \
			$(READLINE_DIR)/colors.c \
			$(READLINE_SIMPLE) \
			$(KEY_ACTIONS) \
			$(AUTO_COMPLETION) \
			$(HISTORY)

READLINE_SIMPLE = \
			$(READLINE_DIR)/readline_simple/readline_simple.c \
			$(READLINE_DIR)/readline_simple/str_edit_simple.c \
			$(READLINE_DIR)/readline_simple/escape_simple.c \
			$(READLINE_DIR)/readline_simple/keys_simple.c

KEY_ACTIONS = \
			$(READLINE_DIR)/key_actions/arrow_keys.c \
			$(READLINE_DIR)/key_actions/ctrl_kult.c \
			$(READLINE_DIR)/key_actions/cut_words.c \
			$(READLINE_DIR)/key_actions/delete_keys.c \
			$(READLINE_DIR)/key_actions/esc_jump_words.c \
			$(READLINE_DIR)/key_actions/esc_t.c \
			$(READLINE_DIR)/key_actions/jump_around.c \
			$(READLINE_DIR)/key_actions/paste_key.c

AUTO_COMPLETION = \
			$(READLINE_DIR)/auto_completion/start_completion.c \
			$(READLINE_DIR)/auto_completion/front_part_compl.c \
			$(READLINE_DIR)/auto_completion/analyse_line_compl.c \
			$(READLINE_DIR)/auto_completion/menu_receipt_compl.c \
			$(READLINE_DIR)/auto_completion/question_if_many_compl.c \
			$(READLINE_DIR)/auto_completion/path_and_cursor_processing_compl.c \
			$(READLINE_DIR)/auto_completion/output_buffer_compl.c

HISTORY = 	$(READLINE_DIR)/history/start_history.c \
			$(READLINE_DIR)/history/history_buffer_proc.c \
			$(READLINE_DIR)/history/history_file_proc.c \
			$(READLINE_DIR)/history/front_part_hist.c \
			$(READLINE_DIR)/history/back_part_hist.c

#______________________________________________________________________________

SOURCES =	main.c \
			$(BUILTIN) \
			$(GLOBAL) \
			$(PARSER) \
			$(READLINE) \

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft
LIB_INCLUDE = $(LIBFT)/includes
LIBFT_PATH = $(LIBFT)/libft.a

INCLUDE_DIR = includes
BUILTIN_INCLUDE_DIR = $(INCLUDE_DIR)/builtin
SHARED_INCLUDE_DIR = $(INCLUDE_DIR)

all:	$(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "\033[32;01mCompiling 21sh...\033[0m"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT_PATH) -ltermcap
	@echo "\033[32;01m21sh is ready\033[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c includes/shell21.h
	@mkdir -p $(DIR_O)
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)
	@mkdir -p $(DIR_O)/$(BUILTIN_DIR)/cd
#_____________________________________________________
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)/shell_variables
	@mkdir -p $(DIR_O)/$(GLOBAL_DIR)/unix_functions	
#_____________________________________________________	
	@mkdir -p $(DIR_O)/$(PARSER_DIR)
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/path_tree_order
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/exec
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/quoting
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/assignment
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/substitution
	@mkdir -p $(DIR_O)/$(PARSER_DIR)/redirection
#_____________________________________________________	
	@mkdir -p $(DIR_O)/$(READLINE_DIR)
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/readline_simple
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/key_actions
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/auto_completion
	@mkdir -p $(DIR_O)/$(READLINE_DIR)/history
#_____________________________________________________	
	gcc $(FLAGS) -c -I$(LIB_INCLUDE) -I$(BUILTIN_INCLUDE_DIR) -I$(SHARED_INCLUDE_DIR) -o $@ $<

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
