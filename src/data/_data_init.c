/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:44:34 by moha              #+#    #+#             */
/*   Updated: 2024/07/20 20:30:31 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_init_args(t_pdata data, int ac, char **av, char **ev)
{
	if (!data)
		return (EXIT_FAILURE);
	ft_memset(&data->env, 0, sizeof(t_env));
	ft_memset(&data->tree, 0, sizeof(t_bt_op));
	data->ac = ac;
	data->av = av;
	data->env.ev = ev;
	data->input = NULL;
	data->tok = NULL;
	data->scop = NULL;
	data->tree = NULL;
	return (EXIT_SUCCESS);
}

int	_data_init(t_pdata data, int ac, char **av, char **ev)
{
	if (!data || _data_init_args(data, ac, av, ev))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
