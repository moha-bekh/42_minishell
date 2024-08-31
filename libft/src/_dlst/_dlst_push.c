/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:43 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 16:02:47 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_dlst_push_front(t_ppadlst dlst, void *addr_1, void *addr_2, int x)
{
	t_pnlst	node;

	if (_alloc((void *)&node, sizeof(t_nlst)) || !node)
		return ;
	*node = (t_nlst){0};
	if (!*dlst)
	{
		if (_alloc((void *)dlst, sizeof(t_adlst)) || !dlst)
			return (free(node));
		(**dlst) = (t_adlst){0};
		(*dlst)->d_top = node;
		(*dlst)->d_bot = node;
	}
	else
	{
		node->next = (*dlst)->d_top;
		(*dlst)->d_top->prev = node;
		(*dlst)->d_top = node;
	}
	node->addr_1 = addr_1;
	node->addr_2 = addr_2;
	node->x = x;
	node->manager = *dlst;
	(*dlst)->d_size++;
}

void	_dlst_push_back(t_ppadlst dlst, void *addr_1, void *addr_2, int x)
{
	t_pnlst	node;

	if (_alloc((void *)&node, sizeof(t_nlst)) || !node)
		return ;
	*node = (t_nlst){0};
	if (!*dlst)
	{
		if (_alloc((void *)dlst, sizeof(t_adlst)) || !dlst)
			return (free(node));
		(**dlst) = (t_adlst){0};
		(*dlst)->d_top = node;
		(*dlst)->d_bot = node;
	}
	else
	{
		node->prev = (*dlst)->d_bot;
		(*dlst)->d_bot->next = node;
		(*dlst)->d_bot = node;
	}
	node->addr_1 = addr_1;
	node->addr_2 = addr_2;
	node->x = x;
	node->manager = *dlst;
	(*dlst)->d_size++;
}

void	_dlst_push_in(t_ppadlst dlst, t_pnlst node, void *addr_1, void *addr_2)
{
	t_pnlst	new;

	if (!*dlst || !node)
		return ;
	if (_alloc((void *)&new, sizeof(t_nlst)) || !new)
		return ;
	*new = (t_nlst){0};
	new->addr_1 = addr_1;
	new->addr_2 = addr_2;
	if ((*dlst)->d_bot == node)
		return (_dlst_push_back(dlst, addr_1, addr_2, 0));
	if (node->prev)
	{
		new->prev = node->prev;
		new->prev->next = new;
	}
	else
		(*dlst)->d_top = new;
	new->next = node;
	node->prev = new;
	new->manager = *dlst;
	(*dlst)->d_size++;
}
