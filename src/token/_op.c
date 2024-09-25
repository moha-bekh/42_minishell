/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:25:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/25 22:49:38 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_or(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, _OR);
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	*i += 2;
	if (!data->tokens->d_bot->prev || (data->tokens->d_bot->prev
			&& _tok_id(data->tokens->d_bot->prev->x, _STX_OP)))
		return (_err_print(_ERR_TOKEN, "||", true, 2));
	return (_SUCCESS);
}

int	_tok_and(t_pdata data, int *i)
{
	int	count;

	count = 0;
	while (data->prompt[*i + count] == '&' && count < 2)
		count++;
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, _AND);
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	*i += 2;
	if (count == 1)
		return (_err_print(_ERR_TOKEN, "&", true, 2));
	else if (!data->tokens->d_bot->prev || (data->tokens->d_bot->prev
			&& _tok_id(data->tokens->d_bot->prev->x, _STX_OP)))
		return (_err_print(_ERR_TOKEN, "&&", true, 2));
	return (_SUCCESS);
}

int	_tok_pipe(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, (*i)++, 1), NULL,
		_PIPE);
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	if (!data->tokens->d_bot->prev || (data->tokens->d_bot->prev
			&& _tok_id(data->tokens->d_bot->prev->x, _STX_OP)))
		return (_err_print(_ERR_TOKEN, "|", true, 2));
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
