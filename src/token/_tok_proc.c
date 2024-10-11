/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:12:52 by moha              #+#    #+#             */
/*   Updated: 2024/10/11 16:37:47 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_errno_proc(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, '$');
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	*i += 2;
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
	if (!str)
		return (_FAILURE);
	_dlst_push_back(&data->tokens, str, NULL, '*');
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& _tok_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
	return (_SUCCESS);
}

int	_sub_proc(t_pdata data, int *i)
{
	char	x;

	x = data->prompt[*i + 1];
	if (x == '(' || x == ')')
		return (_err_print(_ERR_TOKEN, &x, true, 2));
	if (data->prompt[*i] == '(')
	{
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL,
			'(');
		if (!data->tokens->d_bot->addr_1)
			return (_FAILURE);
		data->args.parnth++;
	}
	else if (data->prompt[*i] == ')')
	{
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL,
			')');
		if (!data->tokens->d_bot->addr_1)
			return (_FAILURE);
		data->args.parnth++;
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
