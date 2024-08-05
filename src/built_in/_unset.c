/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:55:55 by moha              #+#    #+#             */
/*   Updated: 2024/08/05 11:48:25 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_unset(t_pdata data, char **arg)
{
	t_pev	tmp;
	int		i;

	if (!data || !arg)
	{
		data->_errno = 0;
		return ;
	}
	tmp = data->env.dll_env->e_top;
	while (tmp)
	{
		i = 0;
		while (arg[i])
		{
			if (!ft_strcmp(tmp->key, arg[i]))
				data->env.dll_env = _env_pop_in(data->env.dll_env, tmp);
			i++;
		}
		tmp = tmp->next;
	}
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_set_senv(&data->env.dll_senv, data->env.dll_env);
	data->_errno = 0;
}
