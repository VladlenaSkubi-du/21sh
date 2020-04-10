NAME = 21sh

SRCS_DIR = srcs

READLINE_DIR = readline
AUTO_COMPLETION = auto_completion
HISTORY = history
KEY_ACTIONS = key_actions
READLINE_SIMPLE = readline_simple

PARSER_DIR = parser
ASSIGNMENT = assignment
EXEC = exec
PATH_TREE_ORDER = path_tree_order
QUOTING = QUOTING
REDIRECTIONS = redirection
SUBSTITUTION = substitution

BUILTIN_DIR = builtin
CD = cd
FC = fc

GLOBAL_DIR = global
SHELL_VARIABLES = shell_variables
UNIX_FUNCTIONS = unix_functions

SRCS_READLINE = $(wildcard $(SRCS_DIR)/$(READLINE_DIR)/*.c)
SRCS_AUTOCOMPL = $(wildcard $(SRCS_DIR)/$(READLINE_DIR)/$(AUTO_COMPLETION)/*.c)
SRCS_HISTORY = $(wildcard $(SRCS_DIR)/$(READLINE_DIR)/$(HISTORY)/*.c)
SRCS_KEYS = $(wildcard $(SRCS_DIR)/$(READLINE_DIR)/$(KEY_ACTIONS)/*.c)
SRCS_RSIMPLE = $(wildcard $(SRCS_DIR)/$(READLINE_DIR)/$(READLINE_SIMPLE)/*.c)

SRCS_PARSER = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/*.c)
SRCS_ASSIGN = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/$(ASSIGNMENT)/*.c)
SRCS_EXEC = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/$(EXEC)/*.c)
SRCS_PATHTREE = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/$(PATH_TREE_ORDER)/*.c)
SRCS_QUOTE = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/$(QUOTING)/*.c)
SRCS_REDIR = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/$(REDIRECTIONS)/*.c)
SRCS_SUBST = $(wildcard $(SRCS_DIR)/$(PARSER_DIR)/$(SUBSTITUTION)/*.c)

SRCS_BUILTIN = $(wildcard $(SRCS_DIR)/$(BUILTIN_DIR)/*.c)
SRCS_CD = $(wildcard $(SRCS_DIR)/$(BUILTIN_DIR)/$(CD)/*.c)
SRCS_FC = $(wildcard $(SRCS_DIR)/$(BUILTIN_DIR)/$(FC)/*.c)

SRCS_GLOBAL = $(wildcard $(SRCS_DIR)/$(GLOBAL_DIR)/*.c)
SRCS_VARS = $(wildcard $(SRCS_DIR)/$(GLOBAL_DIR)/$(SHELL_VARIABLES)/*.c)
SRCS_FUNCS = $(wildcard $(SRCS_DIR)/$(GLOBAL_DIR)/$(UNIX_FUNCTIONS)/*.c)

SRCS_SHARED = $(wildcard $(SRCS_DIR)/*.c)

OBJS_DIR = obj
OBJS_READLINE = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_READLINE))
OBJS_AUTOCOMPL = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_AUTOCOMPL))
OBJS_HISTORY = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_HISTORY))
OBJS_KEYS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_KEYS))
OBJS_RSIMPLE = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_RSIMPLE))

OBJS_PARSER = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_PARSER))
OBJS_ASSIGN = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_ASSIGN))
OBJS_EXEC = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_EXEC))
OBJS_PATHTREE = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_PATHTREE))
OBJS_QUOTE = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_QUOTE))
OBJS_REDIR = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_REDIR))
OBJS_SUBST = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_SUBST))

OBJS_BUILTIN = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_BUILTIN))
OBJS_CD = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_CD))
OBJS_FC = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_FC))

OBJS_GLOBAL = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_GLOBAL))
OBJS_VARS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_VARS))
OBJS_FUNCS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_FUNCS))

OBJS_SHARED = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS_SHARED))
OBJS = $(OBJS_READLINE) $(OBJS_AUTOCOMPL) $(OBJS_HISTORY) $(OBJS_KEYS) $(OBJS_RSIMPLE) \
	$(OBJS_PARSER) $(OBJS_ASSIGN) $(OBJS_EXEC) $(OBJS_PATHTREE) $(OBJS_QUOTE) $(OBJS_REDIR) $(OBJS_SUBST) \
	$(OBJS_BUILTIN) $(OBJS_CD) $(OBJS_FC) \
	$(OBJS_GLOBAL) $(OBJS_VARS) $(OBJS_FUNCS) \
	$(OBJS_SHARED)

INCLUDE_DIR = includes
BUILTIN_INCLUDE_DIR = $(INCLUDE_DIR)/builtin
SHARED_INCLUDE_DIR = $(INCLUDE_DIR)

LIB_DIR = libft
LIB_INCLUDE = $(LIB_DIR)/includes
LIBFT_PATH = $(LIB_DIR)/libft.a

TERMCAP = -ltermcap

CC_FLAGS = -Wall -Wextra -Werror -g

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

$(OBJS_DIR)/$(READLINE_DIR)/%.o:$(SRCS_DIR)/$(READLINE_DIR)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(READLINE_DIR)/$(AUTO_COMPLETION)/%.o:$(SRCS_DIR)/$(READLINE_DIR)/$(AUTO_COMPLETION)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(READLINE_DIR)/$(HISTORY)/%.o:$(SRCS_DIR)/$(READLINE_DIR)/$(HISTORY)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(READLINE_DIR)/$(KEY_ACTIONS)/%.o:$(SRCS_DIR)/$(READLINE_DIR)/$(KEY_ACTIONS)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(READLINE_DIR)/$(READLINE_SIMPLE)/%.o:$(SRCS_DIR)/$(READLINE_DIR)/$(READLINE_SIMPLE)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<


$(OBJS_DIR)/$(PARSER_DIR)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(PARSER_DIR)/$(ASSIGNMENT)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/$(ASSIGNMENT)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(PARSER_DIR)/$(EXEC)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/$(EXEC)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(PARSER_DIR)/$(PATH_TREE_ORDER)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/$(PATH_TREE_ORDER)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(PARSER_DIR)/$(QUOTING)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/$(QUOTING)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(PARSER_DIR)/$(REDIRECTIONS)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/$(REDIRECTIONS)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(PARSER_DIR)/$(SUBSTITUTION)/%.o:$(SRCS_DIR)/$(PARSER_DIR)/$(SUBSTITUTION)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<


$(OBJS_DIR)/$(BUILTIN_DIR)/%.o:$(SRCS_DIR)/$(BUILTIN_DIR)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(BUILTIN_INCLUDE_DIR) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(BUILTIN_DIR)/$(CD)/%.o:$(SRCS_DIR)/$(BUILTIN_DIR)/$(CD)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(BUILTIN_INCLUDE_DIR) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(BUILTIN_DIR)/$(FC)/%.o:$(SRCS_DIR)/$(BUILTIN_DIR)/$(FC)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(BUILTIN_INCLUDE_DIR) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<


$(OBJS_DIR)/$(GLOBAL_DIR)/%.o:$(SRCS_DIR)/$(GLOBAL_DIR)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(GLOBAL_DIR)/$(SHELL_VARIABLES)/%.o:$(SRCS_DIR)/$(GLOBAL_DIR)/$(SHELL_VARIABLES)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR)/$(GLOBAL_DIR)/$(UNIX_FUNCTIONS)/%.o:$(SRCS_DIR)/$(GLOBAL_DIR)/$(UNIX_FUNCTIONS)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<


$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	gcc $(CC_FLAGS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -o $@ -c $<

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)/$(READLINE_DIR) \
	$(OBJS_DIR)/$(READLINE_DIR)/$(AUTO_COMPLETION) \
	$(OBJS_DIR)/$(READLINE_DIR)/$(HISTORY) \
	$(OBJS_DIR)/$(READLINE_DIR)/$(KEY_ACTIONS) \
	$(OBJS_DIR)/$(READLINE_DIR)/$(READLINE_SIMPLE) \
	$(OBJS_DIR)/$(PARSER_DIR) \
	$(OBJS_DIR)/$(PARSER_DIR)/$(ASSIGNMENT) \
	$(OBJS_DIR)/$(PARSER_DIR)/$(EXEC) \
	$(OBJS_DIR)/$(PARSER_DIR)/$(PATH_TREE_ORDER) \
	$(OBJS_DIR)/$(PARSER_DIR)/$(QUOTING) \
	$(OBJS_DIR)/$(PARSER_DIR)/$(REDIRECTIONS) \
	$(OBJS_DIR)/$(PARSER_DIR)/$(SUBSTITUTION) \
	$(OBJS_DIR)/$(BUILTIN_DIR) \
	$(OBJS_DIR)/$(BUILTIN_DIR)/$(CD) \
	$(OBJS_DIR)/$(BUILTIN_DIR)/$(FC) \
	$(OBJS_DIR)/$(GLOBAL_DIR)/$(SHELL_VARIABLES) \
	$(OBJS_DIR)/$(GLOBAL_DIR)/$(UNIX_FUNCTIONS) \
	$(OBJS_DIR)/$(GLOBAL_DIR)

$(LIBFT_PATH):
	make -C $(LIB_DIR)

$(NAME): $(LIBFT_PATH) $(OBJS_DIR) $(OBJS)
	gcc $(CC_FLAGS) -L $(LIB_DIR) -l ft $(TERMCAP) -o $(NAME) $(OBJS) -I$(LIB_INCLUDE) -I$(SHARED_INCLUDE_DIR) -I$(BUILTIN_INCLUDE_DIR)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)

re: fclean all