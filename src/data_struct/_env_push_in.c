/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_push_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:51 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:17:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_env_push_in(u_padll dll, t_pev target, char *key, char *value)
{
	t_pev	node;

	if (_alloc((void *)&node, sizeof(t_ev)) || !node)
		return (NULL);
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(u_adll)) || !dll)
			return (free(node), NULL);
		dll->e_top = node;
		dll->e_bot = node;
	}
	else
	{
		node->next = target;
		node->prev = target->prev;
		target->prev->next = node;
		target->prev = node;
	}
	node->key = key;
	node->value = value;
	dll->e_size++;
	return (dll);
}
