/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 16:16:19 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_id(char a, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == a)
			return (true);
	return (false);
}

int	_quote_proc(t_pdata data, int *i)
{
	char	*str;
	char	type_quote;
	int		j;

	type_quote = data->prompt[*i];
	j = *i;
	while (data->prompt[*i] && data->prompt[*i] != '\n')
	{
		*i += 1;
		if (data->prompt[*i] && data->prompt[*i] == type_quote)
		{
			str = ft_substr(data->prompt, j + 1, (*i - j - 1));
			_dlst_push_back(&data->tokens, str, NULL, type_quote);
			*i += 1;
			if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
				data->tokens->d_bot->flag = true;
			return (_SUCCESS);
		}
	}
	return (_err_print(_ERR_CLOSE, &type_quote, false, 2));
}

int	_tok_word(t_pdata data, int *i)
{
	char	*str;
	int		j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& !_tok_id(data->prompt[*i], _TOKENS))
		*i += 1;
	str = ft_substr(data->prompt, j, (*i - j));
	_dlst_push_back(&data->tokens, str, NULL, _WORD);
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& _tok_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
	return (_SUCCESS);
}

int	_first_tok(t_pdata data, int *i)
{
	if (data->prompt[*i] && _tok_id(data->prompt[*i], _TOKENS))
	{
		if (_tok_proc(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
	{
		if (_tok_word(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i])
		*i += 1;
	if (_check_top(data))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_tok_list(t_pdata data)
{
	int	i;

	i = 0;
	if (_first_tok(data, &i))
		return (_FAILURE);
	while (data->prompt[i] && data->prompt[i] != '\n')
	{
		if (data->prompt[i] && _tok_id(data->prompt[i], _TOKENS))
		{
			if (_tok_proc(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i] && !ft_isspace(data->prompt[i]))
		{
			if (_tok_word(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i])
			i++;
	}
	if (_check_bot(data))
		return (_FAILURE);
	return (_SUCCESS);
}
