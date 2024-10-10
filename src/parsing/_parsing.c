/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 01:45:25 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_pipe_lines(t_ppbtree node)
{
	t_pnlst	tmp;

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

int	_pars_args_proc(t_ppncmd cmd)
{
	int	i;

	if (!*cmd)
		return (_FAILURE);
	(*cmd)->args = NULL;
	i = _nb_lnargs((*cmd)->token);
	if (i && (_alloc((void **)&(*cmd)->args, sizeof(char *) * (i + 1)) || !(*cmd)->args))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_pars_args_line(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	t_pnlst	tmp;
	int		i;
	char	*str;

	if (!*cmd)
		return (_FAILURE);
	if (inside && _pars_args_proc(cmd))
		return (_FAILURE);
	i = 0;
	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		str = tmp->addr_1;
		if (_tok_id(tmp->x, _TYP_REDIRS))
		{
			if (_pars_redirs(data, cmd, &tmp, inside))
			{
				data->_errno = 1;
				return (_FAILURE);
			}
			continue ;
		}
		else if (inside && str && str[0])
		{
			(*cmd)->args[i++] = ft_strdup(str);
			if (!(*cmd)->args[i - 1])
				return (_FAILURE);
		}
		else if (!inside && str && str[0])
		{
			data->_errno = 2;
			return (ft_dprintf(2, _ERR_TOKEN, str), _FAILURE);
		}
		tmp = tmp->next;
	}
	if (inside && (*cmd)->args)
		(*cmd)->args[i] = NULL;
	if (tmp && tmp->x == ')' && tmp->next && _pars_args_line(data, cmd,
			&tmp->next, false))
		return (_FAILURE);
	return (_SUCCESS);
}
