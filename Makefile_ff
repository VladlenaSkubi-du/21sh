NAME = 42sh

FLAGS = -Wall #-Werror -Wextra
FLAGS += -g

READLINE42 = 		readline42/start_readline42.c \
			readline42/readline.c \
			readline42/prompts.c \
			readline42/prompts_other.c \
			readline42/terminal_input_changes.c \
			readline42/termcap_usage.c \
			readline42/cursor_position.c \
			readline42/front_cursor_changes.c \
			readline42/front_insertions.c \
			readline42/str_edit.c \
			readline42/undo_yank_call.c \
			readline42/undo.c \
			readline42/escape.c \
			readline42/ctrl_key.c \
			readline42/print_readline_help.c \
			readline42/colors.c \
			$(READLINE_SIMPLE) \
			$(KEY_ACTIONS) \
			$(AUTO_COMPLETION) \
			$(HISTORY)

READLINE_SIMPLE =	readline42/readline_simple/readline_simple.c \
			readline42/readline_simple/str_edit_simple.c \
			readline42/readline_simple/escape_simple.c \
			readline42/readline_simple/keys_simple.c

KEY_ACTIONS =		readline42/key_actions/ctrl_kwuae.c \
			readline42/key_actions/ctrl_tly.c \
			readline42/key_actions/arrow_keys.c \
			readline42/key_actions/esc_word_proc.c \
			readline42/key_actions/esc_t.c \
			readline42/key_actions/cut_keys.c \
			readline42/key_actions/jump_keys.c \
			readline42/key_actions/easter_egg.c

AUTO_COMPLETION =	readline42/auto_completion/start_completion.c \
			readline42/auto_completion/front_part_compl.c \
			readline42/auto_completion/analyse_line_compl.c \
			readline42/auto_completion/menu_receipt_compl.c \
			readline42/auto_completion/question_if_many_compl.c \
			readline42/auto_completion/path_processing_compl.c \
			readline42/auto_completion/cursor_position_completion.c \
			readline42/auto_completion/output_buffer_compl.c

HISTORY = 			readline42/history/start_history.c \
			readline42/history/history_buffer_proc.c \
			readline42/history/history_file_proc.c \
			readline42/history/history_processing.c \
			readline42/history/front_part_hist.c \
			readline42/history/back_part_hist.c

PARSER = 			parser/parser42.c \
			parser/find_spec.c \
			parser/slice_to_blocks.c \
			parser/before_execution.c \
			$(PATH_TREE) \
			$(EXEC) \
			$(QUOTING) \
			$(SUBSTITUTION) \
			$(ASSIGNMENT) \
			$(REDIRECTION)

PATH_TREE = 		parser/path_tree/ft_block.c \
			parser/path_tree/ft_path_help.c \
			parser/path_tree/ft_path.c

EXEC = 				parser/exec/exec_init.c \
			parser/exec/exec_core.c \
			parser/exec/exec_utils.c \
			parser/exec/path_parse.c \
			parser/exec/bg_fg.c \
			parser/exec/exec_new.c \
			parser/exec/job_init.c \
			parser/exec/jobs.c

QUOTING =			parser/quoting/quote_control.c \
			parser/quoting/pre_parsing_work.c

SUBSTITUTION = 		parser/substitution/substitution.c \
			parser/substitution/ft_find_var.c \
			parser/substitution/ft_curv_var.c \
			parser/substitution/param_help_func.c \
			parser/substitution/ft_substring_var.c \
			parser/substitution/tilda.c \
			parser/substitution/history_sign.c

ASSIGNMENT =		parser/assignment/backend_variables.c \
			parser/assignment/assignment.c

REDIRECTION = 		parser/redirection/redirect.c \
			parser/redirection/ft_tmpfile.c \
			parser/redirection/redir_types_out.c \
			parser/redirection/redir_types_in.c \
			parser/redirection/fd_block.c \
			parser/redirection/here_doc.c \
			parser/redirection/here_doc_buffer.c

SIGNALS = 			signals/signals_processing42.c \
			signals/signals_parser.c

SHELL_VARIABLES =	shell_variables/environment42.c \
			shell_variables/variables_processing42.c \
			shell_variables/variables_array_processing42.c

