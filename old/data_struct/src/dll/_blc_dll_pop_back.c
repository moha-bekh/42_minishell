/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_dll_pop_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:57:31 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 18:56:28 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll_blc	_blc_dll_pop_back(t_pdll_blc dll)
{
	t_pblc	tmp;

	if (!dll)
		return (ft_putstr_fd("blocs is NULL\n", STDERR_FILENO), NULL);
	if ((dll->top && dll->bot) && dll->top == dll->bot)
	{
		free(dll->top->value);
		dll->top->value = NULL;
		free(dll->top);
		dll->top = NULL;
		free(dll);
		dll = NULL;
		return (NULL);
	}
	dll->size--;
	tmp = dll->bot;
	dll->bot = dll->bot->prev;
	dll->bot->next = NULL;
	free(tmp->value);
	tmp->value = NULL;
	tmp->prev = NULL;
	free(tmp);
	tmp = NULL;
	return (dll);
}
