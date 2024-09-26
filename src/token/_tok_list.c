/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 17:05:04 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_tok_id(char a, char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == a)
// 			return (true);
// 	return (false);
// }

int	_quote_proc(t_pdata data, int *i)
{
	char	*str;
	char	*tmp;
	char	type_quote;
	int		j;

	type_quote = data->prompt[*i];
	j = *i;
	*i += 1;
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
		*i += 1;
	if (!data->prompt[*i])
		return (_err_print(_ERR_CLOSE, &type_quote, false, 2));
	if (data->tokens && data->tokens->d_bot->flag)
	{
		str = ft_substr(data->prompt, j + 1, (*i - j - 1));
		tmp = ft_strjoin(data->tokens->d_bot->addr_1, str);
		free(str);
		free(data->tokens->d_bot->addr_1);
		data->tokens->d_bot->addr_1 = tmp;
	}
	else
	{
		str = ft_substr(data->prompt, j + 1, (*i - j - 1));
		if (!str)
			return (_FAILURE);
		_dlst_push_back(&data->tokens, str, NULL, type_quote);
	}
	*i += 1;
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
	return (_SUCCESS);
}
// {
// if (data->prompt[*i] && data->prompt[*i] == type_quote)
// {
// str = _xpd_str(data, str);
// if (!str)
// 	return (_FAILURE);
// }
// }

int	_tok_word(t_pdata data, int *i)
{
	char	*str;
	char	*tmp;
	int		j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& !_tok_id(data->prompt[*i], _TOKENS))
		*i += 1;
	if (data->tokens && data->tokens->d_bot->flag)
	{
		str = ft_substr(data->prompt, j, (*i - j));
		tmp = ft_strjoin(data->tokens->d_bot->addr_1, str);
		free(str);
		free(data->tokens->d_bot->addr_1);
		data->tokens->d_bot->addr_1 = tmp;
	}
	else
	{
		str = ft_substr(data->prompt, j, (*i - j));
		if (!str)
			return (_FAILURE);
		_dlst_push_back(&data->tokens, str, NULL, _WORD);
		if (!data->tokens->d_bot->addr_1)
			return (_FAILURE);
	}
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& _tok_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
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

int	_hd_fill(t_pdata data, t_pnlst token)
{
	int		hd;
	char	*line;

	hd = open(token->addr_1, O_RDWR);
	while (true)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, token->next->addr_1))
			break ;
		line = _xpd_str(data, line);
		if (!line)
			return (_FAILURE);
		write(hd, line, ft_strlen(line));
		write(hd, "\n", 1);
		free(line);
	}
	token = token->next;
	return (_SUCCESS);
}

int	_here_doc_filler(t_pdata data)
{
	t_pnlst	tmp;

	tmp = data->tokens->d_top;
	while (tmp)
	{
		if (tmp->x == _HERE_DOC)
		{
			if (_hd_fill(data, tmp))
				return (_FAILURE);
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_tok_list(t_pdata data)
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
			if (_tok_word(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i])
			i++;
	}
	if (_check_bot(data))
		return (_FAILURE);
	if (_here_doc_filler(data))
		return (_FAILURE);
	return (_SUCCESS);
}
