/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_pop_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:43:00 by moha              #+#    #+#             */
/*   Updated: 2024/08/09 17:45:40 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_next(u_padll dll)
{
	if (dll->t_size > 1)
	{
		dll->t_top->prev = dll->t_bot;
		dll->t_bot->next = dll->t_top;
	}
	else
	{
		dll->t_bot->next = NULL;
		dll->t_top->prev = NULL;
	}
}

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

u_padll	_tok_pop_front(u_padll dll)
{
	t_ptok	tmp;

	if (!dll)
		return (NULL);
	if ((dll->t_top && dll->t_bot) && dll->t_top == dll->t_bot)
		return (_dll_last_node(dll), NULL);
	dll->t_size--;
	tmp = dll->t_top;
	dll->t_top = dll->t_top->next;
	set_next(dll);
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->value);
	tmp->value = NULL;
	free(tmp);
	tmp = NULL;
	return (dll);
}
