/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_push_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:51:16 by moha              #+#    #+#             */
/*   Updated: 2024/07/20 18:02:18 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_push_right(t_pbt_op tree, t_pbt_op node)
{
	if (!tree)
		tree = node;
	else
	{
		tree->right = node;
		node->root = tree;
	}
	return (tree);
}
