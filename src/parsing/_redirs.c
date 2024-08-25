/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/25 00:31:06 by moha             ###   ########.fr       */
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

int	_pars_redir_outt(t_pcmd *cmd, t_pnlst token)
{
	(*cmd)->redirs.out_name = (char *)token->addr_1;
	(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((*cmd)->redirs.fd[1] < 0)
	{
		ft_dprintf(2, "bash: %s: Is a directory\n", (*cmd)->redirs.out_name);
		return (_FAILURE);
	}
	(*cmd)->redirs.out_trunc = true;
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_pars_redir_outa(t_pcmd *cmd, t_pnlst token)
{
	(*cmd)->redirs.out_name = (char *)token->addr_1;
	(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	if ((*cmd)->redirs.fd[1] < 0)
	{
		ft_dprintf(2, "bash: %s: Is a directory\n", (*cmd)->redirs.out_name);
		return (_FAILURE);
	}
	(*cmd)->redirs.out_trunc = false;
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_pars_redirs(t_pcmd *cmd, t_pnlst token)
{
	while (token && token->x != _PIPE && !_token_id(token->x, _TYP_SEP))
	{
		if (token->x == 'H')
		{
			(*cmd)->redirs.here_name = get_random_name();
			(*cmd)->redirs.here_limit = token->next->addr_1;
		}
		else if (token->x == '<' && _pars_redir_in(cmd, token->next))
			return (_FAILURE);
		else if (token->x == '>' && _pars_redir_outt(cmd, token->next))
			return (_FAILURE);
		else if (token->x == 'N' && _pars_redir_outa(cmd, token->next))
			return (_FAILURE);
		token = token->next;
	}
	return (_SUCCESS);
}
