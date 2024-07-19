/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:11:53 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 20:02:24 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_tok_parenthesis_process(char *input, u_padll token, int *i)
// {
// 	int	j;

// 	j = *i;
// 	if (input[*i] == ')')
// 		return (_tok_syntax_err(')', 1));
// 	while (input[*i] && input[*i] != _NEWLINE)
// 	{
// 		*i += 1;
// 		if (input[*i] == '(')
// 			_tok_parenthesis_process(input, token, i);
// 		if (input[*i] == ')')
// 		{
// 			token = _tok_push_back(token, _OPEN_PAR, ft_substr(input, j + 1, *i
// - j - 1));
// 			_tok_process(token->t_bot->value, token);
// 			*i += 1;
// 			return (IT_IS);
// 		}
// 	}
// 	return (_tok_syntax_close_err('('));
// }

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
			token = _tok_push_back(token, tok, ft_substr(input, j + 1, (*i - j - 1)));
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
	if (token->t_bot->value[*i] == '&' && token->t_bot->value[*i + 1] == '&')
		return (_tok_and(input, token, i));
	else if (token->t_bot->value[*i] == '|' && token->t_bot->value[*i
		+ 1] == '|')
		return (_tok_or(input, token, i));
	else if (token->t_bot->value[*i] == '|' && token->t_bot->value[*i
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
	// else if (_tok_is(_PARENTHESIS, input[*i])
		// && _tok_parenthesis_process(input, token, i) == EXIT_ERROR)
	// 	return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}

int	_tok_literal_process(char *input, u_padll token, int *i)
{
	int	j;

	j = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !_tok_is(_TOKENS, input[*i]))
		*i += 1;
	token = _tok_push_back(token, _LITERAL, ft_substr(input, j, (*i - j)));
	if (input[*i] && !ft_isspace(input[*i]) && (input[*i] == '"' || input[*i] == '\''))
		token->t_bot->join = true;
	return (EXIT_SUCCESS);
}

int	_tok_process(char *input, u_padll token)
{
	int	i;

	i = 0;
	token->t_bot->type = _TOP;
	while (input[i] && input[i] != _NEWLINE)
	{
		if (input[i] && _tok_is(_TOKENS, input[i]))
		{
			if (_tok_token_process(input, token, &i) == EXIT_ERROR)
				return (EXIT_ERROR);
		}
		else if (input[i] && !ft_isspace(input[i]))
			_tok_literal_process(input, token, &i);
		else if (input[i])
			i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	t_data	data;
	int		i;

	i = -1;
	(void)i;
	if (_data_init(&data, ac, av, ev))
		return (EXIT_FAILURE);
	while (1)
	{
		printf(CYAN "-------------------------------------- PROMPT --------------------------------------" RESET "\n");
		data.input = readline(">$ ");
		if (!data.input || !ft_strncmp(data.input, "exit", 4))
			return (EXIT_FAILURE);
		add_history(data.input);
		printf(BLUE "-------------------------------------- TOKENS --------------------------------------" RESET "\n");
		_tok_process(data.input, data.tok);
		_tok_print(data.tok);
		_tok_clear(data.tok);
	}
	return (EXIT_SUCCESS);
}

// {
//// DATA INIT TEST
// 	printf("data->ac = %d\n", data.ac);
// 	while (data.av[++i])
// 		printf("data->av[%d] = %s\n", i, data.av[i]);
// 	i = -1;
// 	while (data.env.ev[++i])
// 		printf("data->env.ev[%d] = %s\n", i, data.env.ev[i]);
// }