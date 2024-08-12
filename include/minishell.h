/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:11:56 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 19:48:58 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/* ###########################################################################
C LIBS */
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
/* ###########################################################################
MY LIBS */
# include "libft.h"
/* ###########################################################################
DATA STRUCTURE */
typedef struct s_ev
{
	char				*key;
	char				*value;
	struct s_ev			*next;
	struct s_ev			*prev;
} t_ev, *t_pev;

typedef struct s_tok
{
	char				type;
	char				*value;
	bool				join;
	struct s_tok		*next;
	struct s_tok		*prev;
} t_tok, *t_ptok;

struct s_bt_op;

typedef struct s_scop
{
	struct s_bt_op		*ptr_op;
	struct s_scop		*next;
	struct s_scop		*prev;
} t_scop, *t_pscop;

typedef struct s_redir
{
	char				*here_name;
	char				*here_limit;
	char				*in_name;
	bool				_access;
	char				*out_name;
	bool				trunc;
	int					fd[2];
	int					pfd[2];
	int					here_fd;
} t_redir, t_predir;

typedef struct s_cmd
{
	t_ptok				token;
	bool				built_in;
	char				*cmd_path;
	char				**cmd_arg;
	t_redir				redir;
	pid_t				pid;
	int					status;
	struct s_cmd		*next;
	struct s_cmd		*prev;
} t_cmd, *t_pcmd;

typedef struct s_adll
{
	union
	{
		struct
		{
			t_pev		e_top;
			t_pev		e_bot;
			int			e_size;
		};
		struct
		{
			t_ptok		t_top;
			t_ptok		t_bot;
			int			t_size;
		};
		struct
		{
			t_pscop		s_top;
			t_pscop		s_bot;
			int			s_size;
		};
		struct
		{
			t_pcmd		c_top;
			t_pcmd		c_bot;
			int			c_size;
		};
	};
} u_adll, *u_padll;

typedef struct s_bt_op
{
	char				type;
	t_ptok				token;
	u_padll				cmd;
	int					status;
	struct s_bt_op		*left;
	struct s_bt_op		*root;
	struct s_bt_op		*right;
} t_bt_op, *t_pbt_op;

typedef struct s_env
{
	char				**env;
	char				**min_ev;
	u_padll				dll_env;
	u_padll				dll_senv;
} t_env, *t_penv;

typedef struct s_data
{
	int					ac;
	char				**av;
	char				*input;
	char				*tmp;
	char				*built_in[7];
	char				**paths[2];
	int					_errno;
	t_env				env;
	u_padll				tok;
	u_padll				exp;
	u_padll				scp;
	t_pbt_op			tree;
	struct sigaction	sa;
} t_data, *t_pdata;
/* ###########################################################################
DATA FUNCTIONS */
int						_data_init(t_pdata data, int ac, char **av, char **ev);
void					_data_cleaner(t_pdata data);
void					_data_clear_lists(t_pdata data);
// void					_data_clear_builtin(char **builtin);
/* ###########################################################################
ENVIRONMENT FUNCTIONS */
int						_set_env(t_pdata data, u_padll *env, char **ev);
int						_set_senv(u_padll *s_env, u_padll env);
int						_delete_from_env(t_pdata data, char **arg);
/* ###########################################################################
BUILT-IN FUNCTIONS */

int						_echo(t_pdata data, char **arg);
int						_env(t_pdata data, char **arg);
int						_exit_(t_pdata data, char **arg);
int						_export(t_pdata data, char **arg);
int						_pwd(void);
int						_unset(t_pdata data, char **arg);
/* ###########################################################################
TOKEN FUNCTIONS */
int						_token(t_pdata data);
int						_op_proc(t_pdata data, int *i);
int						_redir_proc(t_pdata data, int *i);
// UTILS
int						_tok_is(char *str, char a);
int						_tok_stx_err(char a, int n);
int						_tok_stx_close_err(char a);
int						_tok_check(t_pdata data);
/* ###########################################################################
EXPAND FUNCTIONS */
int						_expand(t_pdata data);
int						_expand_string(t_pdata data, t_ptok token);
int						_varchr_conv(char c);
/* ###########################################################################
TREE FUNCTIONS */
t_pbt_op				_tree(t_pdata data);
/* ###########################################################################
PARSING FUNCTIONS */
int						_parsing(t_pbt_op tree);
int						_pars_redirs(t_pcmd cmd, t_ptok token);
/* ###########################################################################
EXECUTION FUNCTIONS */
int						_exec(t_pdata data, t_pbt_op tree);
int						_is_builtin(t_pdata data, char *str);
int						_path_slash(t_pdata data, int idx);
int						_resolve_path(t_pdata data, t_pbt_op node);
/* ###########################################################################
SIGNAL FUNCTIONS */
int						_set_signals(t_pdata data);
void					sa_hndl(int sig);
void					child_hndl(int sig);
/* ###########################################################################
UTILS FUNCTIONS */
int						_alloc(void **target, size_t size);
void					_clean(void *target, size_t size);

