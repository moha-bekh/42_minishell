/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_push_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:32:17 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 20:34:00 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_push_at(t_pbt_op tree, t_pbt_op node, bool left)
{
	if (!tree)
		tree = node;
	else if (left)
	{
		if (!tree->left)
		{
			tree->left = node;
			node->root = tree;
		}
		else
			_op_bt_push_at(tree->left, node, left);
	}
	else if (!left)
	{
		if (!tree->right)
		{
			tree->right = node;
			node->root = tree;
		}
		else
			_op_bt_push_at(tree->right, node, left);
	}
	return (tree);
}
