/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_push_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:06:42 by moha              #+#    #+#             */
/*   Updated: 2024/07/19 19:14:59 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll	_dll_push_in(t_pdll dll, t_pnode target, char *value)
{
	t_pnode	node;

	if (_alloc((void *)&node, sizeof(t_node)) || !node)
		return (ft_putstr_fd(ALLOC_FAIL, STDERR_FILENO), NULL);
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(t_dll)) || !dll)
			return (ft_putstr_fd(ALLOC_FAIL, STDERR_FILENO), free(node), NULL);
		dll->top = node;
		dll->bot = node;
	}
	else
	{
		node->next = target;
		node->prev = target->prev;
		target->prev->next = node;
		target->prev = node;
	}
	node->value = value;
	dll->size++;
	return (dll);
}
