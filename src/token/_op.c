/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:25:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 11:35:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_or(t_pdata data, int *i)
{
	_dllst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, _OR);
	*i += 2;
	if (!data->tokens->d_bot->prev || (data->tokens->d_bot->prev
			&& _token_id(data->tokens->d_bot->prev->x, _STX_OP)))
	{
		ft_dprintf(2, _ERR_TOKEN, "||");
		return (_SYNTAX);
	}
	return (_SUCCESS);
}

int	_tok_and(t_pdata data, int *i)
{
	int	count;

	count = 0;
	while (data->prompt[*i + count] == '&' && count < 2)
		count++;
	_dllst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, _AND);
	*i += 2;
	if (count == 1)
	{
		ft_dprintf(2, _ERR_TOKEN, "&");
		return (_SYNTAX);
	}
	else if (!data->tokens->d_bot->prev || (data->tokens->d_bot->prev && _token_id(data->tokens->d_bot->prev->x, _STX_OP)))
	{
		ft_dprintf(2, _ERR_TOKEN, "&&");
		return (_SYNTAX);
	}
	return (_SUCCESS);
}

int	_tok_pipe(t_pdata data, int *i)
{
	_dllst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL,
		_PIPE);
	*i += 1;
	if (!data->tokens->d_bot->prev || (data->tokens->d_bot->prev && _token_id(data->tokens->d_bot->prev->x, _STX_OP)))
	{
		ft_dprintf(2, _ERR_TOKEN, "|");
		return (_SYNTAX);
	}
	return (_SUCCESS);
}

int	_op_proc(t_pdata data, int *i)
{
	int	count;

	count = 0;
	if (data->prompt[*i] == '&')
		return (_tok_and(data, i));
	else if (data->prompt[*i] == '|')
	{
		while (data->prompt[*i + count] == '|' && count < 2)
			count++;
		if (count == 1)
			return (_tok_pipe(data, i));
		else
			return (_tok_or(data, i));
	}
	return (_SUCCESS);
}