int						_get_start_index(char *str);
char					*_get_env_value(u_padll env, char *key);
int						_count_arg(t_ptok token);
char					*get_random_name(void);
int						is_overflow(char *str);

int						_join_strings(t_pdata data);
/* ###########################################################################
DLL FUNCTIONS */
u_padll					_cmd_clear(u_padll dll);
u_padll					_cmd_pop_back(u_padll dll);
u_padll					_cmd_pop_in(u_padll dll, t_pcmd target);
void					_cmd_print(u_padll dll);
u_padll					_cmd_push_back(u_padll dll, t_ptok token,
							char **cmd_arg);

u_padll					_env_clear(u_padll dll);
u_padll					_env_pop_back(u_padll dll);
u_padll					_env_pop_in(u_padll dll, t_pev target);
void					_env_print(u_padll dll);
u_padll					_env_push_back(u_padll dll, char *key, char *value);
u_padll					_env_sort(u_padll dll);

u_padll					_scp_clear(u_padll dll);
u_padll					_scp_pop_back(u_padll dll);
u_padll					_scp_push_back(u_padll dll, struct s_bt_op *ptr_op);

u_padll					_tok_clear(u_padll dll);
u_padll					_tok_pop_back(u_padll dll);
u_padll					_tok_pop_front(u_padll dll);
u_padll					_tok_pop_in(u_padll dll, t_ptok target);
void					_tok_print(u_padll dll);
u_padll					_tok_push_back(u_padll dll, char type, char *value);
/* ###########################################################################
BINARY TREE FUNCTIONS */
t_pbt_op				_op_bt_clear(t_pbt_op tree);
t_pbt_op				_op_bt_create(char type, t_ptok token);
void					_op_bt_print(t_pbt_op tree, bool prefix, int i);
t_pbt_op				_op_bt_push_right(t_pbt_op tree, t_pbt_op node);
t_pbt_op				_op_bt_push_root(t_pbt_op tree, t_pbt_op node);
/* ###########################################################################
TOKENS TYPE */
enum					e_tokens
{
	_PIPE = 'P',
	_HERE_DOC = 'H',
	_REDIR_OUTA = 'N',
	_AND = 'A',
	_OR = 'O',
	_WORD = 'W',
};
/* ###########################################################################
TOKENS GROUPS */
# define _TOKENS "*'\"()$|&<>"
# define _OPERATORS "|&"
# define _PARENTHESIS "()"
# define _QUOTES "'\""
# define _REDIRS "<>"
# define _OTHERS "()$*"
# define _TYP_SEP "AO()"
# define _TYP_REDIRS "HN<>"
/* ###########################################################################
TOKENS SYNTAX ERRORS */
# define _STX_ERR "syntax error near unexpected token `"
# define _STX_ERR_CLOSE "syntax error a token field `"
# define _STX_ERR_REDIR "bash: syntax error near unexpected token `newline'\n"
# define _STX_ERR_OP "|&;"
# define _STX_ERR_PIPE ";"
# define _STX_ERR_REDIR_IN ">;&|"
# define _STX_ERR_REDIR_OUTT "<;&|"
# define _STX_ERR_REDIR_OUTA "><|&;"
# define _STX_ERR_HERE_DOC "<&|();\n"
/* ###########################################################################
OTHERS ERRORS */
# define _CMD_NOT_FOUND "bash: %s: command not found\n"
/* ###########################################################################
PATH */
# define _PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"
// # define _PATH_ "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
/* ###########################################################################
EXIT CODES */
enum					e_return
{
	_EXT_DUP2 = -8,
	_EXT_DUP = -7,
	_EXT_EXEC = -6,
	_EXT_PIPE = -5,
	_EXT_FORK = -4,
	_EXT_OPEN = -3,
	_ALLOC = -2,
	_ERROR = -1,
	_SUCCESS = 0,
	_FAILURE = 1,
	_SYNTAX_ERR = 3,
	_IS = 1,
	_NOT = 0
};
/* ###########################################################################
COLORS */
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define RESET "\033[0;39m"
#endif /* MINISHELL_H */