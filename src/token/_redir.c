/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:25:01 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/09 16:33:03 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_redir_heredoc(t_pdata data, int *i)
{
	char	*path;

	if (++data->args.nb_hd > 16)
	{
		ft_dprintf(2, _ERR_HEREDOC);
		_data_clear(data);
		exit(2);
	}
	_dlst_push_back(&data->tokens, _get_rname(), NULL, _HERE_DOC);
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	path = ft_strjoin("/tmp/", data->tokens->d_bot->addr_1);
	if (!path)
		return (_FAILURE);
	free(data->tokens->d_bot->addr_1);
	data->tokens->d_bot->addr_1 = path;
	*i += 2;
	if (data->tokens && data->tokens->d_bot->prev
		&& _tok_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, "<<", true, 2));
	return (_SUCCESS);
}

int	_redir_in(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, (*i)++, 1), NULL,
		'<');
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	if (_tok_id(data->prompt[*i], _OPERATORS))
		return (_err_print(_ERR_TOKEN, &data->prompt[*i], true, 2));
	if (data->tokens && data->tokens->d_bot->prev
		&& _tok_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, "<", true, 2));
	return (_SUCCESS);
}

int	_redir_outa(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, *i, 2), NULL,
		_REDIR_OUTA);
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	*i += 2;
	if (data->tokens && data->tokens->d_bot->prev
		&& _tok_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, ">>", true, 2));
	return (_SUCCESS);
}

int	_redir_outt(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, ft_substr(data->prompt, (*i)++, 1), NULL,
		'>');
	if (!data->tokens->d_bot->addr_1)
		return (_FAILURE);
	if (data->tokens && data->tokens->d_bot->prev
		&& _tok_id(data->tokens->d_bot->prev->x, _TYP_REDIRS))
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
