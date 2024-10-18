/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:43 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/18 13:32:19 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_dlst_push_front(t_ppadlst dlst, void *addr_1, void *addr_2, int x)
{
	t_pnlst	node;

	node = _dlst_new_node();
	if (!node)
		return ;
	if (!*dlst)
	{
		*dlst = _dlst_new_manager();
		if (!*dlst)
			return (free(node));
		(*dlst)->d_top = node;
		(*dlst)->d_bot = node;
	}
	else
	{
		node->next = (*dlst)->d_top;
		(*dlst)->d_top->prev = node;
		(*dlst)->d_top = node;
	}
	node->manager = *dlst;
	node->addr_1 = addr_1;
	node->addr_2 = addr_2;
	node->x = x;
	(*dlst)->d_size++;
}

void	_dlst_push_back(t_ppadlst dlst, void *addr_1, void *addr_2, int x)
{
	t_pnlst	node;

	node = _dlst_new_node();
	if (!node)
		return ;
	if (!*dlst)
	{
		*dlst = _dlst_new_manager();
		if (!*dlst)
			return (free(node));
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

void	_dlst_push_before(t_ppadlst dlst, t_pnlst node, void *addr_1,
		void *addr_2)
{
	t_pnlst	new;

	new = _dlst_new_node();
	if (!new)
		return ;
	if (!*dlst)
	{
		*dlst = _dlst_new_manager();
		if (!*dlst)
			return (free(new));
		(*dlst)->d_top = new;
		(*dlst)->d_bot = new;
	}
	_dlst_merge_nodes(*dlst, node->prev, new, node);
	new->addr_1 = addr_1;
	new->addr_2 = addr_2;
	new->manager = *dlst;
	(*dlst)->d_size++;
}

void	_dlst_push_after(t_ppadlst dlst, t_pnlst node, void *addr_1,
		void *addr_2)
{
	t_pnlst	new;

	new = _dlst_new_node();
	if (!new)
		return ;
	if (!*dlst)
	{
		*dlst = _dlst_new_manager();
		if (!*dlst)
			return (free(new));
		(*dlst)->d_top = new;
		(*dlst)->d_bot = new;
	}
	_dlst_merge_nodes(*dlst, node, new, node->next);
	new->addr_1 = addr_1;
	new->addr_2 = addr_2;
	new->manager = *dlst;
	(*dlst)->d_size++;
}

// else if ((*dlst)->d_bot == node)
// {
//     (*dlst)->d_bot->next = new;
//     new->prev = (*dlst)->d_bot;
//     (*dlst)->d_bot = new;
// }
// else
// {
//     node->next->prev = new;
//     new->next = node->next;
//     new->prev = node;
//     node->next = new;
// }

// void	_dlst_push_in(t_ppadlst dlst, t_pnlst node, void *addr_1, void *addr_2)
// {
// 	t_pnlst	new;

// 	if (!dlst || !*dlst || !node)
// 		return ;
// 	if (_alloc((void *)&new, sizeof(t_nlst)) || !new)
// 		return ;
// 	*new = (t_nlst){0};
// 	new->addr_1 = addr_1;
// 	new->addr_2 = addr_2;
// 	if ((*dlst)->d_top == node || (*dlst)->d_bot == node)
// 		return (_dlst_push_back(dlst, addr_1, addr_2, 0));
// 	new->manager = *dlst;
// 	node->next->prev = new;
// 	new->next = node->next;
// 	new->prev = node;
// 	node->next = new;
// 	(*dlst)->d_size++;
// }
