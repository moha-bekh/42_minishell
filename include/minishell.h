/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:31:50 by moha              #+#    #+#             */
/*   Updated: 2024/09/28 20:09:08 by mbekheir         ###   ########.fr       */
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
# include <termios.h>

typedef struct s_data t_data, *t_pdata; // Struct Data

extern int				*g_ptr_errno;

/* SIGNALS */
void					_hndl_sigint(int sig);
void					_hndl_hd_sigint(int sig);

int						_set_sigint(t_pdata data);
int						_ign_sigint(t_pdata data);
int						_dfl_sigint(t_pdata data);
int						_ign_sigquit(t_pdata data);
int						_dfl_sigquit(t_pdata data);
int						_sig_init_sas(t_pdata data);

/* DATA */
int						_data_init(t_pdata data, int ac, char **av, char **ev);
int						_env_init(t_pdata data);
/* CLEAR */
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
int						_exec_redirections(t_ppncmd cmd);

// int						_exec_builtin(t_pdata data, t_ppncmd cmd);
// int						_exec_builtin_proc(t_pdata data, t_ppncmd cmd);
// int						_exec_proc(t_pdata data, t_ppncmd cmd);
// int						_exec(t_pdata data, t_ppbtree node);
// int						_exec_redirections(t_ppncmd cmd);

/* EXPAND */
int						_xpd_line(t_pdata data, t_ppnlst token);
int						_xpd_wildcards(t_pdata data, t_ppnlst token);
char					*_xpd_str(t_pdata data, char *line);
/* EXPAND UTILS */
int						_xpd_right_border(t_ppnlst token, t_ppadlst list);
int						_xpd_left_border(t_ppnlst token, t_ppadlst list);
int						_xpd_full_astrix(char *str);

/* PARSING */
int						_pars_pipe_lines(t_ppbtree node);
int						_pars_args_line(t_pdata data, t_ppncmd cmd,
							t_ppnlst token, bool inside);
int						_pars_redirs(t_pdata data, t_ppncmd cmd, t_ppnlst token,
							bool inside);

/* BUILTINS */
int						_cd(t_pdata data, char **args);
int						_echo(char **args);
int						_env(t_pdata data, char **args);
int						_exit_(t_pdata data, char **args);
int						_export(t_pdata data, char **args);
int						_pwd(t_pdata data);
int						_unset(t_pdata data, char **args);

/* UTILS */
void					_bt_print(t_pbtree node, int i);
void					_dlst_print_builtins(t_padlst dlst);
void					_dlst_print_env(t_padlst dlst);
void					_dlst_print_export(t_padlst dlst);
void					_dlst_print_tokens(t_padlst dlst);
int						_err_print(char *str, void *arg, bool ptr, int _errno);
t_pdata					_get_data(void);
char					*_get_env_value(t_pdata data, char *key);
char					*_get_rname(void);
int						_is_builtin(t_pdata data, char **args);
int						_is_overflow(char *str);
int						_is_varchr(char c);
int						_join_strings(t_ppnlst token);
int						_key_exist(t_padlst env, char *arg);
int						_limit_quoted(char *str);
char					**_ltoa(t_padlst dlst);
int						_nb_lnargs(t_pnlst token);
int						_path_slasher(t_pdata data);
int						_tok_id(char a, char *str);
int						_varstr_conv(char *str);
void					_wait_pids(t_pdata data, t_padlst cmd_line);
int						_xpd_conv(char c);
int						_xpd_needed(char *str);

int						_resolve_path(t_pdata data, t_ppncmd cmd);

struct					s_args
{
	int					ac;
	char				**av;
	char				**env;
	char				**env_path;
	char				**hard_path;
	int					parnth;
	int					nb_hd;
};

struct					s_shell
{
	int					_stdin;
	int					_stdout;
	struct termios		org_term;
	struct termios		new_term;
	struct sigaction	s_sigint;
	struct sigaction	s_sigquit;
};

struct					s_data
{
	char				*prompt;
	struct s_args		args;
	t_padlst			builtins;
	t_padlst			env;
	t_padlst			export;
	t_padlst			tokens;
	t_pbtree			tree;
	t_padlst			xpd;
	int					_errno;
	struct s_shell		shell;
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
};

# define _ERR_TOKEN "bash: syntax error near unexpected token `%s'\n"
# define _ERR_CLOSE "bash: syntax error a token field `%c' is not closed\n"
# define _ERR_NEWLINE "bash: syntax error near unexpected token `newline'\n"
# define _ERR_HEREDOC "bash: maximum here-document count exceeded\n"
# define _ERR_NOT_FOUND "bash: %s: command not found\n"
# define _ERR_IS_DIR "bash: %s: Is a directory\n"
# define _ERR_NO_FILE "bash: %s: No such file or directory\n"
# define _ERR_NO_DIR "bash: cd: %s: No such file or directory\n"
# define _ERR_PWD "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"

# define _ERR_ENV_NO_FILE "env: %s: No such file or directory\n"
# define _ERR_EXPORT_INVALID "bash: export: `%s': not a valid identifier\n"

# define _ERR_EXIT_NUM "exit\nbash: exit: %s: numeric argument required\n"
# define _ERR_EXIT_MANY "exit\nbash: exit: too many arguments\n"

# define _ERR_PERM "bash: %s: permission denied\n"
# define _ERR_HERE_EOF "bash: warning: here-document delimited by end-of-file (wanted `%s')\n"

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
