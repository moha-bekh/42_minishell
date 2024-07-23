/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:44 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:16:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_env_push_back(u_padll dll, char *key, char *value)
{
	t_pev	node;

	if (_alloc((void *)&node, sizeof(t_ev)) || !node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(u_adll)) || !dll)
			return (free(node), NULL);
		dll->e_top = node;
		dll->e_bot = node;
	}
	else
	{
		node->prev = dll->e_bot;
		dll->e_bot->next = node;
		dll->e_bot = node;
	}
	node->key = key;
	node->value = value;
	dll->e_size++;
	return (dll);
}
