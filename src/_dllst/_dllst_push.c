/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dllst_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:43 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 01:26:10 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dllst_push_front(u_padllst *dllst, void *addr_1, void *addr_2, int x)
{
	t_pnlst	node;

	if (_alloc((void *)&node, sizeof(t_nlst)) || !node)
		return ;
	*node = (t_nlst){0};
	if (!*dllst)
	{
		if (_alloc((void *)dllst, sizeof(u_adllst)) || !dllst)
			return (free(node));
		(**dllst) = (u_adllst){0};
		(*dllst)->d_top = node;
		(*dllst)->d_bot = node;
	}
	else
	{
		node->next = (*dllst)->d_top;
		(*dllst)->d_top->prev = node;
		(*dllst)->d_top = node;
	}
	node->addr_1 = addr_1;
	node->addr_2 = addr_2;
	node->x = x;
	node->manager = *dllst;
	(*dllst)->d_size++;
}

void	_dllst_push_back(u_padllst *dllst, void *addr_1, void *addr_2, int x)
{
	t_pnlst	node;

	if (_alloc((void *)&node, sizeof(t_nlst)) || !node)
		return ;
	*node = (t_nlst){0};
	if (!*dllst)
	{
		if (_alloc((void *)dllst, sizeof(u_adllst)) || !dllst)
			return (free(node));
		(**dllst) = (u_adllst){0};
		(*dllst)->d_top = node;
		(*dllst)->d_bot = node;
	}
	else
	{
		node->prev = (*dllst)->d_bot;
		(*dllst)->d_bot->next = node;
		(*dllst)->d_bot = node;
	}
	node->addr_1 = addr_1;
	node->addr_2 = addr_2;
	node->x = x;
	node->manager = *dllst;
	(*dllst)->d_size++;
}

void	_dllst_push_in(u_padllst *dllst, t_pnlst node, void *addr_1, void *addr_2)
{
	t_pnlst	new;

	if (!*dllst || !node)
		return ;
	if (_alloc((void *)&new, sizeof(t_nlst)) || !new)
		return ;
	*new = (t_nlst){0};
	new->addr_1 = addr_1;
	new->addr_2 = addr_2;
	if ((*dllst)->d_bot == node)
		return (_dllst_push_back(dllst, addr_1, addr_2, 0));
	if (node->prev)
	{
		new->prev = node->prev;
		new->prev->next = new;
	}
	else
		(*dllst)->d_top = new;
	new->next = node;
	node->prev = new;
	new->manager = *dllst;
	(*dllst)->d_size++;
}
