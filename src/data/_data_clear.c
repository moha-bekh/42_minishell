/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 03:25:35 by oek              ###   ########.fr       */
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
	close(data->shell._stdin);
	close(data->shell._stdout);
}
