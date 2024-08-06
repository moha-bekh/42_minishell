/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_pop_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:23:08 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 19:23:35 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

static void	set_next(t_dll *dll)
{
	if (dll->size > 1)
	{
		dll->top->prev = dll->bot;
		dll->bot->next = dll->top;
	}
	else
	{
		dll->bot->next = NULL;
		dll->top->prev = NULL;
	}
}

t_pdll _dll_pop_front(t_pdll dll)
{
	t_pnode tmp;

	if (!dll)
		return (ft_putstr_fd("dll is NULL\n", STDERR_FILENO), NULL);
	if ((dll->top && dll->bot) && dll->top == dll->bot)
	{
		free(dll->top);
		dll->top = NULL;
		free(dll);
		dll = NULL;
		return (NULL);
	}
	dll->size--;
	tmp = dll->top;
	dll->top = dll->top->next;
	set_next(dll);
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp);
	tmp = NULL;
	return (dll);
}
