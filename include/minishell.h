/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:31:50 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 13:55:28 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

// /* STRUCT TYPES */
typedef struct s_ncmd t_ncmd, *t_pncmd, **t_ppncmd;     // List Command
typedef struct s_adlst t_adlst, *t_padlst, **t_ppadlst; // List Manager
typedef struct s_nlst t_nlst, *t_pnlst, **t_ppnlst;     // List Generic

typedef struct s_btree t_btree, *t_pbtree, **t_ppbtree; // Binary Tree

typedef struct s_redir t_redir, *t_predir; // Struct Redirections
typedef struct s_args t_args, *t_pargs;    // Struct Args
typedef struct s_data t_data, *t_pdata;    // Struct Data

extern int				*_ptr_errno;

/* UTILS */
int						_alloc(void **target, size_t size);
int						_err_print(char *str, void *arg, bool ptr, int _errno);

int						_sep(char *str);
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

/* TOKENS */
int						_tok_list(t_pdata data);
int						_tok_id(char a, char *str);
int						_op_proc(t_pdata data, int *i);
int						_redir_proc(t_pdata data, int *i);

/* TREE */
t_pnlst					_tree_builder(t_ppbtree node, t_pnlst token);

/* EXEC */
int						_exec(t_pdata data, t_ppbtree node);
int						_exec_child_proc(t_pdata data, t_ppncmd cmd);
int						_resolve_path(t_pdata data, t_ppncmd cmd);

int						_exec_builtin_proc(t_pdata data, t_ppncmd cmd);
int						_is_builtin(t_pdata data, char **args);

int						_exec_redirections(t_pdata data, t_ppncmd cmd);
int						_save_stdfds(t_pdata data);
int						_restore_stdfds(t_pdata data);
int						_here_doc_proc(t_ppncmd cmd);

/* EXPAND */
int						_xpd_line(t_ppnlst token);
int						_xpd_wildcards(t_ppnlst token);

/* PARSING */
int						_pars_pipe_lines(t_ppbtree node);
int						_pars_args_line(t_pdata data, t_ppncmd cmd,
							t_ppnlst token, bool inside);
int						_pars_redirs(t_ppncmd cmd, t_ppnlst token, bool inside);

/* BUILTINS */
int						_cd(t_pdata data, char **args);
int						_echo(t_pdata data, char **args);
// int						_echo(t_pdata data, t_pnlst token, char **args);
int						_env(t_pdata data, char **args);
int						_exit_(t_pdata data, char **args);
int						_export(t_pdata data, char **args);
int						_pwd(void);
int						_unset(t_pdata data, char **args);

/* BINARY TREE */
void					_bt_clear(t_ppbtree node);
t_pbtree				_bt_create(t_pnlst token);
t_pbtree				_bt_join(t_pbtree left, t_pnlst token, t_pbtree right);
void					_bt_print(t_pbtree node, int i);
void					_bt_push_left(t_ppbtree node, t_pbtree new);
void					_bt_push_right(t_ppbtree node, t_pbtree new);
void					_bt_push_root(t_ppbtree node, t_pbtree new);

/* GENERIC LINKED LIST */
void					_dlst_push_front(t_ppadlst dlst, void *addr_1,
							void *addr_2, int x);
void					_dlst_push_back(t_ppadlst dlst, void *addr_1,
							void *addr_2, int x);
void					_dlst_push_in(t_ppadlst dlst, t_pnlst node,
							void *addr_1, void *addr_2);

void					_dlst_pop_front(t_ppadlst dlst);
void					_dlst_pop_back(t_ppadlst dlst);
void					_dlst_pop_in(t_ppadlst dlst, t_ppnlst node);

void					_dlst_clear(t_ppadlst dlst);

int						_dlst_foreach_cmd(t_pdata data, t_pncmd cmd,
							int (*f)(t_pdata, t_pncmd), char *limiters);

void					_dlst_sort(t_ppadlst dlst, bool reverse);

void					_dlst_print_builtins(t_padlst dlst);
void					_dlst_print_env(t_padlst dlst);
void					_dlst_print_export(t_padlst dlst);
void					_dlst_print_tokens(t_padlst dlst);

/* CMD LIST */
void					_cmd_push_back(t_ppadlst dlst, t_pnlst token);
void					_cmd_pop_back(t_ppadlst dlst);
void					_cmd_clear(t_ppadlst dlst);
void					_cmd_print_line(t_pncmd cmd);
void					_cmd_print_all(t_padlst dlst);

struct					s_args
{
	int					ac;
	char				**av;
	char				**env;
	char				**env_path;
	char				**hard_path;
	int					_stdin;
	int					_stdout;
	int					parentheses;
	int					here_doc;
};

struct					s_data
{
	char				*prompt;
	t_args				args;
	t_padlst			builtins;
	t_padlst			env;
	t_padlst			export;
	t_padlst			tokens;
	t_pbtree			tree;
	int					_errno;
	struct sigaction	s_sig;
};

struct					s_nlst
{
	void				*addr_1;
	void				*addr_2;
	int					x;
	bool				flag;
	t_pnlst				next;
	t_pnlst				prev;
	t_padlst			manager;
};
struct					s_redir
{
	char				*in_name;
	char				*out_name;
	char				*here_name;

	char				**here_names;
	char				**here_limit;
	int					here_idx;
	int					here_fd;

	int					pfd[2];
	int					fd[2];

	bool				in_access;
	bool				out_trunc;
	bool				out_inside;
	bool				here_inside;
};

struct					s_ncmd
{
	t_pnlst				token;
	char				**args;
	char				*path;
	t_redir				redirs;
	pid_t				pid;
	t_pncmd				next;
	t_pncmd				prev;
	t_padlst			manager;
};

struct					s_adlst
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
			t_pncmd		c_top;
			t_pncmd		c_bot;
			int			c_size;
		};
	};
};

struct					s_btree
{
	t_pnlst				token;
	t_padlst			cmd_line;
	struct s_btree		*root;
	struct s_btree		*left;
	struct s_btree		*right;
};

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
	_SUCCESS = 0,
	_FAILURE = 1,
	_ERROR = -1,
	_ALLOC = -2
};

# define _ERR_TOKEN "bash: syntax error near unexpected token `%s'\n"
# define _ERR_CLOSE "bash: syntax error a token field `%c' is not closed\n"
# define _ERR_NEWLINE "bash: syntax error near unexpected token `newline'\n"
# define _ERR_HEREDOC "bash: maximum here-document count exceeded\n"
# define _ERR_NOT_FOUND "bash: %s: command not found\n"
# define _ERR_IS_DIR "bash: %s: Is a directory\n"
# define _ERR_NO_FILE "bash: %s: No such file or directory\n"

# define _ERR_ENV_NO_FILE "env: %s: No such file or directory\n"
# define _ERR_EXPORT_INVALID "bash: export: `%s': not a valid identifier\n"

# define _ERR_EXIT_NUM "bash: exit: %s: numeric argument required\n"
# define _ERR_EXIT_MANY "bash: exit: too many arguments\n"

# define _PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"

# define _O_RWCT O_RDWR | O_CREAT | O_TRUNC, 0644
# define _O_RWCA O_RDWR | O_CREAT | O_APPEND, 0644

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

# define _TYP_SEP "AO()"
# define _TYP_REDIRS "<>HN"

# define WHITE "\033[0;97m"
# define RESET "\033[0;39m"

# define CYAN "\033[0;96m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"

# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define RED "\033[0;91m"

#endif /* MINISHELL_H */