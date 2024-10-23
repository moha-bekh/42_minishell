/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _quote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:25:23 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/23 01:52:48 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_quote_join(t_pdata data, int *i, int j)
{
	char	*str;
	char	*tmp;
	char	type_quote;

	type_quote = data->prompt[j];
	str = ft_substr(data->prompt, j + 1, (*i - j - 1));
	if (!str)
		return (_FAILURE);
	tmp = ft_strjoin(data->tokens->d_bot->addr_1, str);
	if (!tmp)
		return (_FAILURE);
	free(str);
	free(data->tokens->d_bot->addr_1);
	data->tokens->d_bot->addr_1 = tmp;
	data->tokens->d_bot->x = type_quote;
	return (_SUCCESS);
}

int	_quote_proc(t_pdata data, int *i)
{
	char	*str;
	char	type_quote;
	int		j;

	j = *i;
	type_quote = data->prompt[j];
	*i += 1;
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
		*i += 1;
	if (!data->prompt[*i])
		return (_err_print(_ERR_CLOSE, &type_quote, false, 2));
	{
		str = ft_substr(data->prompt, j + 1, (*i - j - 1));
		if (!str)
			return (_FAILURE);
		_dlst_push_back(&data->tokens, str, NULL, type_quote);
	}
	*i += 1;
	_join_flag(data, *i);
	return (_SUCCESS);
}

// if (data->tokens && data->tokens->d_bot->flag && data->tokens->d_bot->prev
	// && data->tokens->d_bot->prev->x == 'H' && _quote_join(data, i, j))
// 	return (_FAILURE);
// else