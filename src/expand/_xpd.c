/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:22:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/20 20:35:01 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_var(t_pdata data, t_ppnlst token)
{
	char	*tmp;

	if (!ft_strcmp((*token)->addr_1, "$?"))
	{
		free((*token)->addr_1);
		(*token)->addr_1 = ft_itoa(data->_errno);
		if (!(*token)->addr_1)
			return (_FAILURE);
		return (_SUCCESS);
	}
	tmp = _get_env_value(data, (*token)->addr_1);
	if (tmp)
	{
		free((*token)->addr_1);
		(*token)->addr_1 = ft_strdup(tmp);
		if (!(*token)->addr_1)
			return (_FAILURE);
	}
	else
	{
		(*token)->addr_2 = ft_strjoin("$", (*token)->addr_1);
		free((*token)->addr_1);
		(*token)->addr_1 = NULL;
	}
	return (_SUCCESS);
}

int	_xpd_line(t_pdata data, t_ppnlst token)
{
	t_pnlst	tmp;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp->x == '$' && _xpd_var(data, &tmp))
			return (_FAILURE);
		if (tmp->x == '"' && _xpd_needed(tmp->addr_1))
			tmp->addr_1 = _xpd_str(data, tmp->addr_1, true);
		// tmp->x = '*';
		tmp = tmp->next;
	}
	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if ((tmp->x == '*' /* || tmp->x == '"' || tmp->x == '$' */) && _xpd_wildcards(data, &tmp, true))
			return (_FAILURE);
		tmp = tmp->next;
	}
	_join_strings(token);
	return (_SUCCESS);
}
