/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:41:33 by ajordan-          #+#    #+#             */
/*   Updated: 2024/08/07 20:36:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BF
#  define BF 100
# endif

# define RET_OK 0
# define RET_KO 1
# define RET_ERR -1
# define EXIT_ERROR -1

# define ALLOC_KO -10
# define ALLOC_FAIL "Error: Allocation failed\n"

# define IT_IS 1
# define IS_NT 0

typedef struct s_btree
{
	void			*value;
	struct s_btree	*left;
	struct s_btree	*parent;
	struct s_btree	*right;
}					t_btree;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}					t_list;

struct s_dll;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	char			*key;
	char			*value;
}					t_node;
// STRUCTURE LINKED LIST
typedef struct s_dll
{
	struct s_node	*top;
	struct s_node	*bot;
	int				size;
}					t_dll;

// FT_FREE
void				ft_free(void *ptr);
void				ft_free_arr(char **arr);
void				ft_free_arrr(char ***arrr);
void				ft_free_tab(int **tab, int size);
// FT_IS
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
bool				ft_isspace(int c);
int					ft_ishex_alpha(int c);
int					ft_ishexALPHA(int c);
// FT_LST
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				lst_push_top(t_list **lst, void *value);
void				lst_push_bot(t_list **lst, void *value);
void				lst_pop_top(t_list **lst);
t_list				*lst_last_prev(t_list *lst);
void				lst_clear(t_list *lst);
// FT_MEM
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_memswap(void *const a, void *const b, size_t size);
// FT_PRINTF
int					ft_printf(const char *str, ...);
// FT_PRINTF_UTILS
int					ft_print_char(char c);
int					ft_print_hex(unsigned int nb, const char format);
int					ft_print_nbr(int nb);
int					ft_print_ptr(unsigned long long ptr);
int					ft_print_str(char *str);
int					ft_print_unsigned(unsigned int nb);
void				ft_putchar(char c);
void				ft_putstr(char *str);
// M_PRINTF
int					ft_printfd(int fd, const char *format, ...);
// void				ft_print_char(int fd, char c, int *len);
// void				ft_print_str(int fd, char *str, int *len);
// void				ft_print_nbr(int fd, int nbr, int *len);
// void				ft_print_unsigned(int fd, unsigned int unbr, int *len);
// void				ft_print_hex(int fd, unsigned int unbr, const char format,
// 						int *len);
// void				ft_print_ptr(int fd, unsigned long long ptr, int *len);
// FT_PUT
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
// FT_STR
char				**ft_split(char const *str, char c);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr_in(char *str, char *to_ad, char target);
// FT_TO
int					ft_atoi(const char *str);
int					ft_atol(const char *nptr);
char				*ft_itoa(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_swap(int *a, int *b);
int					ft_atoi_base(const char *str, int base);
// SORT
void				quick_sort(int *tab, int start, int end);

// get_next_line
char				*get_next_line(int fd, t_list **lst);
void				read_and_stock(int fd, t_list **lst);
void				add_to_list(t_list **lst, char *buf, int readed);
void				extract_line(t_list *lst, char **line);
bool				clean_list(t_list **lst);
// get_next_line_utils
int					is_new_line(t_list *lst);
t_list				*get_last_node(t_list *lst);
void				generate_line(t_list *lst, char **line);
void				free_list(t_list *lst);
size_t				ft_strlen(const char *s);

// NODE
t_node				*node_new(void);
t_node				*node_create(void);
bool				node_empty(t_node *node);
// DLL
t_dll				*dll_bot_pop(t_dll *dll);
t_dll				*dll_bot_push(t_dll *dll, void *value);
void				*dll_bot_value(t_dll *dll);
t_dll				*dll_clear(t_dll *dll);
t_dll				*dll_create(void);
bool				dll_empty(t_dll *dll);
t_dll				*dll_new(void);
void				dll_ptr(t_dll *dll);
void				dll_int(t_dll *dll);
void				dll_str(t_dll *dll);
void				dll_char(t_dll *dll);
void				dll_print(t_dll *dll, void (*f)(t_dll *));
int					dll_size(t_dll *dll);
t_dll				*dll_top_pop(t_dll *dll);
t_dll				*dll_top_push(t_dll *dll, void *value);
void				*dll_top_value(t_dll *dll);

t_btree				*btree_create(void *value);
void				btree_clear(t_btree *btree);
t_btree				*btree_join(t_btree *left, t_btree *right, void *value);
void				btree_ptr(t_btree *btree, bool prefix);
void				btree_str(t_btree *btree, bool prefix);
void				btree_char(t_btree *btree, bool prefix);
int					btree_size(t_btree *btree);

void				btree_print(t_btree *btree, void (*in_type)(t_btree *btree,
							bool prefix, int tab), bool prefix);
void				btree_int(t_btree *btree, bool prefix, int tab);

void				print_tab(int tab);
void				print_parent(t_btree *btree);

#endif