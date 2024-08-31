/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:12:52 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 16:16:08 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		j = ++(*i);
		while (data->prompt[*i] && _is_varchr(data->prompt[*i]))
			*i += 1;
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, j, (*i - j)),
			NULL, '$');
	}
	else
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, (*i)++, 1), NULL,
			'W');
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
		data->tokens->d_bot->flag = true;
	return (_SUCCESS);
}

int	_wildcards_proc(t_pdata data, int *i)
{
	char	*str;
	int		j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
	{
		if (_tok_id(data->prompt[*i], _TOKENS) && data->prompt[*i] != '*')
			break ;
		*i += 1;
	}
	str = ft_substr(data->prompt, j, *i - j);
	_dlst_push_back(&data->tokens, str, NULL, '*');
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& _tok_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
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

int	_tok_proc(t_pdata data, int *i)
{
	if (_tok_id(data->prompt[*i], _OPERATORS) && _op_proc(data, i))
		return (_FAILURE);
	else if (_tok_id(data->prompt[*i], _REDIRS) && _redir_proc(data, i))
		return (_FAILURE);
	else if (_tok_id(data->prompt[*i], _SUBSHELL) && _sub_proc(data, i))
		return (_FAILURE);
	else if (_tok_id(data->prompt[*i], _QUOTES) && _quote_proc(data, i))
		return (_FAILURE);
	else if (data->prompt[*i] == '$' && _dollar_proc(data, i))
		return (_FAILURE);
	else if (data->prompt[*i] == '*' && _wildcards_proc(data, i))
		return (_FAILURE);
	return (_SUCCESS);
}
