# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/04 16:34:17 by sschmele          #+#    #+#              #
#    Updated: 2020/08/07 22:13:39 by sschmele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror
FLAGS += -g
	
ARROW_FUNCTIONS = ./arrow_functions/ft_arrdel.c \
	./arrow_functions/ft_realloc_array.c \
	./arrow_functions/ft_delelem_array.c \
	./arrow_functions/ft_arrshift.c \
	./arrow_functions/ft_memrealloc_array.c
	
LIST_STRUCTURE = ./list_structure/ft_lstadd.c \
	./list_structure/ft_lstclear.c \
	./list_structure/ft_lstdel.c \
	./list_structure/ft_lstdelcont.c \
	./list_structure/ft_lstdelone.c \
	./list_structure/ft_lstiter.c \
	./list_structure/ft_lstlast.c \
	./list_structure/ft_lstmap.c \
	./list_structure/ft_lstnew.c \
	./list_structure/ft_lstadd_to_end.c \
	./list_structure/ft_lstsize.c \
	./list_structure/ft_lstadd_after.c \
	./list_structure/ft_lstfree_after.c \
	./list_structure/ft_lstfree_current.c \
	./list_structure/ft_lstfree.c

TREE_FUNCTIONS = $(AVL_TREE)

AVL_TREE = ./tree_functions/avl_tree/ft_treeinit_leaf.c \
	./tree_functions/avl_tree/ft_treeadd_leaf.c \
	./tree_functions/avl_tree/ft_treefill_array.c \
	./tree_functions/avl_tree/ft_treefree.c

MALLOC_FUNCTIONS = ./malloc_functions/ft_itoa.c \
	./malloc_functions/ft_ltoa_base.c \
	./malloc_functions/ft_makerevstr.c \
	./malloc_functions/ft_memalloc.c \
	./malloc_functions/ft_realloc.c \
	./malloc_functions/ft_restrsub.c \
	./malloc_functions/ft_strchrnew.c \
	./malloc_functions/ft_strdup.c \
	./malloc_functions/ft_strjoin.c \
	./malloc_functions/ft_strmap.c \
	./malloc_functions/ft_strmapi.c \
	./malloc_functions/ft_strndup.c \
	./malloc_functions/ft_strnewsetchar.c \
	./malloc_functions/ft_strrejoin.c \
	./malloc_functions/ft_strremerge.c \
	./malloc_functions/ft_strsplit.c \
	./malloc_functions/ft_strsub.c \
	./malloc_functions/ft_strtrim.c \
	./malloc_functions/ft_utoa_base.c \
	./malloc_functions/ft_strnew.c \
	./malloc_functions/ft_strshift.c \
	./malloc_functions/ft_xmalloc.c

MEMORY_FUNCTIONS = ./memory_functions/ft_bzero.c \
	./memory_functions/ft_memccpy.c \
	./memory_functions/ft_memchr.c \
	./memory_functions/ft_memcmp.c \
	./memory_functions/ft_memcpy.c \
	./memory_functions/ft_memdel.c \
	./memory_functions/ft_memmove.c \
	./memory_functions/ft_memset.c

OTHER_FUNCTIONS = ./other_functions/ft_atoi.c \
	./other_functions/ft_atoi_base.c \
	./other_functions/ft_gnl.c \
	./other_functions/ft_isalnum.c \
	./other_functions/ft_isalpha.c \
	./other_functions/ft_isascii.c \
	./other_functions/ft_isdigit.c \
	./other_functions/ft_ishexdigit.c \
	./other_functions/ft_isoctdigit.c \
	./other_functions/ft_isprint.c \
	./other_functions/ft_issign.c \
	./other_functions/ft_nb_root.c \
	./other_functions/ft_tolower.c \
	./other_functions/ft_toupper.c \
	./other_functions/swap_chars.c \
	./other_functions/swap_ints.c
	
OUTPUT_FUNCTIONS = ./output_functions/ft_putnstr.c \
	./output_functions/ft_printmap.c \
	./output_functions/ft_putchar_fd.c \
	./output_functions/ft_putchar.c \
	./output_functions/ft_putendl_fd.c \
	./output_functions/ft_putendl.c \
	./output_functions/ft_putnbr_fd.c \
	./output_functions/ft_putnbr.c \
	./output_functions/ft_putnstr_fd.c \
	./output_functions/ft_putenendl_fd.c \
	./output_functions/ft_putstr_fd.c \
	./output_functions/ft_putstr.c

