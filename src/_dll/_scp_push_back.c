/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scp_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:54:31 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:15:15 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_scp_push_back(u_padll dll, struct s_bt_op *ptr_op)
{
	t_pscop	node;

	if (_alloc((void *)&node, sizeof(t_scop)) || !node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->ptr_op = ptr_op;
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(u_adll)) || !dll)
			return (free(node), NULL);
		dll->s_top = node;
		dll->s_bot = node;
	}
	else
	{
		node->prev = dll->s_bot;
		dll->s_bot->next = node;
		dll->s_bot = node;
	}
	dll->s_size++;
	return (dll);
}
