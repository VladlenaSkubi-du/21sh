/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:31:24 by sschmele          #+#    #+#             */
/*   Updated: 2020/07/31 12:00:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>

# include "ft_printf.h"

# define GNL_CLEAN		-42

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_stack
{
	int					data;
	struct s_stack		*next;
}						t_stack;

typedef struct			s_avltree
{
	char				*key;
	void				*value;
	struct s_avltree	*right;
	struct s_avltree	*left;
}						t_avltree;

typedef struct			s_list_fd
{
	int					fd;
	t_list				*buf;
	int					index;
	int					end;
	struct s_list_fd	*next;
}						t_fd_list;

/*
** Folder ARROW_FUNCTIONS
**_____________________________________________________________________________
*/

void					ft_arrdel(char **arr);
char					**ft_realloc_array(char ***subj, int len_subj,
							int len_needed);
void					ft_delelem_array(char ***array, int len,
							int start, int num);
void					ft_arrshift(char **arr, int size, int shift);
void					**ft_memrealloc_array(void ***subj, int len_subj,
							int len_needed);

/*
** Folder LIST_STRUCTURE
**_____________________________________________________________________________
*/

void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstclear(t_list **begin_list);
void					ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void					ft_lstdelcont(void *content, size_t size);
void					ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstlast(t_list **begin_list);
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstadd_to_end(t_list **start,
							t_list *new_list);
int						ft_lstsize(t_list *begin_list);
void					ft_lstadd_after(t_list **current, t_list *new);
int						ft_lstfree_after(t_list **current);
int						ft_lstfree_current(t_list **head);
void					ft_lstfree(t_list **head);

/*
** Folder TREE_FUNCTIONS
**_____________________________________________________________________________
*/

t_avltree				*ft_treeinit_leaf(char *key);
int						ft_treeadd_leaf(t_avltree **root,
							t_avltree	*new_leaf, int *len);
int						ft_treefill_array(t_avltree **root, char **list,
							int *len, int *max);
void					ft_treefree(t_avltree **root);

/*
** Folder MALLOC_FUNCTIONS
**_____________________________________________________________________________
*/

char					*ft_itoa(int ni);
char					*ft_ltoa_base(long nb, int base);
char					*ft_makerevstr(char *s);
void					*ft_memalloc(size_t size);
void					*ft_realloc(void *subj, size_t len_subj,
							size_t len, size_t len_needed);
char					*ft_restrsub(char *s, int start, int len);
char					*ft_strchrnew(char *s, int c);
char					*ft_strdup(const char *s1);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
char					*ft_strndup(const char *s1, size_t n);
char					*ft_strnewsetchar(size_t size, char c);
char					*ft_strrejoin(char *s1, char *s2);
char					*ft_strremerge(char *s1,
							size_t len_s1, char *s2, size_t n);
char					**ft_strsplit(char const *s, char c);
char					*ft_strsub(char const *s,
							unsigned int start, size_t len);
char					*ft_strtrim(char const *s);
char					*ft_utoa_base(unsigned long nb, int base);
char					*ft_strnew(size_t size);
void					*ft_xmalloc(size_t size);
void					ft_strshift(char *str, int shift);

/*
** Folder MEMORY_FUNCTIONS
**_____________________________________________________________________________
*/

void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst,
							const void *src, int c, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					ft_memdel(void **ap);

/*
** Folder OUTPUT_FUNCTIONS
**_____________________________________________________________________________
*/

void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putnbr(int n);
void					ft_putendl(char const *s);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putnstr(char const *s, int len);
void					ft_printmap(char **map, int side);
void					ft_putnendl_fd(char *str, int n, int fd);
void					ft_putnstr_fd(char *str, int n, int fd);

/*
** Folder SORT_FUNCTIONS
**_____________________________________________________________________________
*/

void					ft_bubble_sort(char *s);
void					ft_choice_sort(char *s);
void					ft_insertive_sort(char *s);

/*
** Folder STACK_STRUCTURE
**_____________________________________________________________________________
*/

/*
** User makes his own safety for the pop-stack function because it returns data
** that is int and it is impossible to return some "wrong" int to show the fail
** Maybe one day I rewrite it.
*/

t_stack					*ft_init_stack(void);
int						ft_pop_stack(t_stack **head);
int						ft_push_stack(t_stack **head, int data);
void					ft_clear_stack(t_stack **head);
int						ft_last_stack(t_stack **head);

/*
** Folder STRING_FUNCTIONS
**_____________________________________________________________________________
*/

char					*ft_straddsy(char *dest, char sy);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
int						ft_strchri(char *s, int c);
void					ft_strclr(char *s);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dest, const char *src);
void					ft_strdel(char **as);
int						ft_strequ(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char*));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
size_t					ft_strlenchri(const char *s, char c);
char					*ft_strncat(char *s1, const char *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t len);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
char					*ft_strrchr(const char *s, int c);
int						ft_strrchri(char *s, int c);
char					*ft_strstr(const char *haystack, const char *needle);
int						ft_strchrdiff(const char *s1, const char *s2, char sy);
int						ft_strchrcmp(const char *s1, const char *s2, char x);

/*
** Folder OTHER_FUNCTIONS
**_____________________________________________________________________________
*/

int						ft_atoi(const char *str);
int						ft_atoi_base(char *str, int str_base);
int						ft_isdigit(int c);
int						ft_ishexdigit(char c);
int						ft_isoctdigit(char c);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
long					ft_nb_root(long nb, size_t root);
void					swap_chars(char *cmd, int b, int a);
void					swap_ints(int *a, int *b);
int						ft_issign(char c);
int						ft_gnl(const int fd, char **line);

#endif
