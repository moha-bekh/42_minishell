/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:22:59 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 16:02:55 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pbtree	_bt_create(t_pnlst token)
{
	t_pbtree	node;

	if (_alloc((void *)&node, sizeof(t_btree)))
		return (NULL);
	*node = (t_btree){0};
	node->token = token;
	return (node);
}
