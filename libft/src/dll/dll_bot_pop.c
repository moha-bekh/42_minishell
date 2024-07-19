/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_bot_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:19:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 14:04:12 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_bot_pop(t_dll *dll)
{
	t_node	*tmp;

	if (!dll)
	{
		ft_putstr_fd("dll_bot_pop: dll is NULL\n", STDERR_FILENO);
		return (NULL);
	}
	if (dll->top && dll->bot && dll->top == dll->bot)
	{
		dll->size--;
		free(dll->top);
		free(dll);
		return (NULL);
	}
	tmp = dll->bot;
	dll->bot = dll->bot->prev;
	dll->bot->next = dll->top;
	dll->top->prev = dll->bot;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp);
	dll->size--;
	return (dll);
}