FC =				builtin/fc/fc.c \
			builtin/fc/fc_modes_l.c \
			builtin/fc/fc_modes_s.c \
			builtin/fc/fc_modes_e.c \
			builtin/fc/fc_nums_calc.c \
			builtin/fc/fc_modes_flags.c \
			builtin/fc/fc_modes_no_arguments.c \
			builtin/fc/fc_exec.c \
			builtin/fc/fc_exec_mode_s.c \
			builtin/fc/fc_exec_mode_e.c \
			builtin/fc/fc_tmpfile.c

CD =        builtin/cd/cd.c \
            builtin/cd/cd_flags.c \
            builtin/cd/cd_valid.c \
            builtin/cd/cd_parser.c \
            builtin/cd/cd_change_path.c \
            builtin/cd/cd_new_path.c

BUILTIN = 			builtin/exit.c \
			builtin/set.c \
			builtin/unset.c \
			builtin/history.c \
			builtin/init_structures.c \
			builtin/usages.c \
            builtin/echo.c \
            builtin/pwd.c \
			$(FC) \
            $(CD)

LIBFT_42 =			libft_42/ft_xmalloc.c \
			libft_42/ft_realloc.c \
			libft_42/swap_chars.c \
			libft_42/swap_ints.c \
			libft_42/ft_straddsy.c \
			libft_42/ft_strrchri.c \
			libft_42/ft_issign.c \
			libft_42/ft_add_list.c \
			libft_42/ft_realloc_array.c \
			libft_42/ft_lstclear.c \
			libft_42/ft_count_words.c \
			libft_42/ft_strlenchri.c \
			libft_42/ft_find_token.c \
			libft_42/ft_gnl.c \
			libft_42/ft_putnstr_fd.c \
			libft_42/ft_putnendl_fd.c \
			$(STACK_STRUCTURE)
			# libft_42/ft_lstlast.c \

STACK_STRUCTURE = 	libft_42/stack_structure/ft_init_stack.c \
			libft_42/stack_structure/ft_pop_stack.c \
			libft_42/stack_structure/ft_push_stack.c \
			libft_42/stack_structure/ft_clear_stack.c \
			libft_42/stack_structure/ft_last_stack.c

SOURCES =	main.c \
			options_42sh_42.c \
			options_proc42.c \
			error_handler42.c \
			clean_all42.c \
			$(READLINE42) \
			$(PARSER) \
			$(SIGNALS) \
			$(SHELL_VARIABLES) \
			$(BUILTIN) \
			$(LIBFT_42)

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft/libft.a

all:	$(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "\033[32;01mCompiling 42sh...\033[0m"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -ltermcap
	@echo "\033[32;01m42sh is ready\033[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c includes/shell42.h
	@mkdir -p $(DIR_O)
	@mkdir -p $(DIR_O)/readline42
	@mkdir -p $(DIR_O)/readline42/readline_simple
	@mkdir -p $(DIR_O)/readline42/key_actions
	@mkdir -p $(DIR_O)/readline42/auto_completion
	@mkdir -p $(DIR_O)/readline42/history
	@mkdir -p $(DIR_O)/parser
	@mkdir -p $(DIR_O)/parser/path_tree
	@mkdir -p $(DIR_O)/parser/exec
	@mkdir -p $(DIR_O)/parser/quoting
	@mkdir -p $(DIR_O)/parser/assignment
	@mkdir -p $(DIR_O)/parser/substitution
	@mkdir -p $(DIR_O)/parser/redirection
	@mkdir -p $(DIR_O)/signals
	@mkdir -p $(DIR_O)/shell_variables
	@mkdir -p $(DIR_O)/builtin
	@mkdir -p $(DIR_O)/builtin/fc
	@mkdir -p $(DIR_O)/builtin/cd
	@mkdir -p $(DIR_O)/libft_42
	@mkdir -p $(DIR_O)/libft_42/stack_structure
	gcc $(FLAGS) -c -I includes -o $@ $<

clean:
	@echo "\033[34mDeleting 42sh o-files\033[0m"
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@echo "\033[34mDeleting 42sh binary\033[0m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re:		fclean all

.PHONY: all fclean clean re
