/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dollar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:36:10 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/18 13:31:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_errno_(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, '$');
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	*i += 2;
	return (_SUCCESS);
}

int	_var_(t_pdata data, int *i)
{
	int	j;

	if (data->tokens && data->tokens->d_bot->x == 'H')
	{
		j = (*i);
		(*i) += 1;
	}
	else
		j = ++(*i);
	while (data->prompt[*i] && _is_varchr(data->prompt[*i]))
		*i += 1;
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, j, (*i - j)), NULL,
		'$');
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
	return (_SUCCESS);
}

int	_dollar_proc(t_pdata data, int *i)
{
	int	j;

	if (data->prompt[*i + 1] && data->prompt[*i + 1] == '?')
		return (_errno_(data, i));
	else if (data->prompt[*i + 1] && _is_varchr(data->prompt[*i + 1]))
		return (_var_(data, i));
	else
	{
		j = *i;
		while (data->prompt[++(*i)] && !ft_isspace(data->prompt[*i])
			&& data->prompt[*i] != '$')
			*i += 1;
		_dlst_push_back(&data->tokens, ft_substr(data->prompt, j, (*i - j)),
			NULL, 'W');
		if (!data->tokens->d_bot->addr_1)
			return (_FAILURE);
	}
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
	return (_SUCCESS);
}
