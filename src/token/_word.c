/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _word.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:23:36 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/21 14:05:54 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_word(t_pdata data, int *i, int j)
{
	char	*str;
	char	*tmp;

	str = ft_substr(data->prompt, j, (*i - j));
	if (!str)
		return (_FAILURE);
	tmp = ft_strjoin(data->tokens->d_bot->addr_1, str);
	if (!tmp)
		return (_FAILURE);
	free(str);
	free(data->tokens->d_bot->addr_1);
	data->tokens->d_bot->addr_1 = tmp;
	return (_SUCCESS);
}

void	_convert_to_wildcard(t_ppnlst token)
{
	int		i;
	char	*str;
	char	quote;

	str = (*token)->addr_1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			while (str[++i] && str[i] != quote)
				;
		}
		if (str[i] == '*')
		{
			(*token)->x = '*';
			return ;
		}
	}
}

int	_new_word(t_pdata data, int *i, int j)
{
	char	*str;

	str = ft_substr(data->prompt, j, (*i - j));
	if (!str)
		return (_FAILURE);
	_dlst_push_back(&data->tokens, str, NULL, _WORD);
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	_convert_to_wildcard(&data->tokens->d_bot);
	return (_SUCCESS);
}

int	_word_proc(t_pdata data, int *i)
{
	int	j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& !_tok_id(data->prompt[*i], _TOKENS))
		*i += 1;
	if (data->tokens && data->tokens->d_bot->flag && data->tokens->d_bot->prev
		&& data->tokens->d_bot->prev->x == 'H')
	{
		if (_join_word(data, i, j))
			return (_FAILURE);
	}
	else
	{
		if (_new_word(data, i, j))
			return (_FAILURE);
	}
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& _tok_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
	return (_SUCCESS);
}
