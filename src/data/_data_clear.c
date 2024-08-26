/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 12:16:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_structs_clear(t_pdata data)
{
	data->_errno = 0;
	free(data->prompt);
	data->prompt = NULL;
	_dllst_clear(&data->tokens);
	_bt_clear(&data->tree);
	return (_SUCCESS);
}

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
	close(data->args._stdin);
	close(data->args._stdout);
	return (_SUCCESS);
}
