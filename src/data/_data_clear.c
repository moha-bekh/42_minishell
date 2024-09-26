/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:44:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 16:59:01 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_structs_clear(t_pdata data)
{
	data->args.nb_hd = 0;
	data->args.parnth = 0;
	data->prompt = NULL;
	_dlst_clear(&data->tokens);
	_dlst_clear(&data->xpd);
	_bt_clear(&data->tree);
	return (_SUCCESS);
}

int	_data_clear(t_pdata data)
{
	free(data->prompt);
	ft_free_arr(data->args.env_path);
	ft_free_arr(data->args.hard_path);
	_dlst_clear(&data->builtins);
	_dlst_clear(&data->env);
	_dlst_clear(&data->export);
	_dlst_clear(&data->tokens);
	_dlst_clear(&data->xpd);
	_bt_clear(&data->tree);
	close(data->shell._stdin);
	close(data->shell._stdout);
	return (_SUCCESS);
}
