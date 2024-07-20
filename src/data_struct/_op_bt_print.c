/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/20 19:01:05 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_op_bt_print(t_pbt_op tree, bool prefix)
{
	if (!tree)
		return ;
	if (tree->root)
	{
		printf("root: ( %c ) -> tree: ( %c ) value: %s\n", tree->root->type, tree->type, tree->value);
	}
	else
	{	
		printf("root: ( %c ) value: %s\n", tree->type, tree->value);
	}
	if (prefix)
	{
		if (tree->left)
			_op_bt_print(tree->left, prefix);
		if (tree->right)
			_op_bt_print(tree->right, prefix);
	}
	else
	{
		if (tree->right)
			_op_bt_print(tree->right, prefix);
		if (tree->left)
			_op_bt_print(tree->left, prefix);
	}
	return ;
}
