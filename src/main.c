/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:11:53 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/23 18:11:10 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_is(char *str, char a)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == a)
			return (IT_IS);
	return (IS_NT);
}

int	_tok_syntax_err(char a, int n)
{
	int	i;

	i = -1;
	ft_putstr_fd(_SYNTAX_ERR, STDERR_FILENO);
	while (++i < n)
		ft_putchar_fd(a, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (RET_ERR);
}

int	_tok_syntax_close_err(char a)
{
	ft_putstr_fd(_SYNTAX_CLOSE_ERR, STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putstr_fd("' must be closed\n", STDERR_FILENO);
	return (RET_ERR);
}

int	_tok_check_operator(u_padll tokens)
{
	t_ptok	tmp;

	tmp = tokens->t_top->next;
	if (tmp->type == 'A' || tmp->type == 'O')
		return (_tok_syntax_err(tmp->value[0], 2));
	if (tokens->t_bot->type == 'A' || tokens->t_bot->type == 'O')
		return (_tok_syntax_err(tokens->t_bot->value[0], 2));
	return (RET_OK);
}

int	_tok_check_pipe(u_padll tokens)
{
	t_ptok	tmp;

	tmp = tokens->t_top->next;
	if (tmp->type == '|')
		return (_tok_syntax_err('|', 1));
	if (tokens->t_bot->type == '|')
		return (_tok_syntax_err('|', 1));
	return (RET_OK);
}
int	_tok_check_redir(t_ptok tok)
{
	if (_tok_is(_REDIRS, tok->value[0]) && tok->next->type != _LITERAL)
		return (_tok_syntax_err(tok->next->value[0], 2));
	return (RET_OK);
}

int	_tok_check(u_padll tokens)
{
	t_ptok	tmp;

	tmp = tokens->t_top;
	if (_tok_check_operator(tokens) == -1 || _tok_check_pipe(tokens) == -1)
		return (RET_ERR);
	while (tmp)
	{
		if (_tok_check_redir(tmp) == -1)
			return (RET_ERR);
		tmp = tmp->next;
	}
	return (RET_OK);
}

int	_tok_quotes_process(char *input, u_padll token, int *i)
{
	char	tok;
	int		j;

	tok = input[*i];
	j = *i;
	while (input[*i] && input[*i] != _NEWLINE)
	{
		*i += 1;
		if (input[*i] && input[*i] == tok)
		{
			token = _tok_push_back(token, tok, ft_substr(input, j + 1, (*i - j
							- 1)));
			*i += 1;
			if (input[*i] && !ft_isspace(input[*i]))
				token->t_bot->join = true;
			return (IT_IS);
		}
	}
	return (_tok_syntax_close_err(tok));
}

int	_tok_set_redir_in(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, '<', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_REDIR_IN_ERR, value[*i + 1]))
	// 	return (_tok_syntax_err(value[*i + 1], 1));
	token->t_bot->value[1] = '\0';
	token->t_bot->value[2] = '\0';
	*i += 1;
	return (IT_IS);
}

int	_tok_set_redir_outt(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, '>', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_REDIR_OUTT_ERR, value[*i + 1]))
	// 	return (_tok_syntax_err(value[*i + 1], 1));
	token->t_bot->value[1] = '\0';
	token->t_bot->value[2] = '\0';
	*i += 1;
	return (IT_IS);
}

