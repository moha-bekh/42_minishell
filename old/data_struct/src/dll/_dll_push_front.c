/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_push_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:37:08 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 10:06:02 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll	_dll_push_front(t_pdll dll, char *value)
{
	t_pnode	node;

	if (_alloc((void *)&node, sizeof(t_node)) || !node)
		return (ft_putstr_fd("dll: " EXIT_ERROR, STDERR_FILENO), NULL);
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(t_dll)) || !dll)
			return (ft_putstr_fd("dll: " EXIT_ERROR, STDERR_FILENO), NULL);
		dll->top = node;
		dll->bot = node;
	}
	else
	{
		dll->top->prev = node;
		dll->bot->next = node;
		node->next = dll->top;
		node->prev = dll->bot;
		dll->top = node;
	}
	node->value = value;
	dll->size++;
	return (dll);
}
