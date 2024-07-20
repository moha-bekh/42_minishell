/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:22:59 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/20 21:25:23 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_create(char type, char *value)
{
	t_pbt_op	tree;

	tree = NULL;
	if (_alloc((void **)&tree, sizeof(t_bt_op)))
		return (NULL);
	tree->type= type;
	tree->tok = NULL;
	tree->value = value;
	tree->cmd_left = NULL;
	tree->cmd_right = NULL;
	tree->left = NULL;
	tree->root = NULL;
	tree->right = NULL;
	return (tree);
}