int	_tok_set_redir_outa(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, 'N', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_REDIR_OUTA_ERR, value[*i + 2]))
	// 	return (_tok_syntax_err(value[*i + 2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_set_here_doc(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, 'H', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_HERE_DOC_ERR, value[*i + 2]))
	// 	return (_tok_syntax_err(value[*i + 2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_or(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _OR, ft_substr(input, *i, 3));
	if (_tok_is(_SYNTAX_OR_ERR, token->t_bot->value[2]))
		return (_tok_syntax_err(token->t_bot->value[2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_and(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _AND, ft_substr(input, *i, 3));
	if (_tok_is(_SYNTAX_AND_ERR, token->t_bot->value[2]))
		return (_tok_syntax_err(token->t_bot->value[2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_pipe(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _PIPE, ft_substr(input, *i, 3));
	if (_tok_is(_SYNTAX_PIPE_ERR, token->t_bot->value[1]))
		return (_tok_syntax_err(token->t_bot->value[1], 1));
	token->t_bot->value[1] = '\0';
	token->t_bot->value[2] = '\0';
	*i += 1;
	return (IT_IS);
}

int	_tok_operator_process(char *input, u_padll token, int *i)
{
	if (token->t_top->value[*i] == '&' && token->t_top->value[*i + 1] == '&')
		return (_tok_and(input, token, i));
	else if (token->t_top->value[*i] == '|' && token->t_top->value[*i
		+ 1] == '|')
		return (_tok_or(input, token, i));
	else if (token->t_top->value[*i] == '|' && token->t_top->value[*i
		+ 1] != '|')
		return (_tok_pipe(input, token, i));
	else
		*i += 1;
	return (IS_NT);
}

int	_tok_others_process(char *input, u_padll token, int *i)
{
	if (input[*i] == '$')
	{
		token = _tok_push_back(token, _DOLLAR, ft_substr(input, *i, 1));
		*i += 1;
		return (IT_IS);
	}
	else if (input[*i] == '*')
	{
		token = _tok_push_back(token, _WILDCARD, ft_substr(input, *i, 1));
		*i += 1;
		return (IT_IS);
	}
	else if (input[*i] == '(')
	{
		token = _tok_push_back(token, _OPEN_PAR, ft_substr(input, *i, 1));
		*i += 1;
		return (IT_IS);
	}
	else if (input[*i] == ')')
	{
		token = _tok_push_back(token, _CLOSE_PAR, ft_substr(input, *i, 1));
		*i += 1;
		return (IT_IS);
	}
	return (IS_NT);
}

int	_tok_redir_process(char *input, u_padll token, int *i)
{
	if (input[*i] == '<' && input[*i + 1] != '<')
		return (_tok_set_redir_in(input, token, i));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (_tok_set_here_doc(input, token, i));
	else if (input[*i] == '>' && input[*i + 1] != '>')
		return (_tok_set_redir_outt(input, token, i));
	else if (input[*i] == '>' && input[*i + 1] == '>')
		return (_tok_set_redir_outa(input, token, i));
	return (EXIT_SUCCESS);
}

int	_tok_token_process(char *input, u_padll token, int *i)
{
	if (_tok_is(_OPERATORS, input[*i]) && _tok_operator_process(input, token,
			i) == EXIT_ERROR)
		return (EXIT_ERROR);
	else if (_tok_is(_REDIRS, input[*i]) && _tok_redir_process(input, token,
			i) == EXIT_ERROR)
		return (EXIT_ERROR);
	else if (_tok_is(_QUOTES, input[*i]) && _tok_quotes_process(input, token,
			i) == EXIT_ERROR)
		return (EXIT_ERROR);
	else if (_tok_is(_OTHERS, input[*i]) && _tok_others_process(input, token,
			i) == EXIT_ERROR)
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}

int	_tok_literal_process(char *input, u_padll token, int *i)
{
	int	j;

	j = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !_tok_is(_TOKENS, input[*i]))
		*i += 1;
	token = _tok_push_back(token, _LITERAL, ft_substr(input, j, (*i - j)));
	if (input[*i] && !ft_isspace(input[*i]) && (input[*i] == '"'
			|| input[*i] == '\''))
		token->t_bot->join = true;
	return (EXIT_SUCCESS);
}

int	_tok_process(char *input, u_padll *token)
{
	int	i;

	i = 0;
	*token = _tok_push_back(*token, _TOP, ft_strdup(input));
	while (input[i] && input[i] != _NEWLINE)
	{
		if (input[i] && _tok_is(_TOKENS, input[i]))
		{
			if (_tok_token_process(input, *token, &i) == EXIT_ERROR)
				return (EXIT_ERROR);
		}
		else if (input[i] && !ft_isspace(input[i]))
			_tok_literal_process(input, *token, &i);
		else if (input[i])
			i++;
	}
	_tok_check(*token);
	return (EXIT_SUCCESS);
}

t_pbt_op	_ptr_recovery(t_pbt_op tree, u_padll *scop)
{
	(*scop)->s_bot->ptr_op->right = tree;
	tree->root = (*scop)->s_bot->ptr_op;
	tree = (*scop)->s_bot->ptr_op;
	(*scop) = _scp_pop_back((*scop));
	return (tree);
}

t_pbt_op	_operation_tree(t_pdata data)
{
	t_ptok	tok;

	tok = data->tok->t_top->next;
	while (tok)
	{
		if (tok->type == _AND || tok->type == _OR)
			data->tree = _op_bt_push_root(data->tree, _op_bt_create(tok->type, tok));
		if (tok->type == _OPEN_PAR)
		{
			data->scop = _scp_push_back(data->scop, data->tree);
			data->tree = NULL;
		}
		else if (tok->type == _CLOSE_PAR)
			data->tree = _ptr_recovery(data->tree, &data->scop);
		else if (_tok_is(_TREE_SEP, tok->prev->type))
			data->tree = _op_bt_push_right(data->tree, _op_bt_create(tok->type, tok));
		tok = tok->next;
	}
	return (data->tree);
}

int	main(int ac, char **av, char **ev)
{
	t_data	data;
	int		i;

	i = 0;
	if (_data_init(&data, ac, av, ev))
		return (EXIT_FAILURE);

	// i = -1;
	// while (data.env.min_ev[++i])
	// 	printf("%s\n", data.env.min_ev[i]);
	// printf("\n====================================================\n\n");


	data.env.dll_env = _env_sort(data.env.dll_env);
	t_pev tmp = data.env.dll_env->e_top;
	
	while (tmp)
	{
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}


	// data.env.dll_sort_env = _env_sort(data.env.dll_sort_env);
	// t_pev tmp_ = data.env.dll_sort_env->e_top;
	// while (tmp_)
	// {
	// 	printf("export %s=", tmp_->key);
	// 	printf("%s\n", tmp_->value);
	// 	tmp_ = tmp_->next;
	// }
	
	
	return (0);

	while (1)
	{
		printf(CYAN "-------------------------------------- PROMPT --------------------------------------" RESET "\n");
		data.input = readline(">$ ");
		if (!data.input || !ft_strncmp(data.input, "exit", 4))
			return (_cleaner(&data), EXIT_FAILURE);
		add_history(data.input);
		if (!ft_strncmp(data.input, "clear", 5))
		{
			system("clear");
			continue ;
		}
		printf(BLUE "-------------------------------------- TOKENS --------------------------------------" RESET "\n");
		_tok_process(data.input, &data.tok);
		_tok_print(data.tok);
		data.tree = _operation_tree(&data);
		_op_bt_print(data.tree, true, i);
		data.tree = _op_bt_clear(data.tree);
		data.tok = _tok_clear(data.tok);
	}
	return (_cleaner(&data), EXIT_SUCCESS);
}

// int	main(void)
// {
// 	t_pbt_op	tree_1;
// 	t_pbt_op	tree_2;
// 	u_padll		scop;

// 	tree_1 = NULL;
// 	tree_2 = NULL;
// 	scop = NULL;

// 	tree_1 = _op_bt_push_right(tree_1, _op_bt_create('1', NULL));
// 	tree_2 = _op_bt_push_root(tree_2, _op_bt_create('2', NULL));
// 	scop = _scp_push_back(scop, tree_1);
// 	scop = _scp_push_back(scop, tree_2);
// 	printf("scp top value = %c\n", scop->s_top->ptr_op->type);
// 	printf("scp bot value = %c\n", scop->s_bot->ptr_op->type);

// 	scop = _scp_pop_back(scop);
// 	printf("scp top value = %c\n", scop->s_bot->ptr_op->type);

// 	(void)tree_1;
// 	(void)tree_2;
// 	return (0);
// }

// int main(void)
// {
// 	t_pbt_op tree;
// 	t_pbt_op scop_1;
// 	t_pbt_op scop_2;
// 	t_pbt_op scop_3;

// 	scop_1 = NULL;
// 	scop_2 = NULL;
// 	scop_3 = NULL;
// 	tree = NULL;

// 	tree = _op_bt_push_right(tree, _op_bt_create('X', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('&', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('Y', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));

// 	scop_1 = tree;
// 	tree = NULL;
// 	tree = _op_bt_push_right(tree, _op_bt_create('Z', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('&', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('A', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('&', NULL));

// 	scop_2 = tree;
// 	tree = NULL;

// 	tree = _op_bt_push_right(tree, _op_bt_create('M', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('N', NULL));

// 	scop_2->right = tree;
// 	tree->root = scop_2;
// 	tree = scop_2;

// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('O', NULL));

// 	scop_1->right = tree;
// 	tree->root = scop_1;
// 	tree = scop_1;

// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('B', NULL));

// 	_op_bt_print(tree, true);

// 	_op_bt_clear(tree);
// 	(void)scop_1;
// 	(void)scop_2;
// 	(void)scop_3;
// 	return (EXIT_SUCCESS);
// }

// {
//// DATA INIT TEST
// 	printf("data->ac = %d\n", data.ac);
// 	while (data.av[++i])
// 		printf("data->av[%d] = %s\n", i, data.av[i]);
// 	i = -1;
// 	while (data.env.ev[++i])
// 		printf("data->env.ev[%d] = %s\n", i, data.env.ev[i]);
// }