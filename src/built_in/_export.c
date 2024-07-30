/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 10:03:18 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_export_print(u_padll dll)
{
	t_pev	tmp;

	if (!dll)
		return ;
	tmp = dll->e_top;
	while (tmp)
	{
		printf("export %s=%s", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return ;
}

int	_export(t_pdata data, char **arg)
{
	int	i;
	int	j;

	if (!arg)
		return (_export_print(data->env.dll_senv), _SUCCESS);
	_clean_env(data, arg);
	i = -1;
	while (arg[++i])
	{
		j = _get_start_index(arg[i]);
		data->env.dll_env = _env_push_back(data->env.dll_env, ft_substr(arg[i],
					0, j), ft_substr(arg[i], j + 1, ft_strlen(arg[i])));
	}
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_set_senv(&data->env.dll_senv, data->env.dll_env);
	return (_SUCCESS);
}
