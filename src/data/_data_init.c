/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:44:34 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 10:11:33 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_init_args(t_pdata data, int ac, char **av, char **ev)
{
	if (!data)
		return (_EMPTY);
	ft_memset(data, 0, sizeof(t_data));
	data->ac = ac;
	data->av = av;
	data->input = NULL;
	data->tmp = NULL;
	data->env.env = ev;
	data->env.min_ev = NULL;
	data->env.dll_env = NULL;
	data->env.dll_senv = NULL;
	data->tok = NULL;
	data->exp = NULL;
	data->scop = NULL;
	data->tree = NULL;
	return (_SUCCESS);
}

int	_data_init_builtin(t_pdata data)
{
	if (!data)
		return (_EMPTY);
	data->built_in[0] = ft_strdup("cd");
	data->built_in[1] = ft_strdup("echo");
	data->built_in[2] = ft_strdup("env");
	data->built_in[3] = ft_strdup("exit");
	data->built_in[4] = ft_strdup("export");
	data->built_in[5] = ft_strdup("pwd");
	data->built_in[6] = ft_strdup("unset");
	return (_SUCCESS);
}

int	_data_min_env(t_pdata data)
{
	if (_alloc((void *)&data->env.min_ev, sizeof(char *) * 3)
		|| !data->env.min_ev)
		return (_ALLOC);
	data->env.min_ev[0] = getcwd(NULL, 0);
	data->env.min_ev[1] = ft_strdup("PATH=" _PATH);
	data->env.min_ev[2] = NULL;
	return (_SUCCESS);
}

int	_data_init(t_pdata data, int ac, char **av, char **ev)
{
	if (!data || _data_init_args(data, ac, av, ev))
		return (_FAILURE);
	if (_data_init_builtin(data))
		return (_FAILURE);
	if (_data_min_env(data))
		return (_FAILURE);
	if (_set_env(&data->env.dll_env, ev))
		return (_FAILURE);
	if (_set_senv(&data->env.dll_senv, data->env.dll_env))
		return (_FAILURE);
	return (_SUCCESS);
}
