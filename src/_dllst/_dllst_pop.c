/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dllst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:54 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/23 13:06:10 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dllst_pop_front(u_padllst *dllst)
{
	t_pnlst	tmp;

	if (!*dllst)
		return ;
	tmp = (*dllst)->d_bot;
	if (--(*dllst)->d_size)
	{
		tmp = (*dllst)->d_top;
		(*dllst)->d_top = (*dllst)->d_top->next;
		(*dllst)->d_top->prev = NULL;
	}
	free(tmp->addr_1);
	free(tmp->addr_2);
	*tmp = (t_nlst){0};
	free(tmp);
	tmp = NULL;
	if (!(*dllst)->d_size)
	{
		(**dllst) = (u_adllst){0};
		free(*dllst);
		*dllst = NULL;
	}
}

void	_dllst_pop_back(u_padllst *dllst)
{
	t_pnlst	tmp;

	if (!*dllst)
		return ;
	tmp = (*dllst)->d_bot;
	if (--(*dllst)->d_size)
	{
		tmp = (*dllst)->d_bot;
		(*dllst)->d_bot = (*dllst)->d_bot->prev;
		(*dllst)->d_bot->next = NULL;
	}
	free(tmp->addr_1);
	free(tmp->addr_2);
	*tmp = (t_nlst){0};
	free(tmp);
	tmp = NULL;
	if (!(*dllst)->d_size)
	{
		(**dllst) = (u_adllst){0};
		free(*dllst);
		*dllst = NULL;
	}
}

void	_dllst_pop_in(u_padllst *dllst, t_pnlst *node)
{
	t_pnlst	tmp;

	if (!*dllst || !node)
		return ;
	if ((*dllst)->d_top && (*dllst)->d_top == *node)
		return (_dllst_pop_front(dllst));
	if ((*dllst)->d_bot && (*dllst)->d_bot == *node)
		return (_dllst_pop_back(dllst));
	if (--(*dllst)->d_size > 2)
	{
		tmp = *node;
		(*node)->prev->next = (*node)->next;
		(*node)->next->prev = (*node)->prev;
		free(tmp->addr_1);
		free(tmp->addr_2);
		*tmp = (t_nlst){0};
		free(tmp);
		tmp = NULL;
	}
}
