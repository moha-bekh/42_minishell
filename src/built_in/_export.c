/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/08/06 07:13:38 by moha             ###   ########.fr       */
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
		if (tmp->value && tmp->value[1] != '"')
			printf("export %s=%s\n", tmp->key, tmp->value);
		else
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	return ;
}

int	_export(t_pdata data, char **arg)
{
	int	i;
	int	j;

	if (!arg[1])
	{
		data->_errno = 0;
		return (_export_print(data->env.dll_senv), _SUCCESS);
	}
	_clean_env(data, arg);
	i = 0;
	while (arg[++i])
	{
		j = _get_start_index(arg[i]);
		data->env.dll_env = _env_push_back(data->env.dll_env, ft_substr(arg[i],
					0, j), ft_substr(arg[i], j + 1, ft_strlen(arg[i])));
		if (!ft_strcmp(data->env.dll_env->e_bot->key, "PATH"))
		{
			ft_free_arr(data->paths[1]);
			data->paths[1] = ft_split(data->env.dll_env->e_bot->value, ':');
			_path_slash(data, 1);
		}
	}
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_set_senv(&data->env.dll_senv, data->env.dll_env);
	data->_errno = 0;
	return (_SUCCESS);
}
