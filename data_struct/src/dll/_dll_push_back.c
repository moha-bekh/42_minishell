/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:22:42 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 21:33:17 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll _dll_push_back(t_pdll dll, char *value)
{
	t_pnode node;

	if (_alloc((void *)&node, sizeof(t_node)) || !node)
		return (ft_putstr_fd(ALLOC_FAIL, STDERR_FILENO), NULL);
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(t_dll)) || !dll)
			return (ft_putstr_fd(ALLOC_FAIL, STDERR_FILENO), NULL);
		dll->top = node;
		dll->bot = node;
	}
	else
	{
		dll->bot->next = node;
		dll->top->prev = node;
		node->prev = dll->bot;
		node->next = dll->top;
		dll->bot = node;
	}
	node->value = value;
	dll->size++;
	return (dll);
}
