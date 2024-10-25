/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:12:25 by moha              #+#    #+#             */
/*   Updated: 2024/10/25 17:36:38 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			if (_found_pair(data, &i))
				return (_FAILURE);
		}
		else
			i++;
	}
	return (_SUCCESS);
}

int	_check_anb_sub(t_pnlst token)
{
	t_pnlst	tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->x == '(' && tmp->prev && (_tok_id(tmp->prev->x, _JOINERS)
				|| tmp->prev->x == 'W'))
			return (_err_print(_ERR_TOKEN, tmp->next->addr_1, true, 2));
		if (tmp && tmp->x == ')')
		{
			tmp = tmp->next;
			while (tmp && !_tok_id(tmp->x, _AFTER_SUB))
			{
				if (tmp && _tok_id(tmp->x, _REDIRS))
					tmp = tmp->next->next;
				else if (tmp && (tmp->x == 'W' || _tok_id(tmp->x, _JOINERS)))
					return (_err_print(_ERR_TOKEN, tmp->addr_1, true, 2));
				tmp = tmp->next;
			}
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_check_top(t_pdata data)
{
	t_pnlst	tmp;

	if (!data->tokens)
		return (_SUCCESS);
	tmp = data->tokens->d_top;
	if (_tok_id(tmp->x, _STX_OP))
		return (_err_print(_ERR_TOKEN, tmp->addr_1, true, 2));
	return (_SUCCESS);
}

int	_check_bot(t_pdata data)
{
	t_pnlst	tmp;

	if (!data->tokens)
		return (_FAILURE);
	tmp = data->tokens->d_bot;
	if (_tok_id(tmp->x, _STX_OP) || _tok_id(tmp->x, _TYP_REDIRS))
		return (_err_print(_ERR_NEWLINE, NULL, false, 2));
	if (data->args.parnth % 2)
	{
		data->args.parnth = 0;
		return (_err_print(_ERR_TOKEN, "(", true, 2));
	}
	data->args.parnth = 0;
	if (_check_sub(data))
		return (_FAILURE);
	if (_check_anb_sub(data->tokens->d_top))
		return (_FAILURE);
	return (_SUCCESS);
}
