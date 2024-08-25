/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:31:50 by moha              #+#    #+#             */
/*   Updated: 2024/08/25 00:31:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define _PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"

# define _TOKENS "*'\"()$|&<>"
# define _OPERATORS "&|"
# define _SUBSHELL "()"
# define _PIPELINE "|"
# define _REDIRS "<>"
# define _QUOTES "'\""
# define _OTHERS "$*"
# define _SCOPES "(\"'"
# define _JOINERS "\"'$*"

# define _STX_OP "AOP"

# define _ERR_TOKEN "bash: syntax error near unexpected token `%s'\n"
# define _ERR_CLOSE "bash: syntax error a token field `%c' is not closed\n"
# define _ERR_NEWLINE "bash: syntax error near unexpected token `newline'\n"
# define _ERR_NOT_FOUND "bash: %s: command not found\n"

# define _TYP_SEP "AO()"
# define _TYP_REDIRS "<>HN"

enum					e_tokens
{
	_AND = 'A',
	_OR = 'O',
	_SUB = 'S',
	_WORD = 'W',
	_PIPE = 'P',
	_REDIR_OUTA = 'N',
	_HERE_DOC = 'H'
};

enum					e_return
{
	_EXT_DUP2 = -15,
	_EXT_DUP = -14,
	_EXT_EXEC = -13,
	_EXT_PIPE = -12,
	_EXT_FORK = -11,
	_EXT_OPEN = -10,

	_SYNTAX = -3,
	_ALLOC = -2,
	_ERROR = -1,
	_SUCCESS = 0,
	_FAILURE = 1
};

/* GENERIC LINKED LIST */
typedef struct s_nlst t_nlst, *t_pnlst;
typedef struct s_adllst u_adllst, *u_padllst;
/* CMD BTREE */
typedef struct s_btree t_btree, *t_pbtree;
/* CMD LIST && REDIR STRUCT */
typedef struct s_redir t_redir, *t_predir;
typedef struct s_cmd t_cmd, *t_pcmd;
/* DATA STRUCT && ARGS STRUCT */
typedef struct s_args t_args, *t_pargs;
typedef struct s_data t_data, *t_pdata;

struct					s_nlst
{
	void				*addr_1;
	void				*addr_2;
	int					x;
	bool				flag;
	t_pnlst				next;
	t_pnlst				prev;
	u_padllst			manager;
};

struct					s_redir
{
	char				*in_name;
	bool				in_access;
	char				*out_name;
	bool				out_trunc;
	int					fd[2];
	int					pfd[2];
	char				*here_name;
	char				*here_limit;
	int					here_fd;
};

struct					s_cmd
{
	t_pnlst				token;
	char				**args;
	char				*path;
	t_redir				redirs;
	pid_t				pid;
	t_pcmd				next;
	t_pcmd				prev;
	u_padllst			manager;
};

struct					s_adllst
{
	union
	{
		struct
		{
			t_pnlst		d_top;
			t_pnlst		d_bot;
			int			d_size;
		};
		struct
		{
			t_pcmd		c_top;
			t_pcmd		c_bot;
			int			c_size;
		};
	};
};

struct					s_btree
{
	t_pnlst				token;
	u_padllst			cmd_line;
	struct s_btree		*root;
	struct s_btree		*left;
	struct s_btree		*right;
};

struct					s_args
{
	int					ac;
	char				**av;
	char				**env;
	char				**env_path;
	char				**hard_path;
	char				*pwd;
	char				*old_pwd;
	int					_stdin;
	int					_stdout;
};

struct					s_data
{
	char				*prompt;
	t_args				args;
	u_padllst			builtins;
	u_padllst			env;
	u_padllst			export;
	u_padllst			tokens;
	t_pbtree			tree;
	int					_errno;
	struct sigaction	s_sig;
};

extern int				*_ptr_errno;

/* UTILS */
int						_alloc(void **target, size_t size);
int						_get_start_index(char *str);
int						_path_slash(t_pdata data);
int						is_overflow(char *str);
char					*get_random_name(void);
int						_count_args(t_pnlst token);

/* SIGNALS */
int						_set_signals(t_pdata data);
void					child_hndl(int sig);
void					sig_hndl(int sig);

/* DATA */
int						_data_init(t_pdata data, int ac, char **av, char **ev);
t_pdata					get_data(void);
int						_data_clear(t_pdata data);
int						_data_structs_clear(t_pdata data);

/* ENV */
void					_data_init_env_n_export(t_pdata data);

/* CHECK */
int						_check_prompt(t_pdata data);

/* TOKENS */
int						_token_list(t_pdata data);
int						_op_proc(t_pdata data, int *i);
int						_redir_proc(t_pdata data, int *i);
int						_token_id(char a, char *str);

/* TREE */
t_pbtree				_tree_builder(t_pdata data);

/* EXEC */
int						_resolve_path(t_pdata data, t_pcmd *cmd);

/* EXPAND */
// functions prototypes

/* PARSING */
int						_pars_pipe_lines(t_pbtree *node);
int						_pars_args_line(t_pcmd *cmd);
int						_pars_redirs(t_pcmd *cmd, t_pnlst token);

/* BUILTINS */
int						_echo(t_pdata data, t_pcmd *cmd);
int						_env(t_pdata data, t_pcmd *cmd);
int						_exit_(t_pdata data, t_pcmd *cmd);
int						_export(t_pdata data, t_pcmd *cmd);
int						_pwd(void);
int						_unset(t_pdata data, t_pcmd *cmd);

/* BINARY TREE */
void					_bt_clear(t_pbtree *node);
t_pbtree				_bt_create(t_pnlst token);
t_pbtree				_bt_join(t_pbtree left, t_pnlst token, t_pbtree right);
void					_bt_print(t_pbtree node, int i);
void					_bt_push_left(t_pbtree *node, t_pbtree new);
void					_bt_push_right(t_pbtree *node, t_pbtree new);
void					_bt_push_root(t_pbtree *node, t_pbtree new);

/* GENERIC LINKED LIST */
void					_dllst_push_front(u_padllst *dllst, void *addr_1,
							void *addr_2, int x);
void					_dllst_push_back(u_padllst *dllst, void *addr_1,
							void *addr_2, int x);
void					_dllst_push_in(u_padllst *dllst, t_pnlst node,
							void *addr_1, void *addr_2);

void					_dllst_pop_front(u_padllst *dllst);
void					_dllst_pop_back(u_padllst *dllst);
void					_dllst_pop_in(u_padllst *dllst, t_pnlst *node);

void					_dllst_clear(u_padllst *dllst);

void					_dllst_print_builtins(u_padllst dllst);
void					_dllst_print_env(u_padllst dllst);
void					_dllst_print_export(u_padllst dllst);
void					_dllst_print_tokens(u_padllst dllst);

void					_dllst_sort(u_padllst *dllst, bool reverse);

/* CMD LIST */
void					_cmd_push_back(u_padllst *dllst, t_pnlst token);
void					_cmd_pop_back(u_padllst *dllst);
void					_cmd_clear(u_padllst *dllst);
void					_cmd_print_line(t_pcmd cmd);
void					_cmd_print_all(u_padllst dllst);

# define WHITE "\033[0;97m"
# define RESET "\033[0;39m"

# define CYAN "\033[0;96m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"

# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define RED "\033[0;91m"

#endif /* MINISHELL_H */