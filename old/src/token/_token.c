/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:00:11 by moha              #+#    #+#             */
/*   Updated: 2024/08/05 12:43:30 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			token = _tok_push_back(token, tok, ft_substr(input, j, (*i - j
							+ 1)));
			*i += 1;
			if (input[*i] && !ft_isspace(input[*i]))
				token->t_bot->join = true;
			return (_IS);
		}
	}
	return (_tok_syntax_close_err(tok));
}
// token = _tok_push_back(token, tok, ft_substr(input, j + 1, (*i - j - 1)));

int	_tok_others_process(char *input, u_padll token, int *i)
{
	if (input[*i] == '$')
	{
		token = _tok_push_back(token, _DOLLAR, ft_substr(input, *i, 1));
		*i += 1;
		return (_IS);
	}
	else if (input[*i] == '*')
	{
		token = _tok_push_back(token, _WILDCARD, ft_substr(input, *i, 1));
		*i += 1;
		return (_IS);
	}
	else if (input[*i] == '(')
	{
		token = _tok_push_back(token, _OPEN_PAR, ft_substr(input, *i, 1));
		*i += 1;
		return (_IS);
	}
	else if (input[*i] == ')')
	{
		token = _tok_push_back(token, _CLOSE_PAR, ft_substr(input, *i, 1));
		*i += 1;
		return (_IS);
	}
	return (_NOT);
}

int	_tok_token_process(char *input, u_padll token, int *i)
{
	if (_tok_is(_OPERATORS, input[*i]) && _tok_operator_process(input, token, i) == _ERROR)
		return (_ERROR);
	else if (_tok_is(_REDIRS, input[*i]) && _tok_redir_process(input, token, i) == _ERROR)
		return (_ERROR);
	else if (_tok_is(_QUOTES, input[*i]) && _tok_quotes_process(input, token, i) == _ERROR)
		return (_ERROR);
	else if (_tok_is(_OTHERS, input[*i]) && _tok_others_process(input, token, i) == _ERROR)
		return (_ERROR);
	return (_SUCCESS);
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
	return (_SUCCESS);
}

int	_tok_process(char *input, u_padll *token)
{
	int	i;

	i = 0;
	if (!input)
		return (_EMPTY);
	*token = _tok_push_back(*token, _TOP, ft_strdup(input));
	while (input[i] && input[i] != _NEWLINE)
	{
		if (input[i] && _tok_is(_TOKENS, input[i]))
		{
			if (_tok_token_process(input, *token, &i) == _ERROR)
				return (_ERROR);
		}
		else if (input[i] && !ft_isspace(input[i]))
		{
			if (_tok_literal_process(input, *token, &i))
				return (_ERROR);
		}
		else if (input[i])
			i++;
	}
	// if (_tok_check(*token) == _ERROR)
	// 	return (_ERROR);
	return (_SUCCESS);
}
