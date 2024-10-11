/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:12:25 by moha              #+#    #+#             */
/*   Updated: 2024/10/11 19:44:57 by mbekheir         ###   ########.fr       */
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
	return (_SUCCESS);
}
