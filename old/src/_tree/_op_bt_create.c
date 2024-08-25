/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:22:59 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/09 11:51:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_create(char type, t_ptok token)
{
	t_pbt_op	tree;

	tree = NULL;
	if (_alloc((void **)&tree, sizeof(t_bt_op)) || !tree)
		return (NULL);
	tree->type = type;
	tree->token = token;
	tree->cmd = NULL;
	tree->left = NULL;
	tree->root = NULL;
	tree->right = NULL;
	return (tree);
}
