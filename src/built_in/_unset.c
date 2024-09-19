/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:55:55 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 05:03:28 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_update_export(t_pdata data)
{
	t_pnlst	tmp;

	_dlst_clear(&data->export);
	tmp = data->env->d_top;
	while (tmp)
	{
		if (tmp->addr_2)
			_dlst_push_back(&data->export, ft_strdup(tmp->addr_1),
				ft_strdup(tmp->addr_2), 0);
		else
			_dlst_push_back(&data->export, ft_strdup(tmp->addr_1), NULL, 0);
		tmp = tmp->next;
	}
	_dlst_sort(&data->export, false);
}

int	_unset(t_pdata data, char **args)
{
	t_pnlst	tmp;
	int		i;

	if (!*args)
		return (_SUCCESS);
	tmp = data->env->d_top;
	while (tmp)
	{
		i = -1;
		while (args[++i])
		{
			if (!ft_strcmp(tmp->addr_1, args[i]))
			{
				_dlst_pop_in(&data->env, &tmp);
				tmp = data->env->d_top;
				break ;
			}
		}
		tmp = tmp->next;
	}
	ft_free_arr(data->args.hard_path);
	ft_free_arr(data->args.env_path);
	_update_export(data);
	return (_SUCCESS);
}
