/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_push_root.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:51:02 by moha              #+#    #+#             */
/*   Updated: 2024/07/20 18:01:56 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_push_root(t_pbt_op tree, t_pbt_op node)
{
	if (!tree)
		tree = node;
	else
	{
		node->left = tree;
		tree->root = node;
		tree = node;
	}
	return (tree);
}