SORT_FUNCTIONS = ./sort_functions/ft_bubble_sort.c \
	./sort_functions/ft_choice_sort.c \
	./sort_functions/ft_insertive_sort.c

STACK_STRUCTURE = ./stack_structure/ft_clear_stack.c \
	./stack_structure/ft_init_stack.c \
	./stack_structure/ft_last_stack.c \
	./stack_structure/ft_pop_stack.c \
	./stack_structure/ft_push_stack.c

STRING_FUNCTIONS = ./string_functions/ft_straddsy.c \
	./string_functions/ft_strcat.c \
	./string_functions/ft_strchr.c \
	./string_functions/ft_strchri.c \
	./string_functions/ft_strclr.c \
	./string_functions/ft_strcmp.c \
	./string_functions/ft_strcpy.c \
	./string_functions/ft_strdel.c \
	./string_functions/ft_strequ.c \
	./string_functions/ft_striter.c \
	./string_functions/ft_striteri.c \
	./string_functions/ft_strlcat.c \
	./string_functions/ft_strlen.c \
	./string_functions/ft_strlenchri.c \
	./string_functions/ft_strncat.c \
	./string_functions/ft_strncmp.c \
	./string_functions/ft_strncpy.c \
	./string_functions/ft_strnequ.c \
	./string_functions/ft_strnstr.c \
	./string_functions/ft_strrchr.c \
	./string_functions/ft_strrchri.c \
	./string_functions/ft_strstr.c \
	./string_functions/ft_strchrdiff.c \
	./string_functions/ft_strchrcmp.c

SRCS =	$(ARROW_FUNCTIONS) \
	$(LIST_STRUCTURE) \
	$(TREE_FUNCTIONS) \
	$(MALLOC_FUNCTIONS) \
	$(MEMORY_FUNCTIONS) \
	$(OUTPUT_FUNCTIONS) \
	$(SORT_FUNCTIONS) \
	$(STACK_STRUCTURE) \
	$(STRING_FUNCTIONS) \
	$(OTHER_FUNCTIONS)

DIR_O = objs

LIB_INCLUDE_DIR = includes
INCLUDE = $(LIB_INCLUDE_DIR)/libft.h

OBJS = $(addprefix $(DIR_O)/,$(SRCS:.c=.o))

#_____________________________________________________

all:	$(NAME)

$(NAME):	$(OBJS) ft_printf/includes/ft_printf.h
	@echo "\033[32;01mCompiling libft...\033[0m"
	@make -C ./ft_printf
	@cp ft_printf/libftprintf.a $(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[32;01mLibft.a is ready.\033[0m"

$(OBJS):	$(DIR_O)/%.o: %.c $(INCLUDE)
#_____________________________________________________
	@mkdir -p $(DIR_O)
	@mkdir -p $(DIR_O)/arrow_functions
	@mkdir -p $(DIR_O)/list_structure
#_____________________________________________________
	@mkdir -p $(DIR_O)/tree_functions
	@mkdir -p $(DIR_O)/tree_functions/avl_tree
#_____________________________________________________
	@mkdir -p $(DIR_O)/malloc_functions
	@mkdir -p $(DIR_O)/memory_functions
	@mkdir -p $(DIR_O)/other_functions
	@mkdir -p $(DIR_O)/output_functions
	@mkdir -p $(DIR_O)/sort_functions
	@mkdir -p $(DIR_O)/stack_structure
	@mkdir -p $(DIR_O)/string_functions
#_____________________________________________________
	@gcc $(FLAGS) -c -I $(LIB_INCLUDE_DIR) -o $@ $<

clean:
	@echo "\033[34mDeleting libft o-files\033[0m"
	@make clean --directory ./ft_printf
	@/bin/rm -rf $(DIR_O)

fclean:	clean
	@echo "\033[34mDeleting libft.a\033[0m"
	@make fclean --directory ./ft_printf
	@/bin/rm -f $(NAME)

re: 	fclean all

.PHONY: all text clean fclean
