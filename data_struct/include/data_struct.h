/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:01:00 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 23:16:36 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

// ###########################################################################
// #  UTILS
// ###########################################################################
int						_alloc(void **target, size_t size);
void					_clean(void *target, size_t size);
void					*ft_memset(void *s, int c, size_t n);
void					ft_putstr_fd(char *str, int fd);
void					ft_free_arr(char **arr);
size_t					ft_strlen(const char *s);
// ###########################################################################
// #  DOUBLE LINKED LIST
// ###########################################################################
struct s_dll;

typedef struct s_dnode
{
	char				*key;
	char				*value;
	struct s_dnode		*next;
	struct s_dnode		*prev;
} t_node, *t_pnode;

typedef struct s_dll
{
	struct s_dnode		*top;
	struct s_dnode		*bot;
	int					size;
} t_dll, *t_pdll;

t_pdll					_dll_clear(t_pdll dll);
t_pdll					_dll_pop_back(t_pdll dll);
t_pdll					_dll_pop_front(t_pdll dll);
t_pdll					_dll_pop_in(t_pdll dll, t_pnode target);
void					_dll_print_env(t_pdll dll);
void					_dll_print(t_pdll dll);
t_pdll					_dll_push_back(t_pdll dll, char *value);
t_pdll					_dll_push_front(t_pdll dll, char *value);
t_pdll					_dll_push_in(t_pdll dll, t_pnode target, char *value);
// ###########################################################################
// #  DOUBLE LINKED LIST TOKENS
// ###########################################################################
struct s_dll_tok;

typedef struct s_tok
{
	char				*value;
	char				type;
	bool				join;
	struct s_dll_tok	*tokens;
	struct s_tok		*next;
	struct s_tok		*prev;
} t_tok, *t_ptok;

typedef struct s_dll_tok
{
	t_tok				*top;
	t_tok				*bot;
	int					size;
} t_dll_tok, *t_pdll_tok;

t_pdll_tok				_tok_dll_clear(t_pdll_tok dll);
t_pdll_tok				_tok_dll_pop_back(t_pdll_tok dll);
void					_tok_dll_print(t_pdll_tok dll);
t_pdll_tok				_tok_dll_push_back(t_pdll_tok dll, char *value);
// ###########################################################################
// #  DOUBLE LINKED LIST BLOCS
// ###########################################################################
struct s_dll_blc;

typedef struct s_blc
{
	char				*value;
	char				**cmds;
	char				operator;
	pid_t				pid;
	int					status;
	int					fd[2];
	int					pfd[2];
	struct s_blc		*next;
	struct s_blc		*prev;
	struct s_dll_blc	*blocs;
} t_blc, *t_pblc;

typedef struct s_dll_blc
{
	t_blc				*top;
	t_blc				*bot;
	int					size;
} t_dll_blc, *t_pdll_blc;

t_pdll_blc				_blc_dll_clear(t_pdll_blc dll);
t_pdll_blc				_blc_dll_pop_back(t_pdll_blc dll);
void					_blc_dll_print(t_pdll_blc dll);
t_pdll_blc				_blc_dll_push_back(t_pdll_blc dll, char *value);
// ###########################################################################
// #  BINARY TREE BLOCS
// ###########################################################################
typedef struct s_bt_blc
{
	char				**cmds;
	char				operator;
	pid_t				pid;
	int					status;
	int					fd[2];
	int					pfd[2];
	struct s_bt_blc		*left;
	struct s_bt_blc		*root;
	struct s_bt_blc		*right;
} t_bt_blc, *t_pbt_blc;

t_pbt_blc				_blc_bt_create(void);
void					_blc_bt_clear(t_pbt_blc root);
int						_blc_bt_size(t_pbt_blc root);
t_pbt_blc				_blc_bt_join(t_pbt_blc tree, t_pbt_blc left,
							t_pbt_blc right);
// ###########################################################################
// #  BINARY TREE TOKENS
// ###########################################################################
typedef struct s_bt_tok
{
	char				*value;
	char				type;
	bool				join;
	struct s_bt_tok		*left;
	struct s_bt_tok		*root;
	struct s_bt_tok		*right;
} t_bt_tok, *t_pbt_tok;

t_pbt_tok				_tok_bt_create(char *value, char type);
t_pbt_tok				_tok_bt_push(t_pbt_tok tree, t_pbt_tok node, bool side);
t_pbt_tok				_tok_bt_join(t_pbt_tok tree, t_pbt_tok left,
							t_pbt_tok right);
void					_tok_bt_clear(t_pbt_tok tree);
void					_tok_bt_print(t_pbt_tok tree, bool prefix);
int						_tok_bt_size(t_pbt_tok tree);
// ###########################################################################
// #  GRAPH
// ###########################################################################
typedef struct s_gnode
{
	int					value;
	struct s_gnode		*next;
} t_gnode, *t_pgnode;

typedef struct s_adjlist
{
	t_pgnode			top;
} t_adjlist, *t_padjlist;

typedef struct s_graph
{
	bool				sens;
	int					vertices;
	t_padjlist			adjlist;
	FILE				*graph_file;
} t_graph, *t_pgraph;

t_pgraph				_graph_create(int vertices, bool sens);
void					_graph_clear(t_pgraph graph);
void					_graph_add_edge(t_pgraph graph, int src, int dst);
void					_graph_print(t_pgraph graph);
void					_graph_display(t_pgraph graph);
t_pgnode				_node_add(int value);
// ###########################################################################
// #  EXIT CODES
// ###########################################################################
# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif // EXIT_SUCCESS
# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif // EXIT_FAILURE
# ifndef EXIT_ERROR
#  define EXIT_ERROR -1
# endif // EXIT_ERROR
# ifndef ALLOC_FAIL
#  define ALLOC_FAIL "allocation failed\n"
# endif // ALLOC_FAIL
// ###########################################################################
#endif // DATA_STRUCT_H