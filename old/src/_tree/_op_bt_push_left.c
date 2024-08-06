/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_push_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:51:12 by moha              #+#    #+#             */
/*   Updated: 2024/07/20 18:02:41 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_push_left(t_pbt_op tree, t_pbt_op node)
{
	if (!tree)
		tree = node;
	{
		tree->left = node;
		node->root = tree;
	}
	return (tree);
}
