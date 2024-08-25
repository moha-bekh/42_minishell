/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:55:55 by moha              #+#    #+#             */
/*   Updated: 2024/08/23 19:27:48 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_update_export(t_pdata data)
{
	t_pnlst	tmp;

	tmp = NULL;
	_dllst_clear(&data->export);
	while (tmp)
	{
		_dllst_push_back(&data->export, ft_strdup(tmp->addr_1),
			ft_strdup(tmp->addr_2), 0);
		tmp = tmp->next;
	}
	_dllst_sort(&data->export, false);
}

int	_unset(t_pdata data, t_pcmd *cmd)
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
				_dllst_pop_in(&data->env, &tmp);
				break ;
			}
		}
		tmp = tmp->next;
	}
	_update_export(data);
	return (_SUCCESS);
}
