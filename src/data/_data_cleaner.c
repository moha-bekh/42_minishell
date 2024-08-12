/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 17:14:55 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_data_clear_builtin(char **builtin)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		free(builtin[i]);
		builtin[i] = NULL;
	}
	return ;
}

void _data_clear_lists(t_pdata data)
{
	data->tok = _tok_clear(data->tok);
	data->exp = _env_clear(data->exp);
	data->scp = _scp_clear(data->scp);
	data->tree = _op_bt_clear(data->tree);
}

void	_data_cleaner(t_pdata data)
{
	_data_clear_builtin(data->built_in);
	ft_free_arr(data->env.min_ev);
	ft_free_arr(data->paths[1]);
	ft_free_arr(data->paths[0]);
	free(data->input);
	data->env.dll_env = _env_clear(data->env.dll_env);
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_data_clear_lists(data);
	return ;
}
