/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_pop_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:14:12 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/08 09:47:32 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_dll_last_node(u_padll dll)
{
	free(dll->t_top->value);
	dll->t_top->value = NULL;
	free(dll->t_top);
	dll->t_top = NULL;
	free(dll);
	dll = NULL;
	return ;
}

static void	_dll_filled(u_padll dll, t_ptok target)
{
	t_ptok	tmp;

	tmp = target;
	target = target->prev;
	target->next = tmp->next;
	tmp->next->prev = target;
	if (dll->e_size == 1)
	{
		dll->t_top->prev = NULL;
		dll->t_bot->next = NULL;
	}
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->value);
	tmp->value = NULL;
	free(tmp);
	tmp = NULL;
	dll->e_size--;
	return ;
}

u_padll	_tok_pop_in(u_padll dll, t_ptok target)
{
	if (!dll)
		return (NULL);
	if ((dll->t_top && dll->t_bot) && dll->t_top == dll->t_bot)
		return (_dll_last_node(dll), NULL);
	_dll_filled(dll, target);
	return (dll);
}
