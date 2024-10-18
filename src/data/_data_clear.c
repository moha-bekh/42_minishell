/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/18 13:16:50 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_data_structs_clear(t_pdata data)
{
	data->args.nb_hd = 0;
	data->args.parnth = 0;
	data->prompt = NULL;
	_dlst_clear(&data->tokens);
	_dlst_clear(&data->xpd);
	_bt_clear(&data->tree);
	if (data->shell._stdin > 0)
	{
		close(data->shell._stdin);
		data->shell._stdin = -1;
	}
	if (data->shell._stdout > 0)
	{
		close(data->shell._stdout);
		data->shell._stdout = -1;
	}
}

void	_data_clear(t_pdata data)
{
	free(data->prompt);
	data->prompt = NULL;
	ft_free_arr(data->args.env_path);
	data->args.env_path = NULL;
	ft_free_arr(data->args.hard_paths);
	data->args.hard_paths = NULL;
	_dlst_clear(&data->builtins);
	_dlst_clear(&data->env);
	_dlst_clear(&data->export);
	_dlst_clear(&data->tokens);
	_dlst_clear(&data->xpd);
	_bt_clear(&data->tree);
	if (data->shell._stdin > 0)
	{
		close(data->shell._stdin);
		data->shell._stdin = -1;
	}
	if (data->shell._stdout > 0)
	{
		close(data->shell._stdout);
		data->shell._stdout = -1;
	}
}

int	_data_clear_exit(t_pdata data, int exit_code)
{
	int	_err;

	_err = data->_errno;
	_data_clear(data);
	if (exit_code == -1)
	{
		exit(_err);
		return (_err);
	}
	exit(exit_code);
	return (exit_code);
}
