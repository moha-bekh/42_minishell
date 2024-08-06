/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:25:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/06 06:31:07 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_or(t_pdata data, int *i)
{
	if (!data->input[*i + 2] || _tok_is(_STX_ERR_OP, data->input[*i + 2]))
		return (_tok_stx_err('|', 1));
	data->tok = _tok_push_back(data->tok, _OR, ft_substr(data->input, *i, 2));
	*i += 2;
	return (_SUCCESS);
}

int	_tok_and(t_pdata data, int *i)
{
	if (!data->input[*i + 2] || _tok_is(_STX_ERR_OP, data->input[*i + 2]))
		return (_tok_stx_err('&', 1));
	data->tok = _tok_push_back(data->tok, _AND, ft_substr(data->input, *i, 2));
	*i += 2;
	return (_SUCCESS);
}

int	_op_proc(t_pdata data, int *i)
{
	if (data->input[*i] == '&')
	{
		if (!data->input[*i + 1])
			return (_tok_stx_err('&', 1));
		else
			return (_tok_and(data, i));
	}
	else if (data->input[*i] == '|')
	{
		if (!data->input[*i + 1])
			return (_tok_stx_err('|', 1));
		else if (data->input[*i + 1] != '|')
		{
			data->tok = _tok_push_back(data->tok, _PIPE, ft_substr(data->input, *i, 1));
			*i += 1;
		}
		else
			return (_tok_or(data, i));
	}
	return (_SUCCESS);
}
