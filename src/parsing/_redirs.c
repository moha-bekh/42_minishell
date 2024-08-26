/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 20:56:52 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_redir_in(t_pcmd *cmd, t_pnlst token)
{
	if ((*cmd)->redirs.in_access)
	{
		ft_dprintf(2, "bash: %s: No such file or directory\n",
			(char *)token->addr_1);
		return (_SUCCESS);
	}
	else if (!(*cmd)->redirs.in_access && !access((char *)token->addr_1,
			F_OK | R_OK))
	{
		(*cmd)->redirs.in_name = (char *)token->addr_1;
		return (_SUCCESS);
	}
	(*cmd)->redirs.in_name = (char *)token->addr_1;
	(*cmd)->redirs.in_access = true;
	return (_SUCCESS);
}

int	_pars_redir_outt(t_pcmd *cmd, t_pnlst token, bool inside)
{
	(*cmd)->redirs.fd[1] = open((char *)token->addr_1, _O_RWCT);
	if ((*cmd)->redirs.fd[1] < 0)
	{
		ft_dprintf(2, "bash: %s: Is a directory\n", (char *)token->addr_1);
		return (_FAILURE);
	}
	if (inside || (!inside && !(*cmd)->redirs.out_inside))
	{
		if (inside)
			(*cmd)->redirs.out_inside = true;
		(*cmd)->redirs.out_name = (char *)token->addr_1;
		(*cmd)->redirs.out_trunc = true;
	}
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_pars_redir_outa(t_pcmd *cmd, t_pnlst token, bool inside)
{
	(*cmd)->redirs.fd[1] = open((char *)token->addr_1, _O_RWCA);
	if ((*cmd)->redirs.fd[1] < 0)
	{
		ft_dprintf(2, "bash: %s: Is a directory\n", (char *)token->addr_1);
		return (_FAILURE);
	}
	if (inside || (!inside && !(*cmd)->redirs.out_inside))
	{
		if (inside)
			(*cmd)->redirs.out_inside = true;
		(*cmd)->redirs.out_name = (char *)token->addr_1;
		(*cmd)->redirs.out_trunc = false;
	}
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}
int	_pars_heredoc(t_pcmd *cmd, t_pnlst token)
{
	if (!(*cmd)->redirs.here_limit)
	{
		(*cmd)->redirs.here_limit = malloc(sizeof(char *) * 17);
		if (!(*cmd)->redirs.here_limit)
			return (_FAILURE);
	}
	if ((*cmd)->redirs.here_name)
	{
		free((*cmd)->redirs.here_name);
		(*cmd)->redirs.here_name = NULL;
	}
	(*cmd)->redirs.here_name = get_random_name();
	(*cmd)->redirs.here_limit[(*cmd)->redirs.idx_limit++] = (char *)token->addr_1;
	return (_SUCCESS);
}

int	_pars_redirs(t_pcmd *cmd, t_pnlst *token, bool inside)
{
	while (*token && (*token)->x != _PIPE && !_token_id((*token)->x, _TYP_SEP))
	{
		if (!inside && !_token_id((*token)->x, _TYP_REDIRS)
			&& !_token_id((*token)->prev->x, _TYP_REDIRS))
			return (ft_dprintf(2, _ERR_TOKEN, (char *)(*token)->addr_1),
				_FAILURE);
		if ((*token)->x == 'H' && _pars_heredoc(cmd, (*token)->next))
			return (_FAILURE);
		else if ((*token)->x == '<' && _pars_redir_in(cmd, (*token)->next))
			return (_FAILURE);
		else if ((*token)->x == '>' && _pars_redir_outt(cmd, (*token)->next,
				inside))
			return (_FAILURE);
		else if ((*token)->x == 'N' && _pars_redir_outa(cmd, (*token)->next,
				inside))
			return (_FAILURE);
		(*token) = (*token)->next;
	}
	return (_SUCCESS);
}
