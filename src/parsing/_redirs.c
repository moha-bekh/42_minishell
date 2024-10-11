/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 19:51:56 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_redir_in(t_ppncmd cmd, t_pnlst token)
{
	if ((*cmd)->redirs.in_access || (*cmd)->redirs.out_access)
		return (_SUCCESS);
	if (!token->addr_1)
	{
		(*cmd)->redirs.in_name = token->addr_2;
		(*cmd)->redirs.in_access = true;
		return (_SUCCESS);
	}
	if (!access(token->addr_1, F_OK | R_OK))
		(*cmd)->redirs.in_access = true;
	(*cmd)->redirs.in_name = token->addr_1;
	return (_SUCCESS);
}

int	_pars_redir_outt(t_ppncmd cmd, t_pnlst token, bool inside)
{
	if ((*cmd)->redirs.out_access || (*cmd)->redirs.in_access)
		return (_SUCCESS);
	if (!token->addr_1)
	{
		(*cmd)->redirs.out_name = token->addr_2;
		(*cmd)->redirs.out_access = true;
		return (_SUCCESS);
	}
	if (access(token->addr_1, F_OK))
	{
		(*cmd)->redirs.fd[1] = open(token->addr_1, _O_RWCT);
		if ((*cmd)->redirs.fd[1] < 0)
			return (perror("open"), _FAILURE);
		close((*cmd)->redirs.fd[1]);
	}
	if (access(token->addr_1, W_OK))
		(*cmd)->redirs.out_access = true;
	if (inside || (!inside && !(*cmd)->redirs.out_inside))
	{
		if (inside)
			(*cmd)->redirs.out_inside = true;
		(*cmd)->redirs.out_name = token->addr_1;
		(*cmd)->redirs.out_trunc = true;
	}
	return (_SUCCESS);
}

int	_pars_redir_outa(t_ppncmd cmd, t_pnlst token, bool inside)
{
	if ((*cmd)->redirs.out_access || (*cmd)->redirs.in_access)
		return (_SUCCESS);
	if (!token->addr_1)
	{
		(*cmd)->redirs.out_name = token->addr_2;
		(*cmd)->redirs.out_access = true;
		return (_SUCCESS);
	}
	if (access(token->addr_1, F_OK))
	{
		(*cmd)->redirs.fd[1] = open(token->addr_1, _O_RWCT);
		if ((*cmd)->redirs.fd[1] < 0)
			return (perror("open"), _FAILURE);
		close((*cmd)->redirs.fd[1]);
	}
	if (access(token->addr_1, W_OK))
		(*cmd)->redirs.out_access = true;
	if (inside || (!inside && !(*cmd)->redirs.out_inside))
	{
		if (inside)
			(*cmd)->redirs.out_inside = true;
		(*cmd)->redirs.out_name = token->addr_1;
		(*cmd)->redirs.out_trunc = false;
	}
	return (_SUCCESS);
}

int	_pars_heredoc(t_ppncmd cmd, t_pnlst token, bool inside)
{
	if (inside || (!inside && !(*cmd)->redirs.here_inside))
	{
		if (inside)
			(*cmd)->redirs.here_inside = true;
		(*cmd)->redirs.in_name = token->addr_1;
	}
	return (_SUCCESS);
}

int	_pars_redirs(t_ppncmd cmd, t_ppnlst token, bool inside)
{
	if (!inside && !_tok_id((*token)->x, _TYP_REDIRS) && !_tok_id((*token)->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, (*token)->addr_1, true, 1));
	if ((*token)->x == 'H' && _pars_heredoc(cmd, *token, inside))
		return (_FAILURE);
	else if ((*token)->x == '<' && _pars_redir_in(cmd, (*token)->next))
		return (_FAILURE);
	else if ((*token)->x == '>' && _pars_redir_outt(cmd, (*token)->next,
			inside))
		return (_FAILURE);
	else if ((*token)->x == 'N' && _pars_redir_outa(cmd, (*token)->next,
			inside))
		return (_FAILURE);
	return (_SUCCESS);
}
