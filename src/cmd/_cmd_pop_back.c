/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_pop_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:15:50 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 18:40:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_pop_cmd(u_padll dll)
{
	t_pcmd	tmp;

	tmp = dll->c_bot;
	dll->c_bot = dll->c_bot->prev;
	dll->c_bot->next = NULL;
	free(tmp->cmd_path);
	tmp->cmd_path = NULL;
	ft_free_arr(tmp->cmd_a);
	tmp->cmd_a = NULL;
	tmp->prev = NULL;
	free(tmp);
	tmp = NULL;
	return (dll);
}

u_padll	_cmd_pop_back(u_padll dll)
{
	if (!dll)
		return (NULL);
	if ((dll->c_top && dll->c_bot) && dll->c_top == dll->c_bot)
	{
		free(dll->c_top->cmd_path);
		dll->c_top->cmd_path = NULL;
		ft_free_arr(dll->c_top->cmd_a);
		dll->c_top->cmd_a = NULL;
		free(dll->c_top);
		dll->c_top = NULL;
		free(dll);
		dll = NULL;
		return (NULL);
	}
	dll->c_size--;
	dll = _pop_cmd(dll);
	return (dll);
}
