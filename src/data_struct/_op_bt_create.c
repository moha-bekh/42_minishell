/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:22:59 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 21:19:16 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_create(char operator)
{
	t_pbt_op	tree;

	tree = NULL;
	if (_alloc((void **)&tree, sizeof(t_bt_op)))
		return (NULL);
	tree->operator= operator;
	tree->cmd_left = NULL;
	tree->cmd_right = NULL;
	tree->left = NULL;
	tree->root = NULL;
	tree->right = NULL;
	return (tree);
}
