/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_pop_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:01:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 17:04:54 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_dll_last_node(u_padll dll)
{
	free(dll->c_top->cmd_path);
	dll->c_top->cmd_path = NULL;
	ft_free_arr(dll->c_top->cmd_arg);
	dll->c_top->cmd_arg = NULL;
	free(dll->c_top);
	dll->c_top = NULL;
	free(dll);
	dll = NULL;
	return ;
}

static void	_dll_filled(u_padll dll, t_pcmd target)
{
	t_pcmd	tmp;

	tmp = target;
	target = target->prev;
	target->next = tmp->next;
	tmp->next->prev = target;
	if (dll->e_size == 1)
	{
		dll->e_top->prev = NULL;
		dll->e_bot->next = NULL;
	}
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->cmd_path);
	tmp->cmd_path = NULL;
	ft_free_arr(tmp->cmd_arg);
	tmp->cmd_arg = NULL;
	free(tmp);
	tmp = NULL;
	dll->e_size--;
	return ;
}

u_padll	_cmd_pop_in(u_padll dll, t_pcmd target)
{
	if (!dll)
		return (NULL);
	if ((dll->e_top && dll->e_bot) && dll->e_top == dll->e_bot)
		return (_dll_last_node(dll), NULL);
	_dll_filled(dll, target);
	return (dll);
}
