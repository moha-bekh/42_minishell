/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:15:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 18:41:08 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pcmd	_set_null(t_pcmd node)
{
	if (!node)
		return (NULL);
	node->cmd_path = NULL;
	node->cmd_arg = NULL;
	node->redir.here_name = NULL;
	node->redir.here_limit = NULL;
	node->redir.in_name = NULL;
	node->redir.out_name = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

u_padll	_cmd_push_back(u_padll dll, t_ptok token, char **cmd_arg)
{
	t_pcmd	node;

	if (_alloc((void *)&node, sizeof(t_cmd)) || !node)
		return (NULL);
	node = _set_null(node);
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
	node->cmd_arg = cmd_arg;
	dll->c_size++;
	return (dll);
}
