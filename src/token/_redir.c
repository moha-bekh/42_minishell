/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:25:01 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 16:43:03 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_redir_heredoc(t_pdata data, int *i)
{
	if (++data->args.here_doc > 16)
	{
		ft_dprintf(2, _ERR_HEREDOC);
		_data_clear(data);
		exit(2);
	}
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL,
		_HERE_DOC);
	*i += 2;
	if (data->tokens && data->tokens->d_bot->prev
		&& _token_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, "<<", true, 2));
	return (_SUCCESS);
}

int	_redir_in(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL, '<');
	*i += 1;
	if (data->tokens && data->tokens->d_bot->prev
		&& _token_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, "<", true, 2));
	return (_SUCCESS);
}

int	_redir_outa(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL, _REDIR_OUTA);
	*i += 2;
	if (data->tokens && data->tokens->d_bot->prev && _token_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, ">>", true, 2));
	return (_SUCCESS);
}

int	_redir_outt(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 1), NULL, '>');
	*i += 1;
	if (data->tokens && data->tokens->d_bot->prev
		&& _token_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, ">", true, 2));
	return (_SUCCESS);
}

int	_redir_proc(t_pdata data, int *i)
{
	if (data->prompt[*i] == '<')
	{
		if (data->prompt[*i + 1] == '<')
			return (_redir_heredoc(data, i));
		return (_redir_in(data, i));
	}
	else if (data->prompt[*i] == '>')
	{
		if (data->prompt[*i + 1] == '>')
			return (_redir_outa(data, i));
		return (_redir_outt(data, i));
	}
	return (_SUCCESS);
}
