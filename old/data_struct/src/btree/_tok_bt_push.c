/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_bt_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:16:04 by moha              #+#    #+#             */
/*   Updated: 2024/07/18 23:16:13 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pbt_tok	_tok_bt_push(t_pbt_tok tree, t_pbt_tok node, bool side)
{
	if (!tree)
		tree = node;
	else if (side)
	{
		if (!tree->left)
		{
			tree->left = node;
			node->root = tree;
		}
		else
			_tok_bt_push(tree->left, node, side);
	}
	else if (!side)
	{
		if (!tree->right)
		{
			tree->right = node;
			node->root = tree;
		}
		else
			_tok_bt_push(tree->right, node, side);
	}
	return (tree);
}
