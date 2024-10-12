/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/12 10:00:34 by mbekheir         ###   ########.fr       */
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

int	_pars_args_alloc(t_ppncmd cmd)
{
	int	i;

	if (!*cmd)
		return (_FAILURE);
	(*cmd)->args = NULL;
	i = _nb_lnargs((*cmd)->token);
	if (i && (_alloc((void **)&(*cmd)->args, sizeof(char *) * (i + 1))
			|| !(*cmd)->args))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_pars_args(t_ppncmd cmd, t_ppnlst token)
{
	t_pnlst	tmp;
	int		i;
	char	*str;

	if (!*cmd || _pars_args_alloc(cmd))
		return (_FAILURE);
	i = 0;
	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (_tok_id(tmp->x, _TYP_REDIRS))
		{
			tmp = tmp->next->next;
			continue ;
		}
		str = tmp->addr_1;
		if (str && str[0])
		{
			(*cmd)->args[i++] = ft_strdup(str);
			if (!(*cmd)->args[i - 1])
				return (_FAILURE);
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_pars_redirs(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	t_pnlst	tmp;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (_tok_id(tmp->x, _TYP_REDIRS))
		{
			if (_pars_redirs_proc(cmd, &tmp, inside))
			{
				data->_errno = 1;
				return (_FAILURE);
			}
			continue ;
		}
		if (!inside && tmp->addr_1)
		{
			data->_errno = 2;
			return (ft_dprintf(2, _ERR_TOKEN, tmp->addr_1), _FAILURE);
		}
		tmp = tmp->next;
	}
	if (tmp && tmp->x == ')' && tmp->next && _pars_redirs(data, cmd, &tmp->next,
			false))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_pars_args_line(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	if (!*cmd || _pars_args(cmd, token))
		return (_FAILURE);
	return (_pars_redirs(data, cmd, token, inside));
}
