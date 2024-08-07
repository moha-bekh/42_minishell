/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 16:47:31 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_quote_proc(t_pdata data, int *i)
{
	char	type_quote;
	int		j;

	type_quote = data->input[*i];
	j = *i;
	while (data->input[*i] && data->input[*i] != '\n')
	{
		*i += 1;
		if (data->input[*i] && data->input[*i] == type_quote)
		{
			data->tok = _tok_push_back(data->tok, type_quote, ft_substr(data->input, j + 1, (*i - j - 1)));
			*i += 1;
			if (data->input[*i] && !ft_isspace(data->input[*i]))
				data->tok->t_bot->join = true;
			return (_SUCCESS);
		}
	}
	return (_tok_stx_close_err(type_quote));
}

int	_other_proc(char *input, u_padll tok, int *i)
{
	if (input[*i] == '$')
	{
		tok = _tok_push_back(tok, '$', ft_substr(input, *i, 1));
		*i += 1;
		return (_SUCCESS);
	}
	else if (input[*i] == '*')
	{
		tok = _tok_push_back(tok, '*', ft_substr(input, *i, 1));
		*i += 1;
		return (_SUCCESS);
	}
	else if (input[*i] == '(')
	{
		tok = _tok_push_back(tok, '(', ft_substr(input, *i, 1));
		*i += 1;
		return (_SUCCESS);
	}
	else if (input[*i] == ')')
	{
		tok = _tok_push_back(tok, ')', ft_substr(input, *i, 1));
		*i += 1;
		return (_SUCCESS);
	}
	return (_FAILURE);
}

int	_tok_proc(t_pdata data, int *i)
{
	if (_tok_is(_OPERATORS, data->input[*i]) && _op_proc(data, i))
		return (_ERROR);
	else if (_tok_is(_REDIRS, data->input[*i]) && _redir_proc(data, i))
		return (_ERROR);
	else if (_tok_is(_QUOTES, data->input[*i]) && _quote_proc(data, i))
		return (_ERROR);
	else if (_tok_is(_OTHERS, data->input[*i]) && _other_proc(data->input,
			data->tok, i))
		return (_ERROR);
	return (_SUCCESS);
}

int	_tok_word(t_pdata data, int *i)
{
	int	j;

	j = *i;
	while (data->input[*i] && !ft_isspace(data->input[*i]) && !_tok_is(_TOKENS,
			data->input[*i]))
		*i += 1;
	data->tok = _tok_push_back(data->tok, _WORD, ft_substr(data->input, j, (*i - j)));
	if (data->input[*i] && !ft_isspace(data->input[*i])
		&& (data->input[*i] == '"' || data->input[*i] == '\''))
		data->tok->t_bot->join = true;
	return (_SUCCESS);
}

int	_token(t_pdata data)
{
	int	i;

	i = 0;
	if (!data || !data->input)
		return (_FAILURE);
	while (data->input[i] && data->input[i] != '\n')
	{
		if (data->input[i] && _tok_is(_TOKENS, data->input[i]))
		{
			if (_tok_proc(data, &i))
				return (_ERROR);
		}
		else if (data->input[i] && !ft_isspace(data->input[i]))
		{
			if (_tok_word(data, &i))
				return (_ERROR);
		}
		else if (data->input[i])
			i++;
	}
	return (_SUCCESS);
}
