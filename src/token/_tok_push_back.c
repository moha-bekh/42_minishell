/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:28:37 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:56:16 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_tok_push_back(u_padll dll, char type, char *value)
{
	t_ptok	node;

	if (_alloc((void *)&node, sizeof(t_tok)) || !node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->value = value;
	node->type = type;
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(u_adll)) || !dll)
			return (free(node), NULL);
		dll->t_top = node;
		dll->t_bot = node;
	}
	else
	{
		node->prev = dll->t_bot;
		dll->t_bot->next = node;
		dll->t_bot = node;
	}
	dll->t_size++;
	return (dll);
}
