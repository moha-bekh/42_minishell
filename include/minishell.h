/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:31:50 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 18:16:20 by moha             ###   ########.fr       */
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
typedef struct s_redir t_redir, *t_predir; // Struct Redirections
typedef struct s_args t_args, *t_pargs;    // Struct Args
typedef struct s_data t_data, *t_pdata;    // Struct Data

extern int				*_ptr_errno;

/* UTILS */
void					_bt_print(t_pbtree node, int i);
int						_cmd_foreach(t_pdata data, t_pncmd cmd,
							int (*f)(t_pdata, t_pncmd), char *limiters);

int						_sep(char *str);
int						_path_slash(t_pdata data);
int						is_overflow(char *str);
char					*get_random_name(void);
int						_count_args(t_pnlst token);

int						_err_print(char *str, void *arg, bool ptr, int _errno);
t_pdata					_get_data(void);

/* SIGNALS */
int						_set_signals(t_pdata data);
void					child_hndl(int sig);
void					sig_hndl(int sig);

/* DATA */
int						_data_init(t_pdata data, int ac, char **av, char **ev);
int						_data_clear(t_pdata data);
int						_data_structs_clear(t_pdata data);


/* TOKENS */
int						_tok_id(char a, char *str);
int						_tok_list(t_pdata data);
int						_tok_proc(t_pdata data, int *i);
int						_op_proc(t_pdata data, int *i);
int						_redir_proc(t_pdata data, int *i);
int						_quote_proc(t_pdata data, int *i);
int						_check_top(t_pdata data);
int						_check_bot(t_pdata data);

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
// int						_echo(t_pdata data, t_pnlst token, char **args);
int						_cd(t_pdata data, char **args);
int						_echo(t_pdata data, char **args);
int						_env(t_pdata data, char **args);
int						_exit_(t_pdata data, char **args);
int						_export(t_pdata data, char **args);
int						_pwd(void);
int						_unset(t_pdata data, char **args);

/* GENERIC LINKED LIST */
void					_dlst_print_builtins(t_padlst dlst);
void					_dlst_print_env(t_padlst dlst);
void					_dlst_print_export(t_padlst dlst);
void					_dlst_print_tokens(t_padlst dlst);

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