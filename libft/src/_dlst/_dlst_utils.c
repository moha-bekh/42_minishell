/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 00:47:53 by oek               #+#    #+#             */
/*   Updated: 2024/10/18 13:32:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pnlst	_dlst_new_node(void)
{
	t_pnlst	node;

	if (_alloc((void *)&node, sizeof(t_nlst)) || !node)
		return (NULL);
	*node = (t_nlst){0};
	return (node);
}

t_padlst	_dlst_new_manager(void)
{
	t_padlst	dlst;

	if (_alloc((void *)&dlst, sizeof(t_adlst)) || !dlst)
		return (NULL);
	*dlst = (t_adlst){0};
	return (dlst);
}

void	_dlst_merge_nodes(t_padlst dlst, t_pnlst prev, t_pnlst node,
		t_pnlst next)
{
	if (prev)
		prev->next = node;
	else
		dlst->d_top = node;
	node->prev = prev;
	node->next = next;
	if (next)
		next->prev = node;
	else
		dlst->d_bot = node;
}
