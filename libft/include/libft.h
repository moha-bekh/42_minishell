/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:41:33 by ajordan-          #+#    #+#             */
/*   Updated: 2024/08/21 16:31:33 by mbekheir         ###   ########.fr       */
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

/* FT_FREE */
void				ft_free_arr(char **arr);
void				ft_free_arrr(char ***arrr);
void				ft_free_tab(int **tab, int size);

/* FT_IS */
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
bool				ft_isspace(int c);
int					ft_ishex_alpha(int c);
int					ft_ishexALPHA(int c);

/* FT_LST */
# ifndef BF
#  define BF 4096
# endif

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}					t_list;

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
//
/* FT_MEM */
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_memswap(void *const a, void *const b, size_t size);

/* FT_PRINTF */
int					ft_printf(const char *str, ...);

/* FT_PRINTF_UTILS */
int					ft_print_char(char c);
int					ft_print_hex(unsigned int nb, const char format);
int					ft_print_nbr(int nb);
int					ft_print_ptr(unsigned long long ptr);
int					ft_print_str(char *str);
int					ft_print_unsigned(unsigned int nb);
void				ft_putchar(char c);
void				ft_putstr(char *str);

/* M_PRINTF */
int					m_printfd(int fd, const char *format, ...);
void				m_print_char(int fd, char c, int *len);
void				m_print_str(int fd, char *str, int *len);
void				m_print_nbr(int fd, int nbr, int *len);
void				m_print_unsigned(int fd, unsigned int unbr, int *len);
void				m_print_hex(int fd, unsigned int unbr, const char format,
						int *len);
void				m_print_ptr(int fd, unsigned long long ptr, int *len);

/* FT_PUT */
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

/* FT_STR */
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

/* FT_TO */
int					ft_atoi(const char *str);
int					ft_atol(const char *nptr);
char				*ft_itoa(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_swap(int *a, int *b);
int					ft_atoi_base(const char *str, int base);

/* SORT */
void				quick_sort(int *tab, int start, int end);

/* get_next_line */
char				*get_next_line(int fd, t_list **lst);
void				read_and_stock(int fd, t_list **lst);
void				add_to_list(t_list **lst, char *buf, int readed);
void				extract_line(t_list *lst, char **line);
bool				clean_list(t_list **lst);

int					is_new_line(t_list *lst);
t_list				*get_last_node(t_list *lst);
void				generate_line(t_list *lst, char **line);
void				free_list(t_list *lst);
size_t				ft_strlen(const char *s);

/* ft_dprintf */
# define FT_DPRINTF_BUFF_SIZE 4096

typedef struct s_ft_dprintf
{
	int				fd;
	const char		*format;
	va_list			args;
	char			buf[FT_DPRINTF_BUFF_SIZE];
	int				len;
	int				i;
	int				j;
} t_ft_dprintf, *t_ft_pdprintf;

int					ft_dprintf(int fd, const char *format, ...);
void				ft_putchar_buf(t_ft_pdprintf d, char c);
void				ft_putstr_buf(t_ft_pdprintf d, char *str);

#endif /* LIBFT_H */