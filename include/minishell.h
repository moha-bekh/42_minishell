/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:11:56 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 17:14:38 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ###########################################################################
// #  C LIBS
// ###########################################################################

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

// ###########################################################################
// #  MY LIBS
// ###########################################################################

# include "libft.h"

// ###########################################################################
// #  ENVIROMENT
// ###########################################################################

# define _PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"
// # define _PATH_ "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

// ###########################################################################
// #  EXIT CODES
// ###########################################################################

# ifndef EXIT_ERROR
#  define EXIT_ERROR -1
# endif // EXIT_ERROR
# ifndef ALLOC_FAIL
#  define ALLOC_FAIL "allocation failed\n"
# endif // ALLOC_FAIL

// ###########################################################################
// # DOUBLE LINKED LIST
// ###########################################################################

typedef struct s_ev
{
	char			*key;
	char			*value;
	struct s_ev		*next;
	struct s_ev		*prev;
} t_ev, *t_pev;

typedef struct s_tok
{
	char			type;
	char			*value;
	bool			join;
	struct s_tok	*next;
	struct s_tok	*prev;
} t_tok, *t_ptok;

struct s_bt_op;
typedef struct s_scop
{
	struct s_bt_op	*ptr_op;
	struct s_scop	*next;
	struct s_scop	*prev;
} t_scop, *t_pscop;

typedef struct s_redir
{
	int				fd[2];
	int				*pfd[2];
	int				here_fd;
	char			*here_name;
} t_redir, t_predir;

typedef struct s_cmd
{
	t_ptok			token;
	bool			built_in;
	char			*cmd_path;
	char			**cmd_a;
	t_redir			redir;
	pid_t			pid;
	int				status;
	struct s_cmd	*next;
	struct s_cmd	*prev;
} t_cmd, *t_pcmd;

typedef struct s_adll
{
	union
	{
		struct
		{
			t_pev	e_top;
			t_pev	e_bot;
			int		e_size;
		};
		struct
		{
			t_ptok	t_top;
			t_ptok	t_bot;
			int		t_size;
		};
		struct
		{
			t_pscop	s_top;
			t_pscop	s_bot;
			int		s_size;
		};
		struct
		{
			t_pcmd	c_top;
			t_pcmd	c_bot;
			int		c_size;
		};
	};
} u_adll, *u_padll;

// ###########################################################################
// #  BINARY TREE
// ###########################################################################

typedef struct s_bt_op
{
	char			type;
	t_ptok			token;
	u_padll			cmd;
	char			**cmd_a;
	struct s_bt_op	*left;
	struct s_bt_op	*root;
	struct s_bt_op	*right;
} t_bt_op, *t_pbt_op;

// ###########################################################################
// #  DATA STRUCTURE
// ###########################################################################

typedef struct s_env
{
	char			**env;
	char			**min_ev;
	u_padll			dll_env;
	u_padll			dll_senv;
	int				shlvl;
} t_env, *t_penv;

typedef struct s_data
{
	int				ac;
	char			**av;
	char			*input;
	char			*tmp;
	char			*built_in[7];
	t_env			env;
	u_padll			tok;
	u_padll			exp;
	u_padll			scop;
	t_pbt_op		tree;
} t_data, *t_pdata;

// ###########################################################################
// #  UTILS TOKENS
// ###########################################################################

// # TOKENS TYPE

enum				e_tokens
{
	_NEWLINE = '\n',
	_SPACE = ' ',
	_SEMICOLON = ';',
	_WILDCARD = '*',
	_SQUOTE = '\'',
	_DQUOTE = '"',
	_OPEN_PAR = '(',
	_CLOSE_PAR = ')',
	_DOLLAR = '$',
	_PIPE = '|',
	_REDIR_IN = '<',
	_HERE_DOC = 'H',
	_REDIR_OUTT = '>',
	_REDIR_OUTA = 'N',
	_AND = 'A',
	_OR = 'O',
	_LITERAL = 'L',
	_TOP = '^',
	_BOT = '\\',
	_TREE = 'T',
};

// # TOKENS GROUPS

# define _TOKENS "*'\"()$|&<>"
# define _OPERATORS "|&"
# define _PARENTHESIS "()"
# define _QUOTES "'\""
# define _REDIRS "<>"
# define _OTHERS "()$*"
# define _TREE_SEP "^AO()"

// #  TOKENS SYNTAX ERRORS

# define _STX_ERR "syntax error near unexpected token `"
# define _STX_ERR_CLOSE "syntax error a token field `"

