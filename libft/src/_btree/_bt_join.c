/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:49:23 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 16:03:00 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pbtree	_bt_join(t_pbtree left, t_pnlst token, t_pbtree right)
{
	t_pbtree	node;

	node = _bt_create(token);
	node->left = left;
	node->right = right;
	if (left)
		left->root = node;
	if (right)
		right->root = node;
	return (node);
}
