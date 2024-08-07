/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:25:01 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 17:58:41 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_redir_heredoc(t_pdata data, int *i)
{
	if (!data->input[*i + 2])
		return (ft_putstr_fd(_STX_ERR_REDIR, STDERR_FILENO), 2);
	if (_tok_is(_STX_ERR_HERE_DOC, data->input[*i + 2]))
		return (_tok_stx_err(data->input[*i + 2], 1));
	data->tok = _tok_push_back(data->tok, _HERE_DOC, ft_substr(data->input, *i,
				2));
	*i += 2;
	return (_SUCCESS);
}

int	_redir_in(t_pdata data, int *i)
{
	if (_tok_is(_STX_ERR_REDIR_IN, data->input[*i + 1]))
		return (_tok_stx_err(data->input[*i + 1], 1));
	data->tok = _tok_push_back(data->tok, '<', ft_substr(data->input, *i, 1));
	*i += 1;
	return (_SUCCESS);
}

int	_redir_outa(t_pdata data, int *i)
{
	if (!data->input[*i + 2])
		return (ft_putstr_fd(_STX_ERR_REDIR, STDERR_FILENO), 2);
	if (_tok_is(_STX_ERR_REDIR_OUTA, data->input[*i + 2]))
		return (_tok_stx_err(data->input[*i + 2], 1));
	data->tok = _tok_push_back(data->tok, _REDIR_OUTA, ft_substr(data->input,
				*i, 2));
	*i += 2;
	return (_SUCCESS);
}

int	_redir_outt(t_pdata data, int *i)
{
	if (_tok_is(_STX_ERR_REDIR_OUTT, data->input[*i + 1]))
		return (_tok_stx_err(data->input[*i + 1], 1));
	data->tok = _tok_push_back(data->tok, '>', ft_substr(data->input, *i, 1));
	*i += 1;
	return (_SUCCESS);
}

int	_redir_proc(t_pdata data, int *i)
{
	if (data->input[*i] == '<')
	{
		if (!data->input[*i + 1])
			return (ft_putstr_fd(_STX_ERR_REDIR, STDERR_FILENO), 2);
		else if (data->input[*i + 1] == '<')
			return (_redir_heredoc(data, i));
		return (_redir_in(data, i));
	}
	else if (data->input[*i] == '>')
	{
		if (!data->input[*i + 1])
			return (ft_putstr_fd(_STX_ERR_REDIR, STDERR_FILENO), 2);
		else if (data->input[*i + 1] == '>')
			return (_redir_outa(data, i));
		return (_redir_outt(data, i));
	}
	return (_SUCCESS);
}
