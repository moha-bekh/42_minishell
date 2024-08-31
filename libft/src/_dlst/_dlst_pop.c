/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:54 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 16:23:05 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_dlst_pop_front(t_ppadlst dlst)
{
	t_pnlst	tmp;

	if (!*dlst)
		return ;
	tmp = (*dlst)->d_bot;
	if (--(*dlst)->d_size)
	{
		tmp = (*dlst)->d_top;
		(*dlst)->d_top = (*dlst)->d_top->next;
		(*dlst)->d_top->prev = NULL;
	}
	free(tmp->addr_1);
	free(tmp->addr_2);
	*tmp = (t_nlst){0};
	free(tmp);
	tmp = NULL;
	if (!(*dlst)->d_size)
	{
		(**dlst) = (t_adlst){0};
		free(*dlst);
		*dlst = NULL;
	}
}

void	_dlst_pop_back(t_ppadlst dlst)
{
	t_pnlst	tmp;

	if (!*dlst)
		return ;
	tmp = (*dlst)->d_bot;
	if (--(*dlst)->d_size)
	{
		tmp = (*dlst)->d_bot;
		(*dlst)->d_bot = (*dlst)->d_bot->prev;
		(*dlst)->d_bot->next = NULL;
	}
	free(tmp->addr_1);
	free(tmp->addr_2);
	*tmp = (t_nlst){0};
	free(tmp);
	tmp = NULL;
	if (!(*dlst)->d_size)
	{
		(**dlst) = (t_adlst){0};
		free(*dlst);
		*dlst = NULL;
	}
}

void	_dlst_pop_in(t_ppadlst dlst, t_ppnlst node)
{
	t_pnlst	tmp;

	if (!*dlst || !node)
		return ;
	if ((*dlst)->d_top && (*dlst)->d_top == *node)
		return (_dlst_pop_front(dlst));
	if ((*dlst)->d_bot && (*dlst)->d_bot == *node)
		return (_dlst_pop_back(dlst));
	(*dlst)->d_size--;
	tmp = *node;
	*node = (*node)->prev;
	(*node)->next = tmp->next;
	tmp->next->prev = *node;
	free(tmp->addr_1);
	free(tmp->addr_2);
	*tmp = (t_nlst){0};
	free(tmp);
	tmp = NULL;
}

void	_dlst_clear(t_ppadlst dlst)
{
	while (*dlst)
		_dlst_pop_back(dlst);
}
