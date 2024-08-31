/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:22:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 22:11:00 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_strings(t_ppnlst token)
{
	t_pnlst	tmp;
	char	*old;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp->flag)
		{
			tmp = tmp->next;
			old = tmp->addr_1;
			tmp->addr_1 = ft_strjoin(tmp->prev->addr_1, tmp->addr_1);
			free(old);
			_dlst_pop_in(&(*token)->manager, &tmp->prev);
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_xpd_var(t_pdata data, t_ppnlst token)
{
	char	*tmp;

	tmp = _env_get_value(data, (*token)->addr_1);
	if (tmp)
	{
		free((*token)->addr_1);
		(*token)->addr_1 = ft_strdup(tmp);
		free(tmp);
	}
	else if (!tmp && !ft_strcmp((*token)->addr_1, "$?"))
	{
		free((*token)->addr_1);
		(*token)->addr_1 = ft_itoa(data->_errno);
	}
	return (_SUCCESS);
}

int	_xpd_line(t_pdata data, t_ppnlst token)
{
	t_pnlst	tmp;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp->x == '*' && _xpd_wildcards(&tmp))
			return (_FAILURE);
		else if (tmp->x == '$' && _xpd_var(data, &tmp))
			return (_FAILURE);
		if (tmp->x == '"' && _xpd_needed(tmp->addr_1))
			_xpd_str(data, &tmp);
		tmp = tmp->next;
	}
	_join_strings(token);
	return (_SUCCESS);
}
