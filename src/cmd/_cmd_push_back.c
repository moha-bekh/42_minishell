/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:15:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 11:29:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_cmd_push_back(u_padll dll, t_ptok token, char **cmd_a)
{
	t_pcmd	node;

	if (_alloc((void *)&node, sizeof(t_cmd)) || !node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->cmd_path = NULL;
	node->cmd_a = NULL;
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(u_adll)) || !dll)
			return (free(node), NULL);
		dll->c_top = node;
		dll->c_bot = node;
	}
	else
	{
		node->prev = dll->c_bot;
		dll->c_bot->next = node;
		dll->c_bot = node;
	}
	node->token = token;
	node->cmd_a = cmd_a;
	dll->c_size++;
	return (dll);
}
