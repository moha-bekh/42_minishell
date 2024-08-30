/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/30 05:03:30 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_token_id(char a, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == a)
			return (true);
	return (false);
}

int	_join_strings(t_pdata data, int start, int end)
{
	char	*old;
	char	*new;

	old = data->tokens->d_bot->addr_1;
	new = ft_substr(data->prompt, start, end);
	data->tokens->d_bot->addr_1 = ft_strjoin(old, new);
	free(old);
	free(new);
	return (_SUCCESS);
}

int	_token_word(t_pdata data, int *i)
{
	int	j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i]) && !_token_id(data->prompt[*i], _TOKENS))
		*i += 1;
	if (data->tokens && data->tokens->d_bot->flag)
		_join_strings(data, j, *i - j);
	else
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, j, (*i - j)), NULL, _WORD);
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]) && _token_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
	return (_SUCCESS);
}

int	_quote_proc(t_pdata data, int *i)
{
	char	type_quote;
	int		j;

	type_quote = data->prompt[*i];
	j = *i;
	while (data->prompt[*i] && data->prompt[*i] != '\n')
	{
		*i += 1;
		if (data->prompt[*i] && data->prompt[*i] == type_quote)
		{
			if (data->tokens && data->tokens->d_bot->flag)
				_join_strings(data, j + 1, *i - j - 1);
			else
				_dlst_push_back(&data->tokens, ft_substr(data->prompt, j + 1,
						(*i - j - 1)), NULL, type_quote);
			*i += 1;
			if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
				data->tokens->d_bot->flag = true;
			return (_SUCCESS);
		}
	}
	return (_err_print(_ERR_CLOSE, &type_quote, false, 2));
}

int	_wildcards_proc(t_pdata data, int *i)
{
	int	j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
	{
		if (_token_id(data->prompt[*i], _TOKENS) && data->prompt[*i] != '*')
			break ;
		*i += 1;
	}
	if (data->tokens && data->tokens->d_bot->flag)
	{
		data->tokens->d_bot->flag = false;
		_join_strings(data, j, *i - j);
	}
	else
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, j, *i - j), NULL,
			'*');
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
		data->tokens->d_bot->flag = true;
	return (_SUCCESS);
}

int	_is_varchr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

int	_dollar_proc(t_pdata data, int *i)
{
	int	j;

	if (data->prompt[*i + 1] && data->prompt[*i + 1] == '?')
	{
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL,
			'$');
		*i += 2;
	}
	else if (data->prompt[*i + 1] && _is_varchr(data->prompt[*i + 1]))
	{
		j = (*i)++;
		while (data->prompt[*i] && _is_varchr(data->prompt[*i]))
			*i += 1;
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, j, (*i - j)),
			NULL, '$');
	}
	else
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, (*i)++, 1), NULL,
			'W');
	return (_SUCCESS);
}

int	_sub_proc(t_pdata data, int *i)
{
	if (data->prompt[*i] == '(')
	{
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL,
			'(');
		data->args.parentheses++;
	}
	else if (data->prompt[*i] == ')')
	{
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL,
			')');
		data->args.parentheses++;
	}
	*i += 1;
	return (_SUCCESS);
}

int	_token_proc(t_pdata data, int *i)
{
	if (_token_id(data->prompt[*i], _OPERATORS) && _op_proc(data, i))
		return (_FAILURE);
	else if (_token_id(data->prompt[*i], _REDIRS) && _redir_proc(data, i))
		return (_FAILURE);
	else if (_token_id(data->prompt[*i], _SUBSHELL) && _sub_proc(data, i))
		return (_FAILURE);
	else if (_token_id(data->prompt[*i], _QUOTES) && _quote_proc(data, i))
		return (_FAILURE);
	else if (data->prompt[*i] == '$' && _dollar_proc(data, i))
		return (_FAILURE);
	else if (data->prompt[*i] == '*' && _wildcards_proc(data, i))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_found_pair(t_pdata data, int *i)
{
	*i += 1;
	while (data->prompt[*i] && data->prompt[*i] != '\n')
	{
		if (data->prompt[*i] == '(')
			_found_pair(data, i);
		if (data->prompt[*i] == ')')
		{
			*i += 1;
			return (_SUCCESS);
		}
		*i += 1;
	}
	return (_err_print(_ERR_CLOSE, ")", false, 2));
}

int	_check_sub(t_pdata data)
{
	int	i;

	i = 0;
	if (!*data->prompt)
		return (_SUCCESS);
	while (data->prompt[i] && data->prompt[i] != '\n')
	{
		if (data->prompt[i] == '(')
			_found_pair(data, &i);
		else
			i++;
	}
	return (_SUCCESS);
}

int	_check_top(t_pdata data)
{
	t_pnlst	tmp;

	if (!data->tokens)
		return (_SUCCESS);
	tmp = data->tokens->d_top;
	if (_token_id(tmp->x, _STX_OP))
		return (_err_print(_ERR_TOKEN, tmp->addr_1, true, 2));
	return (_SUCCESS);
}

int	_check_bot(t_pdata data)
{
	t_pnlst	tmp;

	if (!data->tokens)
		return (_FAILURE);
	tmp = data->tokens->d_bot;
	if (_token_id(tmp->x, _STX_OP) || _token_id(tmp->x, _TYP_REDIRS))
		return (_err_print(_ERR_NEWLINE, NULL, false, 2));
	if (data->args.parentheses % 2)
	{
		data->args.parentheses = 0;
		return (_err_print(_ERR_TOKEN, "(", true, 2));
	}
	data->args.parentheses = 0;
	if (_check_sub(data))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_first_token(t_pdata data, int *i)
{
	if (data->prompt[*i] && _token_id(data->prompt[*i], _TOKENS))
	{
		if (_token_proc(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
	{
		if (_token_word(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i])
		*i += 1;
	if (_check_top(data))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_token_list(t_pdata data)
{
	int	i;

	i = 0;
	if (_first_token(data, &i))
		return (_FAILURE);
	while (data->prompt[i] && data->prompt[i] != '\n')
	{
		if (data->prompt[i] && _token_id(data->prompt[i], _TOKENS))
		{
			if (_token_proc(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i] && !ft_isspace(data->prompt[i]))
		{
			if (_token_word(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i])
			i++;
	}
	if (_check_bot(data))
		return (_FAILURE);
	return (_SUCCESS);
}
