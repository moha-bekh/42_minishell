/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:11:56 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/23 17:45:40 by mbekheir         ###   ########.fr       */
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
// # DOUBLE LINKED LIST
// ###########################################################################

typedef struct s_ev
{
	char			*key;
	char			*value;
	struct s_ev		*next;
	struct s_ev		*prev;
} t_ev, *t_pev;

struct s_bt_op;

typedef struct s_scop
{
	struct s_bt_op	*ptr_op;
	struct s_scop	*next;
	struct s_scop	*prev;
} t_scop, *t_pscop;

typedef struct s_tok
{
	char			type;
	char			*value;
	bool			join;
	struct s_tok	*next;
	struct s_tok	*prev;
} t_tok, *t_ptok;

typedef struct s_redir
{
	int				fd[2];
	int				*pfd[2];
	int				here_fd;
	char			*here_name;
} t_redir, t_predir;

typedef struct s_cmd
{
	char			**cmd_a;
	int				status;
	t_predir		redir;
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
			t_pscop	s_top;
			t_pscop	s_bot;
			int		s_size;
		};
		struct
		{
			t_ptok	t_top;
			t_ptok	t_bot;
			int		t_size;
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
	int				status;
	t_ptok			token;
	u_padll			cmd_left;
	u_padll			cmd_right;
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
	u_padll			dll_sort_env;
	int				shlvl;
} t_env, *t_penv;

typedef struct s_data
{
	int				ac;
	char			**av;
	char			*input;
	t_env			env;
	u_padll			tok;
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

# define _SYNTAX_ERR "syntax error near unexpected token `"
# define _SYNTAX_CLOSE_ERR "syntax error a token field `"

# define _SYNTAX_AND_ERR "&|;"
# define _SYNTAX_OR_ERR "|&;"
# define _SYNTAX_PIPE_ERR ";"
# define _SYNTAX_REDIR_IN_ERR ">|;"
# define _SYNTAX_REDIR_OUTT_ERR "<;"
# define _SYNTAX_REDIR_OUTA_ERR "><|&;"
# define _SYNTAX_HERE_DOC_ERR "<&|();\n"

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
// #  UTILS FUNCTIONS
// ###########################################################################

int					_alloc(void **target, size_t size);
void				_clean(void *target, size_t size);
void				ft_free_arr(char **arr);
int					_data_init(t_pdata data, int ac, char **av, char **ev);
void				_cleaner(t_pdata data);

// ###########################################################################
// #  TOKENS FUNCTIONS
// ###########################################################################

int					_tok_is(char *str, char a);

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

// # SCOP
u_padll				_scp_clear(u_padll dll);
u_padll				_scp_pop_back(u_padll dll);
void				_tok_print(u_padll dll);
u_padll				_scp_push_back(u_padll dll, struct s_bt_op *ptr_op);

// # TOKENS
u_padll				_tok_clear(u_padll dll);
u_padll				_tok_pop_back(u_padll dll);
void				_tok_print(u_padll dll);
u_padll				_tok_push_back(u_padll dll, char type, char *value);
u_padll				_tok_sub_struct(t_ptok start, t_ptok end);

// # OPERATIONS
t_pbt_op			_op_bt_clear(t_pbt_op tree);
t_pbt_op			_op_bt_create(char type, t_ptok token);
t_pbt_op			_op_bt_join(t_pbt_op tree, t_pbt_op left, t_pbt_op right);
void				_op_bt_print(t_pbt_op tree, bool prefix, int i);
t_pbt_op			_op_bt_push_at(t_pbt_op tree, t_pbt_op node, bool left);
t_pbt_op			_op_bt_push_root(t_pbt_op tree, t_pbt_op node);
t_pbt_op			_op_bt_push_right(t_pbt_op tree, t_pbt_op node);
t_pbt_op			_op_bt_push_left(t_pbt_op tree, t_pbt_op node);

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