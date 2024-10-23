/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _join_limiters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:05:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/23 11:10:33 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_proc(t_ppnlst tmp)
{
	char	*old;

	*tmp = (*tmp)->next;
	if (!(*tmp))
		return (1);
	if ((*tmp)->prev->x == '"' || (*tmp)->prev->x == '\'')
		(*tmp)->x = '\'';
	if ((*tmp)->x == '$')
	{
		old = (*tmp)->addr_1;
		(*tmp)->addr_1 = ft_strjoin("$", (*tmp)->addr_1);
		free(old);
	}
	old = (*tmp)->addr_1;
	(*tmp)->addr_1 = ft_strjoin((*tmp)->prev->addr_1, (*tmp)->addr_1);
	free(old);
	if ((*tmp)->prev)
		_dlst_pop_in(&(*tmp)->manager, &(*tmp)->prev);
	else
	{
		free((*tmp)->prev->addr_1);
		(*tmp)->prev->addr_1 = NULL;
	}
	return (0);
}

int	_join_limiters(t_pdata data)
{
	t_pnlst	tmp;

	tmp = data->tokens->d_top;
	while (tmp)
	{
		if (tmp && tmp->x == 'H')
		{
			tmp = tmp->next;
			while (tmp && tmp->flag)
			{
				if (_join_proc(&tmp))
					break ;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (_SUCCESS);
}
