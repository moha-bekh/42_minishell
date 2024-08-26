/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:44:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 19:44:01 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cmd_push_back(u_padllst *dllst, t_pnlst token)
{
	t_pcmd	node;

	node = NULL;
	if (_alloc((void *)&node, sizeof(t_cmd)) || !node)
		return ;
	*node = (t_cmd){0};
	node->redirs = (t_redir){0};
	if (!(*dllst))
	{
		if (_alloc((void *)dllst, sizeof(u_adllst)) || !*dllst)
			return (free(node));
		(**dllst) = (u_adllst){0};
		(*dllst)->c_top = node;
		(*dllst)->c_bot = node;
	}
	else
	{
		node->prev = (*dllst)->c_bot;
		(*dllst)->c_bot->next = node;
		(*dllst)->c_bot = node;
	}
	node->token = token;
	(*dllst)->c_size++;
}
