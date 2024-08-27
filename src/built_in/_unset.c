/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:55:55 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:51:31 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_update_export(t_pdata data)
{
	t_pnlst	tmp;

	tmp = NULL;
	_dlst_clear(&data->export);
	while (tmp)
	{
		_dlst_push_back(&data->export, ft_strdup(tmp->addr_1), ft_strdup(tmp->addr_2), 0);
		tmp = tmp->next;
	}
	_dlst_sort(&data->export, false);
}

int	_unset(t_pdata data, t_ppncmd cmd)
{
	t_pnlst	tmp;
	int		i;

	if (!(*cmd)->args)
		return (_SUCCESS);
	tmp = data->env->d_top;
	while (tmp)
	{
		i = -1;
		while ((*cmd)->args[++i])
		{
			if (!ft_strcmp((char *)tmp->addr_1, (*cmd)->args[i]))
			{
				_dlst_pop_in(&data->env, &tmp);
				break ;
			}
		}
		tmp = tmp->next;
	}
	_update_export(data);
	return (_SUCCESS);
}
