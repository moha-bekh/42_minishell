/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_pop_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:14:23 by moha              #+#    #+#             */
/*   Updated: 2024/07/18 18:32:09 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

static void	_dll_last_node(t_pdll dll)
{
	free(dll->top->value);
	dll->top->value = NULL;
	free(dll->top);
	dll->top = NULL;
	free(dll);
	dll = NULL;
	return ;
}

static void	_dll_filled(t_pdll dll, t_pnode target)
{
	t_pnode	tmp;

	dll->size--;
	tmp = target;
	target = target->prev;
	target->next = tmp->next;
	tmp->next->prev = target;
	if (dll->size == 1)
	{
		dll->top->prev = NULL;
		dll->bot->next = NULL;
	}
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->value);
	tmp->value = NULL;
	free(tmp);
	tmp = NULL;
	return ;
}

t_pdll	_dll_pop_in(t_pdll dll, t_pnode target)
{
	if (!dll)
		return (ft_putstr_fd("dll is NULL\n", STDERR_FILENO), NULL);
	if ((dll->top && dll->bot) && dll->top == dll->bot)
		return (_dll_last_node(dll), NULL);
	_dll_filled(dll, target);
	return (dll);
}
