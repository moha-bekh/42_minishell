/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/23 13:08:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_clear(t_pdata data)
{
	free(data->prompt);
	ft_free_arr(data->args.env_path);
	ft_free_arr(data->args.hard_path);
	_dllst_clear(&data->builtins);
	_dllst_clear(&data->env);
	_dllst_clear(&data->export);
	_dllst_clear(&data->tokens);
	_bt_clear(&data->tree);
	return (_SUCCESS);
}

int	_data_structs_clear(t_pdata data)
{
	free(data->prompt);
	data->prompt = NULL;
	_dllst_clear(&data->tokens);
	_bt_clear(&data->tree);
	return (_SUCCESS);
}
