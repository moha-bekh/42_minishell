/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:41:33 by ajordan-          #+#    #+#             */
/*   Updated: 2024/10/23 02:38:59 by mbekheir         ###   ########.fr       */
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

typedef struct s_list t_list, *t_plist,		**t_pplist; // SIMPLE LIST
typedef struct s_adlst t_adlst, *t_padlst,	**t_ppadlst; // DOUBLE LIST MANAGER
typedef struct s_nlst t_nlst, *t_pnlst,		**t_ppnlst; // DOUBLE LIST NODE
typedef struct s_btree t_btree, *t_pbtree,	**t_ppbtree; // BINARY TREE
typedef struct s_ncmd t_ncmd, *t_pncmd,		**t_ppncmd; // CMD LIST
typedef struct s_ft_dprintf t_fd_dprintf,	*t_ft_pdprintf; // FT_DPRINTF

/* ALLOC && FREE */
int					_alloc(void **target, size_t size);
void				ft_free_arr(char **arr);
void				ft_free_arrr(char ***arrr);
void				ft_free_tab(int **tab, int size);

/* BINARY TREE */
void				_bt_clear(t_ppbtree node);
t_pbtree			_bt_create(t_pnlst token);
t_pbtree			_bt_join(t_pbtree left, t_pnlst token, t_pbtree right);
void				_bt_print(t_pbtree node, int i);
void				_bt_push_left(t_ppbtree node, t_pbtree new);
void				_bt_push_right(t_ppbtree node, t_pbtree new);
void				_bt_push_root(t_ppbtree node, t_pbtree new);

/* CMD LIST */
void				_cmd_push_back(t_ppadlst dlst, t_pnlst token);
void				_cmd_pop_back(t_ppadlst dlst);
void				_cmd_clear(t_ppadlst dlst);
void				_cmd_print_line(t_pncmd cmd);
void				_cmd_print_all(t_padlst dlst);

/* DOUBLE LIST */
t_pnlst				_dlst_new_node(void);
t_padlst			_dlst_new_manager(void);
void				_dlst_merge_nodes(t_padlst dlst, t_pnlst prev, t_pnlst node,
						t_pnlst next);
void				_dlst_push_before(t_ppadlst dlst, t_pnlst node,
						void *addr_1, void *addr_2);
void				_dlst_push_after(t_ppadlst dlst, t_pnlst node, void *addr_1,
						void *addr_2);

void				_dlst_push_front(t_ppadlst dlst, void *addr_1, void *addr_2,
						int x);
void				_dlst_push_back(t_ppadlst dlst, void *addr_1, void *addr_2,
						int x);
void				_dlst_pop_front(t_ppadlst dlst);
void				_dlst_pop_back(t_ppadlst dlst);
void				_dlst_pop_in(t_ppadlst dlst, t_ppnlst node);
void				_dlst_clear(t_ppadlst dlst);
void				_dlst_sort(t_ppadlst dlst, bool reverse);

/* SIMPLE LIST */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

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

/* FT_DPRINTF */
# define FT_DPRINTF_BUFF_SIZE 4096

int					ft_dprintf(int fd, const char *format, ...);
void				ft_putchar_buf(t_ft_pdprintf d, char c);
void				ft_putstr_buf(t_ft_pdprintf d, char *str);

/* FT_IS */
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
bool				ft_isspace(int c);
int					ft_ishex_alpha(int c);
int					ft_ishex_alpha_(int c);

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
int					ft_print_char(char c);
int					ft_print_hex(unsigned int nb, const char format);
int					ft_print_nbr(int nb);
int					ft_print_ptr(unsigned long long ptr);
int					ft_print_str(char *str);
int					ft_print_unsigned(unsigned int nb);
void				ft_putchar(char c);
void				ft_putstr(char *str);

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

typedef struct s_list
{
	char			*value;
	struct s_list	*next;
}					t_list;
// get_next_line
char				*get_next_line(int fd);
void				read_and_stock(int fd, t_list **line_list);
void				add_to_list(t_list **line_list, char *buf, int readed);
void				extract_line(t_list *line_list, char **line);
void				clean_list(t_list **line_list);
// get_next_line_utils
int					is_new_line(t_list *line_list);
t_list				*get_last_node(t_list *line_list);
void				generate_line(t_list *line_list, char **line);
void				free_list(t_list *line_list);
size_t				ft_strlen(const char *s);

/* SORT */
void				quick_sort(int *tab, int start, int end);

struct				s_btree
{
	struct s_btree	*root;
	struct s_btree	*left;
	struct s_btree	*right;
	t_pnlst			token;
	t_padlst		cmd_line;
};

struct				s_nlst
{
	t_padlst		manager;
	t_pnlst			next;
	t_pnlst			prev;
	void			*addr_1;
	void			*addr_2;
	int				x;
	bool			flag;
};

struct				s_redir
{
	char			*in_name;
	char			*out_name;
	char			*here_name;

	int				pfd[2];
	int				fd[2];

	bool			in_access;
	bool			out_access;
	bool			out_trunc;
	bool			out_inside;
	bool			here_inside;
	bool			is_here_doc;
	bool			xpd_hd;
};

struct				s_ncmd
{
	t_padlst		manager;
	t_pncmd			next;
	t_pncmd			prev;
	t_pnlst			token;
	char			**args;
	char			*path;
	struct s_redir	redirs;
	pid_t			pid;
};

struct				s_adlst
{
	union
	{
		struct
		{
			t_pnlst	d_top;
			t_pnlst	d_bot;
			int		d_size;
		};
		struct
		{
			t_pncmd	c_top;
			t_pncmd	c_bot;
			int		c_size;
		};
	};
};

struct				s_ft_dprintf
{
	int				fd;
	const char		*format;
	va_list			args;
	char			buf[FT_DPRINTF_BUFF_SIZE];
	int				len;
	int				i;
	int				j;
};

#endif /* LIBFT_H */