/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_bot_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:17:41 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 12:33:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_bot_push(t_dll *dll, void *value)
{
	t_node	*node;

	node = node_create();
	if (!node)
		return (NULL);

	if (!dll)
	{
		dll = dll_create();
		if (!dll)
			return (m_free(node), NULL);
		dll->top = node;
		dll->bot = node;
	}
	else
	{
		dll->bot->next = node;
		node->next = dll->top;
		node->prev = dll->bot;
		dll->bot = node;
		dll->top->prev = node;
	}
	(void)value;
	node->value = value;
	dll->size++;
	return (dll);
}
