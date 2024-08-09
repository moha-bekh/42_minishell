/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/09 13:11:03 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_redir_in(t_pcmd cmd, t_ptok token)
{
	if (!cmd->redir._access && !access(token->value, F_OK | R_OK))
	{
		cmd->redir.in_name = token->value;
		return (_SUCCESS);
	}
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(token->value, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	cmd->redir.in_name = token->value;
	cmd->redir._access = true;
	return (_FAILURE);
}

int	_pars_redir_outt(t_pcmd cmd, t_ptok token)
{
	cmd->redir.out_name = token->value;
	cmd->redir.fd[1] = open(cmd->redir.out_name, O_RDWR | O_CREAT | O_TRUNC,
			0644);
	cmd->redir.trunc = true;
	close(cmd->redir.fd[1]);
	return (_SUCCESS);
}

int	_pars_redir_outa(t_pcmd cmd, t_ptok token)
{
	cmd->redir.out_name = token->value;
	cmd->redir.fd[1] = open(cmd->redir.out_name, O_RDWR | O_CREAT | O_APPEND,
			0644);
	cmd->redir.trunc = false;
	close(cmd->redir.fd[1]);
	return (_SUCCESS);
}

int	_pars_redirs(t_pcmd cmd, t_ptok token)
{
	t_ptok	tmp;

	if (!cmd || !token)
		return (_FAILURE);
	tmp = token;
	while (tmp && tmp->type != _PIPE && !_tok_is(_TYP_SEP, tmp->type))
	{
		if (tmp->type == 'H')
		{
			cmd->redir.here_name = get_random_name();
			cmd->redir.here_limit = tmp->next->value;
		}
		if (tmp->type == '<')
		{
			if (_pars_redir_in(cmd, tmp->next))
				return (_FAILURE);
		}
		else if (tmp->type == '>')
			_pars_redir_outt(cmd, tmp->next);
		else if (tmp->type == 'N')
			_pars_redir_outa(cmd, tmp->next);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
