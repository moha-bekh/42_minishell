/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 16:47:12 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_pipe_lines(t_pbtree *node)
{
	t_pnlst	tmp;

	if (!*node)
		return (_FAILURE);
	_cmd_push_back(&(*node)->cmd_line, (*node)->token);
	tmp = (*node)->token;
	while (tmp && (!(*node)->root || ((*node)->root
				&& tmp != (*node)->root->token)))
	{
		if (tmp->x == _PIPE)
			_cmd_push_back(&(*node)->cmd_line, tmp->next);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_pars_outside_redirs(t_pcmd *cmd, t_pnlst *token)
{
	int	fd;

	while (token && (*token)->x != _PIPE && !_token_id((*token)->x, _TYP_SEP))
	{
		if (_token_id((*token)->x, _TYP_REDIRS))
		{
			if (_pars_redirs(cmd, *token, false))
				return (_FAILURE);
			else
			{
				fd = open((char *)(*token)->next->addr_1, O_RDWR | O_CREAT | O_TRUNC, 0644);
				close(fd);
			}
			(*token) = (*token)->next;
			if (*token)
				(*token) = (*token)->next;
			continue ;
		}
		else
			return (ft_dprintf(2, _ERR_TOKEN, (char *)(*token)->addr_1),
				_FAILURE);
		(*token) = (*token)->next;
	}
	return (_SUCCESS);
}

int	_pars_inside_redirs(t_pcmd *cmd, t_pnlst *token)
{
	if (_token_id((*token)->x, _TYP_REDIRS))
	{
		if (_pars_redirs(cmd, (*token), true))
			return (_FAILURE);
		(*token) = (*token)->next;
		if (*token)
			(*token) = (*token)->next;
	}
	return (_SUCCESS);
}

int	_pars_args_line(t_pcmd *cmd)
{
	t_pnlst	tmp;
	int		i;

	if (!*cmd)
		return (_FAILURE);
	i = _count_args((*cmd)->token);
	if (i && (_alloc((void **)&(*cmd)->args, sizeof(char *) * (i + 1)) || !(*cmd)->args))
		return (_FAILURE);
	i = 0;
	tmp = (*cmd)->token;
	while (tmp && tmp->x != _PIPE && !_token_id(tmp->x, _TYP_SEP))
	{
		if (_token_id(tmp->x, _TYP_REDIRS) && !_pars_inside_redirs(cmd, &tmp))
			continue ;
		(*cmd)->args[i++] = ft_strdup((char *)tmp->addr_1);
		tmp = tmp->next;
	}
	if (tmp && tmp->x == ')' && tmp->next)
		_pars_outside_redirs(cmd, &tmp->next);
	if ((*cmd)->args)
		(*cmd)->args[i] = NULL;
	return (_SUCCESS);
}
