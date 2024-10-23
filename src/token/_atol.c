/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _atol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/23 01:52:27 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_first_tok(t_pdata data, int *i)
{
	if (data->prompt[*i] && _tok_id(data->prompt[*i], _TOKENS))
	{
		if (_tok_proc(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
	{
		if (_word_proc(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i])
		*i += 1;
	if (_check_top(data))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_atol(t_pdata data)
{
	int	i;

	i = 0;
	if (!data->prompt)
		return (_FAILURE);
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
			if (_word_proc(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i])
			i++;
	}
	if (_check_bot(data) || _join_limiters(data) || _here_doc_filler(data))
		return (_FAILURE);
	return (_SUCCESS);
}
