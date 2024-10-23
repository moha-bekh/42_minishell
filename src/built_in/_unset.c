/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alblanc <alblanc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:58:24 by alblanc           #+#    #+#             */
/*   Updated: 2024/10/23 16:03:22 by alblanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_update_export(t_pdata data)
{
	t_pnlst	tmp;

	_dlst_clear(&data->export);
	tmp = data->env->d_top;
	while (tmp)
	{
		if (tmp->addr_2)
		{
			_dlst_push_back(&data->export, ft_strdup(tmp->addr_1),
				ft_strdup(tmp->addr_2), 0);
			if (!data->export->d_bot->addr_1 || !data->export->d_bot->addr_2)
				return (_FAILURE);
		}
		else
		{
			_dlst_push_back(&data->export, ft_strdup(tmp->addr_1), NULL, 0);
			if (!data->export->d_bot->addr_1)
				return (_FAILURE);
		}
		tmp = tmp->next;
	}
	return (_dlst_sort(&data->export, false), _SUCCESS);
}

void	_unset_paths(t_pdata data)
{
	free(data->args._hard_path);
	data->args._hard_path = NULL;
	ft_free_arr(data->args.hard_paths);
	data->args.hard_paths = NULL;
	ft_free_arr(data->args.env_path);
	data->args.env_path = NULL;
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
			if (!ft_strcmp(args[i], "PATH"))
				_unset_paths(data);
			if (!ft_strcmp(tmp->addr_1, args[i]))
			{
				_dlst_pop_in(&data->env, &tmp);
				tmp = data->env->d_top;
				break ;
			}
		}
		tmp = tmp->next;
	}
	if (_update_export(data))
		return (_FAILURE);
	return (_SUCCESS);
}
