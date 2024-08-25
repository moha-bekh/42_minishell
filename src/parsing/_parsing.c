/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/25 00:30:58 by moha             ###   ########.fr       */
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
	while (tmp && (!(*node)->root || ((*node)->root && tmp != (*node)->root->token)))
	{
		if (tmp->x == _PIPE)
			_cmd_push_back(&(*node)->cmd_line, tmp->next);
		tmp = tmp->next;
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
	tmp = (*cmd)->token;
	i = 0;
	while (tmp && tmp->x != _PIPE && !_token_id(tmp->x, _TYP_SEP))
	{
		if (_token_id(tmp->x, _TYP_REDIRS))
		{
			if (_pars_redirs(cmd, tmp))
				return (_FAILURE);
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		(*cmd)->args[i] = ft_strdup((char *)tmp->addr_1);
		i++;
		tmp = tmp->next;
	}
	if ((*cmd)->args)
		(*cmd)->args[i] = NULL;
	return (_SUCCESS);
}
