/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 18:28:32 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_data_clear_builtin(char **builtin)
{
	int	i;

	i = -1;
	while (++i < 7)
		free(builtin[i]);
	return ;
}

void	_data_cleaner(t_pdata data)
{
	_data_clear_builtin(data->built_in);
	ft_free_arr(data->env.min_ev);
	free(data->input);
	data->env.dll_env = _env_clear(data->env.dll_env);
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	return ;
}
