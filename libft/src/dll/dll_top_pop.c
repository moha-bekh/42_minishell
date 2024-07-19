/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_top_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:19:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 13:58:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_top_pop(t_dll *dll)
{
	t_node	*tmp;

	if (dll_empty(dll))
		return (dll_new());
	if (dll->top == dll->bot)
	{
		dll->size--;
		return (free(dll->top), free(dll), dll_new());
	}
	tmp = dll->top;
	dll->top = dll->top->next;
	dll->top->prev = dll->bot;
	dll->bot->next = dll->top;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp);
	dll->size--;
	return (dll);
}
