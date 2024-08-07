/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 18:16:22 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pars_redir_in(t_pcmd cmd, t_ptok token)
{
	if (!cmd->redir._access && !access(token->value, F_OK | R_OK))
	{
		cmd->redir.in_name = token->value;
		return ;
	}
	cmd->redir.in_name = token->value;
	cmd->redir._access = true;
	return ;
}

int	_pars_redir_outt(t_pcmd cmd, t_ptok token)
{
	close(cmd->redir.fd[1]);
	cmd->redir.out_name = token->value;
	cmd->redir.fd[1] = open(cmd->redir.out_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd->redir.trunc = true;
	return (_SUCCESS);
}

int	_pars_redir_outa(t_pcmd cmd, t_ptok token)
{
	close(cmd->redir.fd[1]);
	cmd->redir.out_name = token->value;
	cmd->redir.fd[1] = open(cmd->redir.out_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd->redir.trunc = false;
	return (_SUCCESS);
}

void	_pars_redirs(t_pcmd cmd, t_ptok token)
{
	t_ptok	tmp;

	if (!cmd || !token)
		return ;
	tmp = token;
	while (tmp && tmp->type != _PIPE && !_tok_is(_TYP_SEP, tmp->type))
	{
		if (tmp->type == 'H')
		{
			cmd->redir.here_name = get_random_name();
			cmd->redir.here_limit = tmp->next->value;
		}
		if (tmp->type == '<')
			_pars_redir_in(cmd, tmp->next);
		else if (tmp->type == '>')
			_pars_redir_outt(cmd, tmp->next);
		else if (tmp->type == 'N')
			_pars_redir_outa(cmd, tmp->next);
		tmp = tmp->next;
	}
}
