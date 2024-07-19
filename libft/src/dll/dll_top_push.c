/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_top_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:18:27 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 11:34:50 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_top_push(t_dll *dll, void *value)
{
	t_node	*node;

	node = NULL;
	node = node_create();
	if (!node)
		return (NULL);
	if (!dll)
	{
		dll = NULL;
		dll = dll_create();
		if (!dll)
			return (m_free(node), NULL);
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
	printf("ptr dll %p\n", dll);
	printf("ptr dll->top: %p\n", dll->top);
	return (dll);
}
