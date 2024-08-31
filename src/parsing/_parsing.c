/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 11:56:06 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_pipe_lines(t_ppbtree node)
{
	t_pnlst	tmp;

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

int	_pars_args_proc(t_ppncmd cmd)
{
	int	i;

	i = _count_args((*cmd)->token);
	if (i && (_alloc((void **)&(*cmd)->args, sizeof(char *) * (i + 1))
			|| !(*cmd)->args))
		return (_ALLOC);
	return (_SUCCESS);
}

int	_pars_args_line(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	t_pnlst	tmp;
	int		i;

	if (!*cmd)
		return (_FAILURE);
	if (inside && _pars_args_proc(cmd))
		return (_FAILURE);
	i = 0;
	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (_tok_id(tmp->x, _TYP_REDIRS))
		{
			if (_pars_redirs(cmd, &tmp, inside))
				return (_FAILURE);
			continue ;
		}
		else if (inside && tmp->addr_1)
		{
			(*cmd)->args[i++] = ft_strdup(tmp->addr_1);
		}
		else if (!inside && tmp->addr_1)
		{
			data->_errno = 2;
			return (ft_dprintf(2, _ERR_TOKEN, tmp->addr_1), _FAILURE);
		}
		tmp = tmp->next;
	}
	if (inside && (*cmd)->args)
		(*cmd)->args[i] = NULL;
	if (tmp && tmp->x == ')' && tmp->next && _pars_args_line(data, cmd, &tmp->next, false))
		return (_FAILURE);
	return (_SUCCESS);
}