# define _STX_ERR_OR "|&;"
# define _STX_ERR_AND "&|;"
# define _STX_ERR_PIPE ";"
# define _STX_ERR_REDIR_IN ">|;"
# define _STX_ERR_REDIR_OUTT "<;"
# define _STX_ERR_REDIR_OUTA "><|&;"
# define _STX_ERR_HERE_DOC "<&|();\n"

// ###########################################################################
// #  UTILS FUNCTIONS
// ###########################################################################

int					_alloc(void **target, size_t size);
void				_clean(void *target, size_t size);
void				_cleaner(t_pdata data);
char				**_psplit(char *str, char *sep);
int					_data_init(t_pdata data, int ac, char **av, char **ev);
int					_get_start_index(char *str);
char				*_get_env_value(u_padll env, char *key);

// ###########################################################################
// #  ENVIRONMENT FUNCTIONS
// ###########################################################################

int					_set_env(u_padll *dll_env, char **ev);
int					_set_senv(u_padll *dll_senv, u_padll env);
int					_clean_env(t_pdata data, char **arg);

// ###########################################################################
// #  BUILT-IN FUNCTIONS
// ###########################################################################

int					_env(t_pdata data);
int					_export(t_pdata data, char **arg);
void				_export_print(u_padll dll);

// ###########################################################################
// #  TOKENS FUNCTIONS
// ###########################################################################

int					_tok_is(char *str, char a);
int					_tok_syntax_err(char a, int n);
int					_tok_syntax_close_err(char a);
int					_tok_check(u_padll tokens);

int					_tok_redir_process(char *input, u_padll token, int *i);
int					_tok_operator_process(char *input, u_padll token, int *i);
int					_tok_process(char *input, u_padll *token);

// ###########################################################################
// #  EXPAND FUNCTIONS
// ###########################################################################

int					_expand_tokens(t_pdata data);

// ###########################################################################
// #  OPERATOR FUNCTIONS
// ###########################################################################

t_pbt_op			_tree_process(t_pdata data);

// ###########################################################################
// #  PARSING FUNCTIONS
// ###########################################################################

int					_parsing(t_pbt_op tree);

// ###########################################################################
// #  EXECUTION FUNCTIONS
// ###########################################################################

// ###########################################################################
// #  DATA STRUCTURE FUNCTIONS
// ###########################################################################

// # ENVIRONMENT
u_padll				_env_clear(u_padll dll);
u_padll				_env_pop_back(u_padll dll);
u_padll				_env_pop_in(u_padll dll, t_pev target);
void				_env_print(u_padll dll);
u_padll				_env_push_back(u_padll dll, char *key, char *value);
u_padll				_env_push_in(u_padll dll, t_pev target, char *key,
						char *value);
u_padll				_env_sort(u_padll dll);

// # TOKENS
u_padll				_tok_clear(u_padll dll);
u_padll				_tok_pop_back(u_padll dll);
u_padll				_tok_pop_in(u_padll dll, t_ptok target);
void				_tok_print(u_padll dll);
u_padll				_tok_push_back(u_padll dll, char type, char *value);
u_padll				_tok_sub_struct(t_ptok start, t_ptok end);

// # SCOP
u_padll				_scp_clear(u_padll dll);
u_padll				_scp_pop_back(u_padll dll);
void				_tok_print(u_padll dll);
u_padll				_scp_push_back(u_padll dll, struct s_bt_op *ptr_op);

// # OPERATIONS
t_pbt_op			_op_bt_clear(t_pbt_op tree);
t_pbt_op			_op_bt_create(char type, t_ptok token);
t_pbt_op			_op_bt_join(t_pbt_op tree, t_pbt_op left, t_pbt_op right);
void				_op_bt_print(t_pbt_op tree, bool prefix, int i);
t_pbt_op			_op_bt_push_at(t_pbt_op tree, t_pbt_op node, bool left);
t_pbt_op			_op_bt_push_root(t_pbt_op tree, t_pbt_op node);
t_pbt_op			_op_bt_push_right(t_pbt_op tree, t_pbt_op node);
t_pbt_op			_op_bt_push_left(t_pbt_op tree, t_pbt_op node);

// # COMMANDS

u_padll				_cmd_push_back(u_padll dll, t_ptok token, char **cmd_a);
u_padll				_cmd_pop_back(u_padll dll);
void				_cmd_print(u_padll dll);
u_padll				_cmd_clear(u_padll dll);

// ###########################################################################
// # COLORS
// ###########################################################################

# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define RESET "\033[0;39m"

#endif // MINISHELL_H