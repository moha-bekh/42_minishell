/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:44:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/21 17:06:55 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_cmd_push_back(t_ppadlst dlst, t_pnlst token)
{
	t_pncmd	node;

	node = NULL;
	if (_alloc((void *)&node, sizeof(t_ncmd)) || !node)
		return ;
	*node = (t_ncmd){0};
	node->redirs = (struct s_redir){0};
	if (!(*dlst))
	{
		if (_alloc((void *)dlst, sizeof(t_adlst)) || !*dlst)
			return (free(node));
		(**dlst) = (t_adlst){0};
		(*dlst)->c_top = node;
		(*dlst)->c_bot = node;
	}
	else
	{
		node->prev = (*dlst)->c_bot;
		(*dlst)->c_bot->next = node;
		(*dlst)->c_bot = node;
	}
	node->token = token;
	(*dlst)->c_size++;
}
