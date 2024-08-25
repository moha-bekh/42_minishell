/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_pop_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:50 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:56:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_dll_last_node(u_padll dll)
{
	free(dll->e_top->key);
	dll->e_top->key = NULL;
	free(dll->e_top->value);
	dll->e_top->value = NULL;
	free(dll->e_top);
	dll->e_top = NULL;
	free(dll);
	dll = NULL;
	return ;
}

static void	_dll_filled(u_padll dll, t_pev target)
{
	t_pev	tmp;

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
	free(tmp->key);
	tmp->key = NULL;
	free(tmp->value);
	tmp->value = NULL;
	free(tmp);
	tmp = NULL;
	dll->e_size--;
	return ;
}

u_padll	_env_pop_in(u_padll dll, t_pev target)
{
	if (!dll)
		return (NULL);
	if ((dll->e_top && dll->e_bot) && dll->e_top == dll->e_bot)
		return (_dll_last_node(dll), NULL);
	_dll_filled(dll, target);
	return (dll);
}
